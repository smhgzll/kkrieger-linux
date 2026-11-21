# .kkrieger Linux port - i386 build (clang + nasm), D3D9 via DXVK-native, SDL3
#
#   make            -> build/kkrieger        (dynamic, -O2, with symbols)
#   make small      -> build-small/kkrieger  (size optimised + stripped)
#   make pack       -> build-small/kkrieger.packed (compressed executable)
#   make run        -> run the build
#
# Runtime needs: 32-bit Vulkan driver + vulkan-loader, SDL3, fontconfig and
#                FreeType (i686),
#                libdxvk_d3d9.so (copied next to the binary).

TOP      := ../..
DXVK     := third_party/dxvk-native/usr
SDL3_LIB ?= /usr/lib/libSDL3.so.0
FONT_LIBS ?= /usr/lib/libfontconfig.so.1 /usr/lib/libfreetype.so.6
KKDATA   ?= pno0001_release.kx
KKDATAFILE ?= $(SRC)/data/$(KKDATA)

SRC      := src

ifeq ($(wildcard $(DXVK)/include/dxvk),)
$(error DXVK-native not found in $(DXVK): run tools/get_dxvk.sh)
endif
BUILD    := build

CXX      := clang++
NASM     := nasm

SOURCES  := _types.cpp _start_linux.cpp mainplayer.cpp kdoc.cpp engine.cpp \
            genbitmap.cpp genmesh.cpp genmaterial.cpp genoverlay.cpp \
            geneffect.cpp genscene.cpp genblobspline.cpp kkriegergame.cpp kkphysic.cpp \
            shadercodegen.cpp _viruz2.cpp \
            materials/material11.cpp materials/rtmanager.cpp \
            player_kkrieger/kkrieger_oplist.cpp

ARCH     := -m32 -msse2 -mfpmath=sse -mstackrealign
# MSVC dialect: MS inline asm blocks, lax template lookup, __stdcall etc.
DIALECT  := -std=gnu++14 -fms-extensions \
            -fdelayed-template-parsing -Wno-c++11-narrowing \
            -fasm-blocks -fno-exceptions -fno-rtti -fno-threadsafe-statics \
            -fno-delete-null-pointer-checks -fno-strict-aliasing -fwrapv
DEFS     := -DKKRIEGER -include $(SRC)/player_kkrieger/kkrieger_config.hpp
INCS     := -I$(SRC) -I$(SRC)/materials -I$(DXVK)/include/dxvk
WARN     := -w

OPT      ?= -O2 -g
LDEXTRA  ?=
SECT     := -ffunction-sections -fdata-sections
CXXFLAGS := $(ARCH) $(DIALECT) $(DEFS) $(INCS) $(WARN) $(OPT) $(SECT) $(EXTRA) -MMD -MP
LDFLAGS  := -m32 -no-pie -Wl,--gc-sections -Wl,-rpath,'$$ORIGIN' -L$(DXVK)/lib32 $(LDEXTRA)
LIBS     := -ldxvk_d3d9 $(SDL3_LIB) $(FONT_LIBS) -lm

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

$(BUILD)/libdxvk_d3d9.so.0: $(DXVK)/lib32/libdxvk_d3d9.so.0
	cp -L $< $@

$(BUILD)/kkrieger: $(OBJS) $(BUILD)/libdxvk_d3d9.so.0
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

-include $(OBJS:.o=.d)

# size build: no unwind tables/stack protector/ident, no libstdc++,
# stripped, no build id/relro, sections packed
SMALLOPT := -Oz -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-unwind-tables \
            -fno-stack-protector -fno-ident -fno-math-errno -fno-vectorize -fno-slp-vectorize -fno-jump-tables \
            -DKK_SMALL
SMALLLD  := -nostdlib++ -nostartfiles -Wl,-s -Wl,--build-id=none -Wl,-z,norelro -Wl,--hash-style=gnu \
            -Wl,-z,noseparate-code -Wl,-O1 -Wl,--as-needed

small:
	$(MAKE) BUILD=build-small OPT="$(SMALLOPT)" LDEXTRA="$(SMALLLD)" STARTOBJ=build-small/start.o \
	  KKDATAFILE=build-small/$(KKDATA:.kx=_v2.kx) build-small/kkrieger
	@ls -l build-small/kkrieger; size build-small/kkrieger

# packed executable (like kkrunchy for the original): tools/kkpack stub with
# the kkrunchy_k7 context mixing model + x86 DisFilter, execs from a memfd
KKPACK := $(TOP)/tools/kkpack

$(KKPACK)/kkpack: $(KKPACK)/kkpack.cpp $(KKPACK)/disfilter.hpp $(KKPACK)/model.asm
	$(NASM) -f elf32 -o $(KKPACK)/model.o $(KKPACK)/model.asm
	$(CXX) -m32 -O2 -msse2 -mfpmath=sse -o $@ $(KKPACK)/kkpack.cpp $(KKPACK)/model.o

pack: small $(KKPACK)/kkpack
	$(KKPACK)/kkpack -x build-small/kkrieger build-small/payload.bin build-small/payload.inc
	$(NASM) -f bin -DLIBPATH -I$(KKPACK)/ -DPAYLOAD='"build-small/payload.bin"' \
	  -DPAYLOADINC='"build-small/payload.inc"' -o build-small/kkrieger.packed $(KKPACK)/stub.asm
	chmod +x build-small/kkrieger.packed
	@ls -l build-small/kkrieger.packed

run: $(BUILD)/kkrieger
	cd $(BUILD) && ./kkrieger

clean:
	rm -rf $(BUILD)

.PHONY: all run clean small pack
