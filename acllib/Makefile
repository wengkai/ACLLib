LIB = \
	-lkernel32 \
	-luser32 \
	-lgdi32 \
	-lwinspool \
	-lcomdlg32 \
	-ladvapi32 \
	-lshell32 \
	-lole32 \
	-loleaut32 \
	-luuid \
	-lodbc32 \
	-lodbccp32 \
	-lwinmm \
	-lmsimg32

main : acllib.h acllib.c main.c
	gcc acllib.c main.c -o a.exe $(LIB)
	
tetris : acllib.h acllib.c tetris.c
	gcc acllib.c tetris.c -Wall -o tetris.exe $(LIB)
		