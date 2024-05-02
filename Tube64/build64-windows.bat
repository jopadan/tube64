@echo Clear...

del bin\tube64.exe
del *.o
del *.map
cls

:COMPILE

@echo Compile...

g++ -m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-rtti -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result -Wno-format-security -c game/tube.cpp -Igame -Imusic -Isound -Itlsf -fsigned-char
g++ -m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-rtti -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result                      -c game/trig.cpp -Igame -Imusic -Isound -Itlsf
g++ -m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-rtti -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result                      -c game/misc.cpp -Igame -Imusic -Isound -Itlsf

g++ -m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-rtti -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result -D_OPL3_ -c music/hmp.cpp  -Igame -Imusic -ISound -Itlsf
g++ -m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-rtti -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result -D_OPL3_ -c sound/sb16.cpp -Igame -Imusic -ISound -Itlsf

gcc -m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections           -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result -c music/hmpfile.c       -Igame -Imusic -Isound -Itlsf
gcc -m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections           -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result -c music/hmpopl.c        -Igame -Imusic -Isound -Itlsf
gcc -m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections           -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result -c music/opl3.c -o opl.o -Igame -Imusic -Isound -Itlsf

gcc -m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections           -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result -c tlsf/tlsf.c
g++ -m64 -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-rtti -ftree-vectorize -fno-math-errno -fmax-errors=1 -fomit-frame-pointer -ffast-math -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-result -c tlsf/allocator.cpp

:LINK

@echo Link...

g++ -m64 -Ofast -DNDEBUG -o bin/tube64.exe tube.o trig.o misc.o opl.o hmpopl.o hmpfile.o hmp.o sb16.o tlsf.o allocator.o -static-libstdc++ -static-libgcc -lmingw32 -lSDL2main -lSDL2 -lwinmm -mwindows -Xlinker -Map=tube.map -Wl,--strip-all -Wl,--gc-sections

pause
exit
