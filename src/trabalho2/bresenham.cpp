#include <GL/glut.h>
#include <algorithm>
#include <cmath>

#define WIDTH 500
#define HEIGHT 500

void draw_line_high(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int step_x = 1;

    if (dx < 0) {
        step_x = -1;
        dx = -dx;
    }

    int d = (2 * dx) - dy;
    int x = x1;

    glBegin(GL_POINTS);
    for (int y = y1; y <= y2; y++) {
        glVertex2i(x, y);
        if (d > 0) {
            d += 2 * (dx - dy);
            x += step_x;
        } else
            d += 2 * dx;
    }
    glEnd();
}

void draw_line_low(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int step_y = 1;

    if (dy < 0) {
        step_y = -1;
        dy = -dy;
    }

    int d = (2 * dy) - dx;
    int y = y1;

    glBegin(GL_POINTS);
    for (int x = x1; x <= x2; x++) {
        glVertex2i(x, y);
        if (d > 0) {
            d += 2 * (dy - dx);
            y += step_y;
        } else
            d += 2 * dy;
    }
    glEnd();
}

void draw_line(int x1, int y1, int x2, int y2) {
    if (abs(y2 - y1) < abs(x2 - x1)) {
        if (x1 > x2) 
            draw_line_low(x2, y2, x1, y1);
        else 
            draw_line_low(x1, y1, x2, y2);
    }
    else {
        if (y1 > y2)
            draw_line_high(x2, y2, x1, y1);
        else
            draw_line_high(x1, y1, x2, y2);
    }
}

/**
 * @brief Desenha os eixos x e y
 */
void draw_axes() {
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.5f);
    for (int i = (int)-(WIDTH / 2); i <= (int)(WIDTH / 2); i += 5) {
        if (std::abs(i) % 25 == 0) {
            glBegin(GL_POINTS);
            glVertex2i(i, 0);
            glEnd();
        }
    }
    for (int i = (int)-(HEIGHT / 2); i <= (int)(HEIGHT / 2); i += 5) {
        if (std::abs(i) % 25 == 0) {
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
    draw_line(0, 0, 200, 100);
    draw_line(0, 0, 100, 200);

    glColor3f(1.0, 0.0, 0.0);
    draw_line(0, 0, -100, 200);
    draw_line(0, 0, -200, 100);

    glColor3f(0.0, 1.0, 0.0);
    draw_line(0, 0, -200, -100);
    draw_line(0, 0, -100, -200);

    glColor3f(1.0, 0.0, 1.0);
    draw_line(0, 0, 200, -100);
    draw_line(0, 0, 100, -200);

    glFlush();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-(WIDTH / 2), (WIDTH / 2), -(HEIGHT / 2), (HEIGHT / 2));
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Retas Otimizadas");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
