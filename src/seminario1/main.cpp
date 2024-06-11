#include <GL/glut.h>
#include <algorithm>
#include <cmath>
#include "graham_scan.hpp"
#include <vector>

// g++ -Wall ./*.cpp -I"../../include/freeglut/include" -L"../../include/freeglut/lib" -lfreeglut -lopengl32  -lglu32 -lm -o ./out/main

#define WIDTH 500
#define HEIGHT 500
#define NUM_POINTS 5

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


void draw_convex_hull(vector<Point> points) {
    int i, num_points = points.size();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (i = 0; i < num_points - 1; i++) {
        glVertex2d(points[i].x, points[i].y);
        glVertex2d(points[i + 1].x, points[i + 1].y);
    }
    glVertex2d(points[i].x, points[i].y);
    glVertex2d(points[0].x, points[0].y);
    glEnd();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    vector<Point> result_points;
    Point points[NUM_POINTS];

    // Desenha os eixos x e y
    draw_axes();

    points[0].x = 30;
    points[0].y = 40;

    points[1].x = 60;
    points[1].y = 40;

    points[2].x = 150;
    points[2].y = 180;

    points[3].x = 100;
    points[3].y = 10;

    points[4].x = 120;
    points[4].y = 130;

    glPointSize(7); // Tamanho do ponto
    glBegin(GL_POINTS);
        glColor3f(0.0, 0.0, 1.0); // Cor do ponto
        for (int i = 0; i < NUM_POINTS; i++) {
            glVertex2i(points[i].x, points[i].y);
        }
    glEnd();

    result_points = convexHull(points, NUM_POINTS);

    glPointSize(7); // Tamanho do ponto
    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0); // Cor do ponto
        for (auto p : result_points) {
            glVertex2i(p.x, p.y);
        }
    glEnd();

    draw_convex_hull(result_points);
    
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
    glutCreateWindow("Fecho convexo 2D");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
