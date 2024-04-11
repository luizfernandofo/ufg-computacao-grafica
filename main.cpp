#include <gl/gl.h>
#include <gl/glu.h>
#include <GL/glut.h>
#include <list>
#include <stdio.h>
#include <cmath>

#define WIDTH 600
#define HEIGHT 600

typedef struct {
  GLuint x, y;
} Point;

std::list<Point *> points;

float distanceSqrd(float p1_x, float p1_y, float p2_x, float p2_y) {
  return (p1_x - p2_x) * (p1_x - p2_x) + (p1_y - p2_y) * (p1_y - p2_y);
}

void mouse_handler(int button, int state, int _x, int _y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    points.push_back(new Point {(GLuint) _x, (GLuint) _y});
  }

  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    if (!points.empty()) {
      std::list<Point *>::iterator it;
      for (it = points.begin(); it != points.end(); ++it) {
        if (distanceSqrd((float) (*(*it)).x, (float) (*(*it)).y, (float) _x, (float)_y) <= 64.f) {
          delete *it;
          points.erase(it);
          break;
        }
      }
    }
  }
}

void reshape_handler(int w, int h){
  glutReshapeWindow(WIDTH, HEIGHT);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);

  glPointSize(15); // Tamanho do ponto
  glBegin(GL_POINTS);
  glColor3f(1.0, 0.0, 0.0); // Cor do ponto (vermelho)
  for (auto p : points) {
    glVertex2i((*p).x, HEIGHT - (*p).y); 
  }
  glEnd();

  glFlush();
}


// ============= Main =============
int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (WIDTH, HEIGHT);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Grupo 1 - Fecho convexo 2D");
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel (GL_FLAT);
  gluOrtho2D(0, WIDTH, 0, HEIGHT); // Define o sistema de coordenadas da janela
  glViewport(0, 0, WIDTH, HEIGHT);
  glutMouseFunc(mouse_handler);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape_handler);
  glutMainLoop();
  return 0;
}

