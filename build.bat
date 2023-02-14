del bin\*.a
gcc -c src/*.c -Isrc
ar -rcs bin/libSimple_String.a *.o
del *.o
pause