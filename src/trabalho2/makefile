#	-mwindows \

ROOT_DIR = ..\..
INCLUDE_DIR = ..\..\include
OUT_DIR = out

build: 
	mkdir out
	g++ -Wall \
	./*.cpp \
	-I"$(ROOT_DIR)/include/freeglut/include" \
	-L"$(ROOT_DIR)/include/freeglut/lib" \
	-lfreeglut \
	-lopengl32 \
	-lglu32 \
	-lm \
	-o $(OUT_DIR)/main.exe
	copy $(INCLUDE_DIR)\freeglut\bin\freeglut.dll $(OUT_DIR)