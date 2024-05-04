#	-mwindows \

ROOT_DIR = ..\..
INCLUDE_DIR = ..\..\include
OUT_DIR = out
MAIN_FILE = bresenham

build: 
	if not exist "$(OUT_DIR)" mkdir $(OUT_DIR)
	g++ -Wall \
	./$(MAIN_FILE).cpp \
	-I"$(ROOT_DIR)/include/freeglut/include" \
	-L"$(ROOT_DIR)/include/freeglut/lib" \
	-lfreeglut \
	-lopengl32 \
	-lglu32 \
	-lm \
	-o $(OUT_DIR)/main.exe
	copy $(INCLUDE_DIR)\freeglut\bin\freeglut.dll $(OUT_DIR)