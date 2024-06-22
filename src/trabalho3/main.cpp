#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>

#define WIDTH 800
#define HEIGHT 800

#define ANIMATION_DURATION 1000 // ms

class Circumference {
  private:
    float center_x;
    float center_y;
    float radius;

    float red;
    float green;
    float blue;

    bool animation_not_started = true;
    std::chrono::time_point<std::chrono::system_clock> animation_start_time;

    // Function to draw a line
    void drawLine(float x1, float y1, float x2, float y2)
    {
      glBegin(GL_LINES);
      glVertex2f(x1, y1);
      glVertex2f(x2, y2);
      glEnd();
    }

  public:
    Circumference(float c_x, float c_y, float radius) {
      this->center_x = c_x;
      this->center_y = c_y;
      this->radius = radius;

      std::srand(std::time(0));
      this->red = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
      this->green = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
      this->blue = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }

    void draw_with_scan_line() {
      if (this->animation_not_started) {
        this->animation_not_started = !this->animation_not_started;
        this->animation_start_time = std::chrono::high_resolution_clock::now();
      }

      glColor3f(this->red, this->green, this->blue);
      auto duration_elapsed = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now() - this->animation_start_time).count()) / ANIMATION_DURATION;

      if (duration_elapsed > 1.0f) duration_elapsed = 1.0f;

      float current_radius = this->radius * duration_elapsed;
      
      for (float y = -current_radius; y <= current_radius; y += 0.001f)
      {
        float x = sqrt(this->radius * this->radius - y * y);
        drawLine(this->center_x - x, this->center_y + y, this->center_x + x, this->center_y + y);
      }

      if (duration_elapsed >= 1.0f) {
        this->animation_not_started = true;
      }
    }

    void draw_radial() {
      if (this->animation_not_started) {
        this->animation_not_started = !this->animation_not_started;
        this->animation_start_time = std::chrono::high_resolution_clock::now();
      }

      glColor3f(this->red, this->green, this->blue);
      auto duration_elapsed = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now() - this->animation_start_time).count()) / ANIMATION_DURATION;

      if (duration_elapsed > 1.0f) duration_elapsed = 1.0f;

      float max_angle = 2.0f * M_PI * duration_elapsed;

      for (float angle = 0.0f; angle <= max_angle; angle += 0.01f) {
        float x = this->center_x + this->radius * cos(angle);
        float y = this->center_y + this->radius * sin(angle);
        drawLine(this->center_x, this->center_y, x, y);
      }

      if (duration_elapsed >= 1.0f) {
        this->animation_not_started = true;
      }
    }
};

// Global variables for circle instances
Circumference c1(0.f, 0.f, 0.3f);
Circumference c2(0.6f, -0.7f, 0.1f);

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  c1.draw_with_scan_line();
  c2.draw_radial();

  glutSwapBuffers();
}

void init()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set orthographic projection
}

void timer(int value)
{
  glutPostRedisplay();
  glutTimerFunc(33, timer, 0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(200, 50);
  glutCreateWindow("Preenchimento de circunferencia otimizado");
  init();
  glutTimerFunc(0, timer, 0);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
