#	-mwindows \

build: 
	g++ -Wall \
	./*.cpp \
	-I"./include/freeglut/include" \
	-L"./include/freeglut/lib" \
	-lfreeglut \
	-lopengl32 \
	-lglu32 \
	-lm \
	-o main.exe