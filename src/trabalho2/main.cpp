#include <GL/glut.h>
#include <algorithm>
#include <cmath>

#define WIDTH 500
#define HEIGHT 500

/**
 * @brief Aplica o algoritmo do ponto médio para traçar uma reta
 * 
 * @param x0 coordenada x do ponto inicial
 * @param y0 coordenada y do ponto inicial
 * @param xEnd coordenada x do ponto final
 * @param yEnd coordenada y do ponto final
 */
void midpoint_algorithm(GLint x0, GLint y0, GLint xEnd, GLint yEnd) {
  GLint dx = abs(xEnd - x0);
  GLint dy = abs(yEnd - y0);
  GLint x = x0, y = y0;
  GLint sx = (x0 < yEnd) ? 1 : -1;
  GLint sy = (y0 < yEnd) ? 1 : -1;
  GLint err = dx - dy;

  glBegin(GL_POINTS);
  while (true) {
      glVertex2i(x, y);
      if (x == xEnd && y == yEnd)
          break;
      int e2 = 2 * err;
      if (e2 > -dy) {
          err -= dy;
          x += sx;
      }
      if (e2 < dx) {
          err += dx;
          y += sy;
      }
  }
  glEnd();
}

/**
 * @brief Desenha os eixos x e y
 */
void draw_axes() {
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(1.5f);
  for (int i = (int) -(WIDTH/2); i <= (int) (WIDTH/2); i += 5) {
      if(std::abs(i) % 25 == 0) {
          glBegin(GL_POINTS);
          glVertex2i(i, 0);
          glEnd();
      }
  }
  for (int i = (int) -(HEIGHT/2); i <= (int) (HEIGHT/2); i += 5) {
      if(std::abs(i) % 25 == 0) {
          glBegin(GL_POINTS);
          glVertex2i(0, i);
          glEnd();
      }
  }
  glFlush();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  // Desenha os eixos x e y
  draw_axes();

  glPointSize(2.f);

  glColor3f(0.0, 0.0, 1.0);
  midpoint_algorithm(0, 0, 125, 125);

  glColor3f(1.0, 0.0, 1.0);
  midpoint_algorithm(200, -200, 25, 100);

  glFlush();
}

void init(void) {
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-(WIDTH/2), (WIDTH/2), -(HEIGHT/2), (HEIGHT/2));
}

int main (int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Retas Otimizadas");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}
