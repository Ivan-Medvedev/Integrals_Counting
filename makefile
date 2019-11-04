LIBS := libm.a

EXECUTABLE := project_007


all: $(EXECUTABLE)
	
$(EXECUTABLE) : pa.o pc.o
	gcc -m32 -o $(EXECUTABLE) pa.o pc.o $(LIBS)
	
	
	
pa.o : Project.asm
	nasm -f elf32 -o pa.o Project.asm
pc.o : Project.c
	gcc -m32 -c -o pc.o Project.c  $(DEFINES)




clean:
	rm -rf *.o $(EXECUTABLE)
