#include <GL/glut.h>
#include <stdio.h>


#define WIDTH 500
#define HEIGHT 500

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void reshape_handler(int w, int h) {
    glutReshapeWindow(WIDTH, HEIGHT);
}

// Função principal
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(200, 50);
    glutCreateWindow("Transformacoes");
    glClearColor(.5f, .5f, .5f, 1.f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape_handler);
    glutMainLoop();
}