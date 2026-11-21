#!/bin/bash
# verify_small.sh PORTDIR OUTDIR [extra make args]
#
# Check that the size build of one port (port/opengl, port/vulkan or
# port/dxvk) still computes exactly what it did before: builds it with the
# debug environment variables enabled (-DKK_SMALL -DKK_COVERAGE,
# PORTDIR/build-verify) and records, with fixed
# 20 ms frames (KK_FIXEDTIME) so runs are reproducible:
#   OUTDIR/hashes.txt   hash of every generated bitmap/mesh (KK_HASHOPS)
#   OUTDIR/*.tga        intro at 3/8/15/25/40 s
#   OUTDIR/game/*.tga   game start, no input
#   OUTDIR/play/*.tga   scripted play (walk, turn, shoot, switch weapon)
# Compare two OUTDIRs with: diff A/hashes.txt B/hashes.txt and
# tools/shotcmp.py A B. Two runs of the same build are identical (the
# scripted play may differ in a handful of pixels).

set -e
P=$(realpath "$1"); O=$(realpath -m "$2"); shift 2 || true
cd "$P"
SO="-Oz -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-stack-protector -fno-ident -fno-math-errno -fno-vectorize -fno-slp-vectorize -fno-jump-tables"
make build-small/pno0001_release_v2.kx >/dev/null
make BUILD=build-verify OPT="$SO -DKK_SMALL -DKK_COVERAGE" LDEXTRA="-nostdlib++ -nostartfiles -Wl,--build-id=none" \
     STARTOBJ=build-verify/start.o HASHIMPORT=1 KKDATAFILE=build-small/pno0001_release_v2.kx "$@" build-verify/kkrieger -j8 >/dev/null
K=$P/build-verify/kkrieger
rm -rf "$O"; mkdir -p "$O/game" "$O/play"
export KK_FIXEDTIME=20 KK_NOGRAB=1 KK_SHOT_MS=1 KK_SHOT_REL=1 KK_SHOT_EXIT=1
(cd "$O" && KK_HASHOPS="$O/hashes.txt" KK_SHOT=3000,8000,15000,25000,40000 timeout 120 "$K" > run1.log 2>&1) || true
(cd "$O/game" && KK_STARTSTATE=0 KK_SHOT=2000,4000,8000 KK_KEYS=999999:X timeout 120 "$K" > ../run2.log 2>&1) || true   # KK_KEYS: ignore real input
(cd "$O/play" && KK_STARTSTATE=0 KK_SHOT=3000,6000,9000,12000,15000 \
  KK_KEYS="1000:W:3000,2000:MOUSE:200,3500:LEFT:600,4500:MOUSE:200,5000:W:2500,6000:MOUSE:200,7000:RIGHT:900,8000:SPACE,9000:2,9500:MOUSE:300,10500:W:3000,11000:MOUSE:200,12500:LEFT:1500,13000:MOUSE:200" \
  timeout 120 "$K" > ../run3.log 2>&1) || true
echo "$O: $(wc -l < "$O/hashes.txt") op hashes, $(ls "$O"/*.tga "$O"/game/*.tga "$O"/play/*.tga | wc -l) shots"
