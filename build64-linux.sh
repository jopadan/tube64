#!/bin/bash

clear

#if false; then

rm -f *.o
rm -f *.map
rm -f bin/tube64

#echo 'Press any key...'
#read -rsn1

INCLUDES="-Isrc/game -Isrc/music -Isrc/sound -Ideps/tlsf -Isrc/tlsf"
CFLAGS+="-m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result -Wno-format-security ${INCLUDES}"
CXXFLAGS+="${CFLAGS} -fno-rtti"

echo 'Compile tube...'
g++ -m64 ${CXXFLAGS} -c src/game/tube.cpp -fsigned-char
g++ -m64 ${CXXFLAGS} -c src/game/trig.cpp
g++ -m64 ${CXXFLAGS} -c src/game/misc.cpp
g++ -m64 ${CXXFLAGS} -D_OPL3_ -c src/music/hmp.cpp
g++ -m64 ${CXXFLAGS} -D_OPL3_ -c src/sound/sb16.cpp
gcc -m64 ${CFLAGS} -c src/music/hmpfile.c
gcc -m64 ${CFLAGS} -c src/music/hmpopl.c
gcc -m64 ${CFLAGS} -c src/music/opl3.c -o opl.o
gcc -m64 ${CFLAGS} -c deps/tlsf/tlsf.c
g++ -m64 ${CXXFLAGS} -c src/tlsf/allocator.cpp

#fi

echo 'Link tube...'
g++ -m64 -Ofast -DNDEBUG -o bin/tube64 tube.o trig.o misc.o opl.o hmpopl.o hmpfile.o hmp.o sb16.o tlsf.o allocator.o -static-libstdc++ -static-libgcc -lSDL2 -lasound -Xlinker -Map=tube.map -Wl,--strip-all -Wl,--gc-sections

chmod +x bin/tube64

