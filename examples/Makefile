SRC = ..\acllib\acllib.c
INCLUDE_DIR = ..\acllib
INCLUDE = $(INCLUDE_DIR)\acllib.h
LIB = kernel32 user32 gdi32 winspool comdlg32 \
	advapi32 shell32 ole32 oleaut32 uuid \
	odbc32 odbccp32 winmm msimg32
	
TARGETS = keyboard paint 

all : paint keyboard

main :
	gcc $(SRC) $@.c -I$(INCLUDE_DIR) $(LIB:%=-l%) -o $@

tetris :
	gcc $(SRC) $@.c -I$(INCLUDE_DIR) $(LIB:%=-l%) -o $@
	
paint : 
	gcc $(SRC) $@.c -I$(INCLUDE_DIR) $(LIB:%=-l%) -o $@
	
keyboard : 
	gcc $(SRC) $@.c -I$(INCLUDE_DIR) $(LIB:%=-l%) -o $@
		
