# .kkrieger Linux port - i386 build (clang + nasm), OpenGL 4.5, SDL3
#
#   make            -> build/kkrieger        (dynamic, -O2, with symbols)
#   make small      -> build-small/kkrieger  (size optimised + stripped)
#   make pack       -> build-small/kkrieger.packed (compressed executable)
#   make run        -> run the build
#
# Build needs:   clang, nasm, python3, OpenGL headers (GL/glcorearb.h), SDL3 headers
# Runtime needs: 32-bit OpenGL 4.5 driver (libglvnd), SDL3, fontconfig and
#                FreeType (i686)

TOP      := ../..
SDL3_LIB ?= /usr/lib/libSDL3.so.0
FONT_LIBS ?= /usr/lib/libfontconfig.so.1 /usr/lib/libfreetype.so.6
GL_LIB   ?= /usr/lib/libOpenGL.so.0
KKDATA   ?= pno0001_release.kx
KKDATAFILE ?= $(SRC)/data/$(KKDATA)

SRC      := src

BUILD    := build

CXX      := clang++
NASM     := nasm

SOURCES  := _types.cpp _start_linux.cpp glrender.cpp mainplayer.cpp kdoc.cpp engine.cpp \
            genbitmap.cpp genmesh.cpp genmaterial.cpp genoverlay.cpp \
            geneffect.cpp genscene.cpp genblobspline.cpp kkriegergame.cpp kkphysic.cpp \
            _viruz2.cpp \
            materials/material11.cpp materials/rtmanager.cpp \
            player_kkrieger/kkrieger_oplist.cpp

ARCH     := -m32 -msse2 -mfpmath=sse -mstackrealign
# MSVC dialect: MS inline asm blocks, lax template lookup, __stdcall etc.
DIALECT  := -std=gnu++14 -fms-extensions \
            -fdelayed-template-parsing -Wno-c++11-narrowing \
            -fasm-blocks -fno-exceptions -fno-rtti -fno-threadsafe-statics \
            -fno-delete-null-pointer-checks -fno-strict-aliasing -fwrapv
DEFS     := -DKKRIEGER -include $(SRC)/player_kkrieger/kkrieger_config.hpp
INCS     := -I$(SRC) -I$(SRC)/materials -I$(BUILD)
WARN     := -w

OPT      ?= -O2 -g
LDEXTRA  ?=
SECT     := -ffunction-sections -fdata-sections
CXXFLAGS := $(ARCH) $(DIALECT) $(DEFS) $(INCS) $(WARN) $(OPT) $(SECT) $(EXTRA) -MMD -MP
LDFLAGS  := -m32 -no-pie -Wl,--gc-sections $(LDEXTRA)
LIBS     := $(SDL3_LIB) $(GL_LIB) $(FONT_LIBS) -lm

STARTOBJ ?=
OBJS     := $(STARTOBJ) $(addprefix $(BUILD)/,$(SOURCES:.cpp=.o)) $(BUILD)/_viruz2a.o $(BUILD)/data_linux.o $(BUILD)/callcode.o

all: $(BUILD)/kkrieger

$(BUILD)/%.o: $(SRC)/%.cpp Makefile
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/_viruz2a_elf.asm: $(SRC)/_viruz2a.asm $(TOP)/tools/v2_asm_to_elf.py
	@mkdir -p $(BUILD)
	python3 $(TOP)/tools/v2_asm_to_elf.py $< $@

$(BUILD)/_viruz2a.o: $(BUILD)/_viruz2a_elf.asm
	$(NASM) -f elf32 -w-label-orphan -o $@ $<

$(BUILD)/data_linux.o: linux/data_linux.asm $(KKDATAFILE)
	$(NASM) -f elf32 -DKKDATA='"$(KKDATAFILE)"' -o $@ $<

# offline V2 tune conversion (the size build has no converter)
$(BUILD)/kxconv: linux/kxconv.cpp $(SRC)/_viruz2.cpp $(SRC)/_types.cpp
	$(CXX) $(ARCH) $(DIALECT) $(DEFS) $(INCS) $(WARN) -O1 $(SECT) -Wl,--gc-sections -o $@ $^

# + the layout the size build's loader reads (tools/kxtranspose.py)
$(BUILD)/%_v2.kx: $(SRC)/data/%.kx $(BUILD)/kxconv $(TOP)/tools/kxtranspose.py
	$(BUILD)/kxconv $< $@.tmp
	python3 $(TOP)/tools/kxtranspose.py $@.tmp $@
	rm -f $@.tmp

$(BUILD)/callcode.o: linux/callcode.asm
	@mkdir -p $(BUILD)
	$(NASM) -f elf32 -o $@ $<

$(BUILD)/start.o: linux/start.asm
	@mkdir -p $(BUILD)
	$(NASM) -f elf32 -o $@ $<

$(BUILD)/starthash.o: linux/start.asm
	$(NASM) -f elf32 -DHASHIMPORT -o $@ $<

