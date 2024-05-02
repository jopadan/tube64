@echo Clear...

del bin\tube64.exe
del *.o
del *.map
cls

:COMPILE

set INCLUDES="-Isrc/game -Isrc/music -Isrc/sound -Ideps/tlsf -Isrc/tlsf"

set CFLAGS="-m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result -Wno-format-security ${INCLUDES}"
set CXXFLAGS="%CFLAGS% -fno-rtti %INCLUDES%"

@echo Compile...

g++ -m64 %CXXFLAGS% -c src/game/tube.cpp -fsigned-char
g++ -m64 %CXXFLAGS% -c src/game/trig.cpp
g++ -m64 %CXXFLAGS% -c src/game/misc.cpp
g++ -m64 %CXXFLAGS% -D_OPL3_ -c src/music/hmp.cpp
g++ -m64 %CXXFLAGS% -D_OPL3_ -c src/sound/sb16.cpp
gcc -m64 %CFLAGS% -c src/music/hmpfile.c
gcc -m64 %CFLAGS% -c src/music/hmpopl.c
gcc -m64 %CFLAGS% -c src/music/opl3.c -o opl.o
gcc -m64 %CFLAGS% -c deps/tlsf/tlsf.c
g++ -m64 %CXXFLAGS% -c src/tlsf/allocator.cpp

:LINK

@echo Link...

g++ -m64 -Ofast -DNDEBUG -o bin/tube64 tube.o trig.o misc.o opl.o hmpopl.o hmpfile.o hmp.o sb16.o tlsf.o allocator.o -static-libstdc++ -static-libgcc -lSDL2main -lSDL2 -lwinmm -mwindows -Xlinker -Map=tube.map -Wl,--strip-all -Wl,--gc-sections

pause
exit
