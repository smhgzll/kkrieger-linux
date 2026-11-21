# .kkrieger Linux port — technical notes

farbrausch's open-sourced code (`fr_public/werkkzeug3_kkrieger`, BSD) plus the
game data extracted from the original 2004 executable. Graphics run on a
Vulkan renderer with the game's shaders in GLSL, precompiled at build time
([Renderer](#renderer)); the Win32 sound / window / GDI layer was rewritten
with SDL3, a software mixer and fontconfig/FreeType. 32-bit (i386) build; the
V2 synthesizer runs from its original NASM source.

The packed size build (`make pack`) is **101,387 bytes**; the original
`pno0001.exe` is 97,280 bytes (details: [Size](#size)). The other two
versions of the port are in [`../opengl`](../opengl) and [`../dxvk`](../dxvk);
[the main README](../../README.md#three-versions) compares them.

## Building and running

Requirements: clang, nasm, python3, `glslc` (shaderc), 32-bit `glibc-devel`
(glibc ≥ 2.34), `vulkan-headers`, `SDL3-devel`, i686 `SDL3`, `fontconfig`, `freetype`, a
32-bit Vulkan 1.3 driver + `vulkan-loader` (the Vulkan loader is opened
through SDL, nothing else is linked), and the Liberation fonts (fontconfig
maps Arial/Times to them).

```sh
make            # build/kkrieger (-O2, symbols, debug environment variables)
make run
./build/kkrieger [-f] [-r 1280x720] [other.kx]
make small      # build-small/kkrieger (-Oz, specialised to the 2004 data)
make pack       # build-small/kkrieger.packed (101 KB, one file)
./build-small/kkrieger.packed [-f] [-r 1280x720]
```

`-f` is fullscreen at desktop resolution (the picture is scaled), `-r` sets the
render resolution (default 1024×768 like the original). Controls are the
original ones: mouse + W/A/S/D, left click fires, space jumps, 1–9 select
weapons, arrow keys + Enter in the menu.

## Debug environment variables (normal build)

| Variable | Effect |
| --- | --- |
| `KK_SHOT=a,b,..` (+`KK_SHOT_MS=1`) | save the back buffer at these frames/ms as `kkshot_*.tga` |
| `KK_SHOT_REL=1` | `KK_SHOT` times are relative to the first frame (after precalc) |
| `KK_SHOT_EXIT=1` | quit after the last screenshot |
| `KK_KEYS=ms:KEY[:held_ms],..` | inject key presses (ENTER, ESC, SPACE, UP.., W, MOUSE); real input is ignored meanwhile |
| `KK_NOGRAB=1` | don't grab the mouse |
| `KK_STARTSTATE=n` | initial `Switches[KGS_GAME]`: 0 = straight into the game, 6 = main menu |
| `KK_STARTPOS=x,y,z[,dir[,look]]` | player start position / direction (radians) |
| `KK_GAMELOG=1` | game state, position, weapon/ammo, triggered zones, `sDPrintF` → stderr |
| `KK_MTRLLOG=1`, `KK_DUMPOP=n` | material / operator output diagnostics |
| `KK_ROOT=n` | render operator `n` as the root |
| `KK_IPPDUMP=ms` | at that game time, dump every IPP operator's output as `ipp_op*.tga` |
| `KK_DUMPTEXT=1` | dump the `Bitmap_Text` results as `text_*.tga` |
| `KK_GPU=n` | use Vulkan device `n` (default: the first discrete GPU); the chosen device is printed |
| `KK_FRAMELOG=1` | print every frame slower than 8 ms, split into tick / paint / rest, with the player position |
| `KK_SOUNDLOG=1` | sound effects as rendered at load time (size, peak) and every `SamplePlay` |
| `KK_FIXEDTIME=ms` | every frame lasts exactly `ms`, fixed random seed: two builds render identical frames |
| `KK_HASHOPS=file` | hash of every generated bitmap/mesh (verifies the size specialisations) |
| `KK_OPSTATS=file` | every operator's type, parameters, strings and animation opcodes (data analysis) |
| `EXTRA="-DKK_CRASHHANDLER -DKK_VERBOSE"` | build with a crash handler and verbose logging |

The size build (`KK_SMALL`) has none of these; `-DKK_COVERAGE` brings them back
(that is how `../../tools/verify_small.sh` builds it).

## What the port changes

Platform (`src/_start_linux.cpp`): SDL3 window/events, the Vulkan renderer, an
SDL3 audio stream with a software mixer for the (3D) sound buffers (the music
is rendered in SDL's audio callback under the stream lock; the game side never
waits for that lock — `SamplePlay` is lock-free and the mixer advances buffer
positions with compare-and-swap), fontconfig (GDI face name → file: Arial →
Liberation Sans, Times → Liberation Serif) + FreeType instead of GDI (no
headers needed, only ABI-stable struct offsets), stdio file I/O.

Compiler compatibility (MSVC 2003 → clang):

* MS inline asm with reference parameters / implicit eax/st0 returns →
  equivalent C (`sFtol`, `sFPow`, `sMulDiv`, `Fade64`, …), `CallCode` →
  `linux/callcode.asm`
* reading variadic arguments as `(&param)[i]` (undefined behaviour) → `va_list`
* `-mstackrealign`, `-fno-delete-null-pointer-checks`, `-fno-strict-aliasing`, `-fwrapv`
* V2 asm: stdcall name decoration, symbols clashing with libm (`pow` …) →
  `../../tools/v2_asm_to_elf.py`

2004 data compatibility (recovered from the decompiled binary):

* `KDoc::Init`: the 2004 export format (FUN_0081859c); fixed 118 BPM; the
  root is the last operator
* operators whose parameter layout changed later: KKriegerPara, Rotate,
  Cylinder, PartSystem, Print, Monster, IPP_Viewport →
  `Compat2004Convention/Defaults`
* `Bitmap_Text2004` (0x80c951): font page/atlas generated at run time
* operator 0xe0 (`Init_Misc_Root2004`, 0x815166) — missing from the repository
* V2M song/effects converted to the newer synth's format (`V2ConvertSong`; the
  size build does it at build time with `linux/kxconv.cpp`)
* material code generator: `sMCA_INVERTA` regression for lerp (2004: FUN_00802664)
* viewport: clear with alpha = 0, use the scene camera after exec
* `IPP_Select` garbage `count` parameter; portal culling and the weapon light
  (disabled by `sINTRO` in the repository configuration)
* sound effects (`RenderSoundEffects`, 2004: FUN_0081e670): the positions in
  the VFX table are in samples, but the V2 player expected milliseconds, so
  every effect was rendered from behind the end of the tune — silent. The
  player now runs at 44100 ticks/s; like 2004 the effects are plain stereo,
  not 3D.
* `sUSE_TIME_OF_YEAR` off (the 2004 exe does not import `GetSystemTime`)
* material animation: the newer engine does not run a mesh's operator chain
  every frame, so the animated materials of the 2004 data (fading intro and
  credits text) never updated → `ExecAnimatedMaterials` (genscene.cpp)
* **Physics (`src/kkphysic.cpp`)**: the published source is a later
  intermediate revision; the 2004 particle physics had been deleted from it,
  only commented-out structs were left. It was recovered from the executable's
  disassembly: Verlet particles, distance constraints, collision that slides
  along up to two planes (`MoveParticle` 0x81b5bd), moving doors/cells pushing
  bodies (`PhysicDCell`), 5-particle player and monster bodies
  (`KKriegerBody`), shot particles (`Scene_Physic` mode 0, started as shot
  events), boxes (mode 1), the 2004 monster AI, and feet in `Scene_Walk`
  probing the ground. The newer engine's single-sphere collider,
  `KKriegerShot`/`ShotAI`, `MonsterMagnetAI`, `KKMonsterWalk` and the
  face-based collision code were removed. This fixed getting stuck on walls,
  shots coming from the wrong place when turning, spider speed/damage rate and
  feet hanging in the air.
* `Init_KKrieger_Para` does not set the start position (in 2004 it is the same
  function as `Init_KKrieger_Events`); the HUD's `%W` prints the ammo for
  weapon 0, not "inf" (0x80d701)
* `SetPainter` walks through `Exec_Misc_Nop` operators too; switching to the
  same root operator does not `ResetRoot` (the 2004 data has a single root)
* the Monster operator with the 2004 parameter layout (26 parameters; no
  weapon kind, spawn switch or walk style): ranged attacks only with link 0
  (the shot event). Before, spiders fired the player's shotgun.
* dynamic cells are solid only when their mode is exactly `KCM_SUB` (an
  unconfirmed door box pushed the player at spawn); static mode 9 cells are
  solid only for the monster foot probe; the `NotForPlayer` rule.
* the 2004 tick ran with the FPU rounding toward −∞ (0x143f). In that mode the
  Verlet step nudges a resting player towards −x/−z every frame, so he slowly
  slides (also measured in the original: 0.0002–0.007 units/s). The port
  deliberately keeps round-to-nearest: no sliding; physics may differ from the
  original in the last bits.

Clang-specific undefined behaviour fixes (these broke the picture/game):

* `Mesh_Cube`: reading ty/tz as `(&tx)[j]` → all geometry was subdivided wrong
* scene operators: `sCopyMem(SRT,&s.x,9*4)` assumed the separate `s,r,t`
  parameters to be contiguous; once clang inlined `Init_Scene_Multiply` into
  `Init_Scene_Transform` the translation was lost, every pickup zone fell to
  the origin and the player collected all of them at spawn → `PackSRT`
* the `Walk` leg array, `InitSRT` local arrays

## Renderer

`src/_start_linux.cpp` implements the engine's graphics interface (material
setups = render states + shaders, textures, geometry buffers, viewports and
render targets) on `src/vkrender.hpp`:

* **Shaders** (`src/shaders/`): the 2004 engine generated its material
  shaders at load time from the material parameters (a shader "metaprogram"
  interpreted per material). The 48 materials of the game data use 21 vertex
  and 41 pixel shaders; they were converted once to GLSL and are now plain
  sources. `materials.txt` maps each material — identified by the fields its
  shaders depend on, see `MaterialShaderKey` in `materials/material11.cpp` —
  to its vertex/pixel shader. The alpha test is part of the pixel shader
  (`round(a·255) > 128`, as on 8-bit hardware). A material that is not in the
  table (another `.kx` document) gets no shader and is not drawn.
* **Packing** (`tools/shaderpack.py`, run by the Makefile): `glslc -O`,
  then the ids of every module are renumbered the same way — types,
  constants and interface variables get one id for all modules, keyed by
  their definition and decorations — so the many identical declarations
  become identical bytes. The modules stay plain SPIR-V (no decoder in the
  executable); the 83 KB of SPIR-V cost 4.0 KB in the pack. The table holds
  FNV-1a hashes of the material keys.
* **Render states**: the material code writes (token, value) pairs with
  Vulkan values (`VKR_ZFUNC`, `VK_COMPARE_OP_LESS_OR_EQUAL`, …); a state keeps
  its value until set again, like the engine expects.
* **Pipelines**: Vulkan 1.3 dynamic rendering; pipelines are keyed by
  shaders, vertex format, blend state, colour mask and topology class.
  Cull mode, depth/stencil (two-sided), topology, viewport, scissor and depth
  bias are dynamic state. Vertex inputs a format lacks read zero, unbound
  textures read (0,0,0,1).
* **Coordinates**: the engine's clip space has y up and z in 0..1 and its
  pixel centres are at integer coordinates: the viewport is flipped and
  shifted by half a pixel; front faces are clockwise. Cube maps clamp; the
  LOD range depends on the mip filter and the texture's level count.
* **Resources**: buffers are persistently mapped; the dynamic vertex/index
  buffers have a copy per frame in flight (2 frames) and start over every
  frame, static buffers wait for the GPU only when a buffer is reused from the
  start. Textures are uploaded through a staging ring, new images read as
  zero, every image stays in `VK_IMAGE_LAYOUT_GENERAL` with a global barrier
  between passes, copies and uploads. Read backs (`ReadTexture`, which the
  texture generators use, and `KK_SHOT`) wait for the GPU.
* **Present**: the engine draws into an off-screen back buffer (the render
  resolution); present blits it to the swapchain image at window size.
  Immediate/mailbox present mode, FIFO with vsync.

Tested with the Khronos validation layer including synchronization
validation (no messages);
`../../tools/verify_small.sh` gives the same 3,634 texture/mesh hashes as the
first version of the port, which ran the engine's original Direct3D 9 code
on DXVK, and the same screenshots within 0.02% of the pixels.

## Size

|  | bytes |
| --- | ---: |
| original `pno0001.exe` (kkrunchy + lekktor, 2004) | 97,280 |
| `build/kkrieger` (-O2, symbols) | 2,198,860 |
| `build-small/kkrieger` (unpacked, stripped) | 395,988 |
| **`build-small/kkrieger.packed`** | **101,387** |

The pack is a 2.3 KB stub + 96.7 KB of compressed ELF (the 83 KB of SPIR-V
cost about 4 KB of it). Unpacking takes about 1.7 s. The original carried no
graphics layer — Windows supplied Direct3D 9 and its shader compiler — while
this version carries its renderer and the compiled shaders: the
[DXVK version](../dxvk) takes Direct3D 9 from a shared library (95,336
bytes), the [OpenGL version](../opengl) leaves pipelines and shader
compilation to the driver (95,088 bytes).

**Packer (`../../tools/kkpack`, shared by the three versions; the model is
the one tuned for the OpenGL version, see [its notes](../opengl/README.md#size))**:
the context-mixing model of kkrunchy_k7 (ryg, public domain, `model.asm`) +
the x86 `DisFilter` (splits the instruction
stream into opcode, modrm, displacement, immediate, call target … streams;
the opcode tables were fixed for the SSE opcodes clang emits). The stub
(`stub.asm`, hand-written ELF header) decodes the stream, unfilters `.text`
and runs the result with `memfd_create` + `execveat`. Section headers and link-only sections are
dropped from the pack. `kkpack -x elf payload.bin payload.inc` packs and
verifies by unpacking; a stub built with `-DDUMP` writes the unpacked image
to stdout.

**Compiler**: `-Oz`, `-fno-vectorize -fno-slp-vectorize -fno-jump-tables`
(chosen by packed size, not raw size: x87 FPU code, LTO, the machine outliner
and `-mno-stackrealign` all shrank the code but grew the pack),
`-nostartfiles` + `linux/start.asm`, `-nostdlib++`, `--gc-sections`.

**Data**: the V2 tunes are converted at build time (`kxconv`, so neither the
converter nor its parameter tables end up in the exe); `../../tools/kxtranspose.py`
stores operator types/inputs as separate streams and operator parameters
column-major within each class (−1.2 KB; `KDoc::Init` reads this layout when
`KK_SMALL` is set).

**Code**: stb_truetype → FreeType (−7 KB packed), debug code and messages, the
operators the 2004 data does not use. And, like lekktor did for the original
but checked against the data (`KK_OPSTATS` + basic block coverage,
`../../tools/coverage`): the 23 unused animation bytecode opcodes, the unused
IPP viewport modes (the data always has `flags=7`), mesh skinning, the
sprite/thick line material programs, the screen grab chain, the
`SCRIPTVERIFY`/`CheckBitmap`/`CheckMesh` error paths, loading external .kx
files, root switching. All of it is `#ifdef KK_SMALL`; the normal build stays
general.

**Verification**: `../../tools/verify_small.sh . DIR` builds the size build with
the debug variables, records — with `KK_FIXEDTIME` — 13 screenshots of the
intro, the game start and scripted play, and the hashes of all 3,634 generated
bitmaps/meshes; compare two directories with `diff` + `../../tools/shotcmp.py`.
The specialised code gives bit-identical results to the general code built
with the same flags.

## Known issues

* MSVC `/QIfist`: in 2004 float→int conversions in C rounded, clang truncates →
  procedural textures may differ slightly.
* The game scene is about 15% brighter than the original (more on distant
  walls). The IPP chain is identical to 2004 (the colour operation table was
  found byte for byte in the binary); the difference is in scene lighting: the
  2004 engine (0x817134) draws a base pass lit by a white light tied to the
  camera, stencil passes for up to 3 shadowing lights and up to 4 lights in a
  single pass, while the port uses the later engine with a pass per light and
  its material/shader generator.
* The intro's IPP "glare" result was not compared against the original.
* `-O2` and `-Oz` builds differ in the last floating point bits of some mesh
  operators (bend/rotate chains), so after a few seconds the O2 build's game
  play can diverge from the -Oz one. With the same flags, general and
  specialised code are identical.
* The packed exe uses `memfd_create`/`execveat` (Linux ≥ 3.19); it does not run
  where `vm.memfd_noexec=2`; `build-small/kkrieger` can be started directly.

## Comparing with the original

`../../tools/hook/` adds a code cave to the (unpacked) original that intercepts
the `Present` call and writes the back buffer as `shot_NN.raw` at given
milliseconds; run it with Proton 11. `--startgame` starts straight in the
game, `--nomouse` disables mouse look (under XWayland `SetCursorPos` fails, so
the view drifted on its own). Comparison images are in `../../docs/compare/`.
Built with `-DPLAYTEST -DKEYS='dd ms,0x100,vk, ms,0x101,vk,...'` the hook also
sends key presses to the game window and writes the player position
(`KKriegerGame+0x14948`) to `pos.bin` every 250 ms. Pass the exe to Proton by
its absolute path.
