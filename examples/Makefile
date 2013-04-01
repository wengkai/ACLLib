SRC = ..\acllib\acllib.c
INCLUDE_DIR = ..\acllib
LIB = gdi32 ole32 oleaut32 uuid winmm msimg32

ex01 :
	gcc $(SRC) $@.c -I$(INCLUDE_DIR) $(LIB:%=-l%) -DWINVER=0x0501 -o $@ 