$(BUILD)/imports.o: linux/imports.cpp Makefile
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# the game's shaders: minified GLSL text, packed with the material table
SHADERSRC := $(wildcard $(SRC)/shaders/*.vert $(SRC)/shaders/*.frag) $(SRC)/shaders/materials.txt
$(BUILD)/shaders.inc $(BUILD)/materialshaders.inc &: $(SHADERSRC) tools/shaderpack.py
	@mkdir -p $(BUILD)
	python3 tools/shaderpack.py $(SRC)/shaders $(BUILD)/shaders.inc $(BUILD)/materialshaders.inc
$(BUILD)/glrender.o: $(BUILD)/shaders.inc
$(BUILD)/materials/material11.o: $(BUILD)/materialshaders.inc

ifeq ($(HASHIMPORT),1)
# import by hash (tools/mkimports.py, linux/imports.cpp): link once the
# normal way to learn the imports, then again against empty libraries that
# only carry the sonames - no symbol names, PLT or version tables remain
REALLIBS := $(SDL3_LIB) $(GL_LIB) $(FONT_LIBS) /usr/lib/libm.so.6 /usr/lib/libgcc_s.so.1 /usr/lib/libc.so.6
$(BUILD)/kkrieger: $(OBJS) $(BUILD)/starthash.o $(BUILD)/imports.o tools/mkimports.py
	$(CXX) $(LDFLAGS) -o $@.dyn $(OBJS) $(LIBS)
	python3 tools/mkimports.py $@.dyn $(BUILD)/importtab.asm $(REALLIBS)
	$(NASM) -f elf32 -o $(BUILD)/importtab.o $(BUILD)/importtab.asm
	python3 tools/mkimports.py --stubs $@.dyn $(BUILD)/stubs $(CXX)
	$(CXX) $(LDFLAGS) -nostdlib -o $@ $(filter-out $(STARTOBJ),$(OBJS)) $(BUILD)/starthash.o \
	  $(BUILD)/imports.o $(BUILD)/importtab.o -Wl,--no-as-needed @$(BUILD)/stubs/list
else
$(BUILD)/kkrieger: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)
endif

-include $(OBJS:.o=.d)

# size build: no unwind tables/stack protector/ident, no libstdc++,
# stripped, no build id/relro, sections packed
SMALLOPT := -Oz -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-unwind-tables \
            -fno-stack-protector -fno-ident -fno-math-errno -fno-vectorize -fno-slp-vectorize -fno-jump-tables \
            -DKK_SMALL
SMALLLD  := -nostdlib++ -nostartfiles -Wl,-s -Wl,--build-id=none -Wl,-z,norelro -Wl,--hash-style=gnu \
            -Wl,-z,noseparate-code -Wl,-O1 -Wl,--as-needed

small:
	$(MAKE) BUILD=build-small OPT="$(SMALLOPT)" LDEXTRA="$(SMALLLD)" STARTOBJ=build-small/start.o HASHIMPORT=1 \
	  KKDATAFILE=build-small/$(KKDATA:.kx=_v2.kx) build-small/kkrieger
	@ls -l build-small/kkrieger; size build-small/kkrieger

# size build with symbols and a link map, for ../../tools/packprof.py
prof:
	$(MAKE) BUILD=build-prof OPT="$(SMALLOPT)" LDEXTRA="$(filter-out -Wl$(comma)-s,$(SMALLLD)) -Wl,-Map=build-prof/kkrieger.map" \
	  STARTOBJ=build-prof/start.o HASHIMPORT=1 KKDATAFILE=build-small/$(KKDATA:.kx=_v2.kx) build-small/$(KKDATA:.kx=_v2.kx) build-prof/kkrieger

comma := ,

# packed executable (like kkrunchy for the original): tools/kkpack stub with
# the kkrunchy_k7 context mixing model + x86 DisFilter, execs from a memfd
KKPACK := $(TOP)/tools/kkpack

$(KKPACK)/kkpack: $(KKPACK)/kkpack.cpp $(KKPACK)/disfilter.hpp $(KKPACK)/model.asm
	$(NASM) -f elf32 -o $(KKPACK)/model.o $(KKPACK)/model.asm
	$(CXX) -m32 -O2 -msse2 -mfpmath=sse -o $@ $(KKPACK)/kkpack.cpp $(KKPACK)/model.o

pack: small $(KKPACK)/kkpack
	$(KKPACK)/kkpack -x build-small/kkrieger build-small/payload.bin build-small/payload.inc
	$(NASM) -f bin -I$(KKPACK)/ -DPAYLOAD='"build-small/payload.bin"' \
	  -DPAYLOADINC='"build-small/payload.inc"' -o build-small/kkrieger.packed $(KKPACK)/stub.asm
	chmod +x build-small/kkrieger.packed
	@ls -l build-small/kkrieger.packed

run: $(BUILD)/kkrieger
	cd $(BUILD) && ./kkrieger

clean:
	rm -rf $(BUILD)

.PHONY: all run clean small pack prof
