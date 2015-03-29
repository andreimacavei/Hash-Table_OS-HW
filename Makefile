CC = cl
CFLAGS = /W3 -D_CRT_SECURE_NO_DEPRECATE /nologo

build: tema1.exe

tema1.exe: main.obj hash.obj list.obj
	$(CC) /nologo main.obj hash.obj list.obj /Fe$@

main.obj: main.c utils.h
	$(CC) $(CFLAGS) /Fo$@ /c main.c

hash.obj: hash.c hash.h utils.h
	$(CC) $(CFLAGS) /Fo$@ /c hash.c

list.obj: list.c list.h utils.h
	$(CC) $(CFLAGS) /Fo$@ /c list.c

clean: exe_clean obj_clean

obj_clean:
	del *.obj

exe_clean:
	del *.exe
