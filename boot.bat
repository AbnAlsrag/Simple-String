del bin\*.a
gcc -c src/*.c -Isrc
ar -rcs bin/libSimple_String.a *.o
del *.o
del test\Test.exe
gcc -o test/Test test/*.c -Isrc -Lbin -lSimple_String
cls
test\Test
pause