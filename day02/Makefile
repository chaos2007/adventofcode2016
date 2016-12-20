# Unit tests are written in funit, use gems to install.

test:
	funit

all:
	gfortran main.f90 class_Keypad.f90
	./a.out

clean:
	rm -rf a.out
	rm *.o *.mod
	funit --clean


