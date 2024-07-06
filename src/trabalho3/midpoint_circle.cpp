#include <GL/glut.h>

// g++ midpoint_circle.cpp -I"../../include/freeglut/include" -L"../../include/freeglut/lib" -lfreeglut -lopengl32 -lglu32 -o ./out/midpoint_circle
// ./out/midpoint_circle

typedef struct point {
    GLint x, y;
} Point;


void draw_pixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plot_circle_points(GLint xc, GLint yc, Point circle_point) {
    draw_pixel(xc + circle_point.x, yc + circle_point.y);
    draw_pixel(xc - circle_point.x, yc + circle_point.y);
    draw_pixel(xc + circle_point.x, yc - circle_point.y);
    draw_pixel(xc - circle_point.x, yc - circle_point.y);
    draw_pixel(xc + circle_point.y, yc + circle_point.x);
    draw_pixel(xc - circle_point.y, yc + circle_point.x);
    draw_pixel(xc + circle_point.y, yc - circle_point.x);
    draw_pixel(xc - circle_point.y, yc - circle_point.x);
}

void midpoint_circle(GLint xc, GLint yc, GLint radius) {
    // Valores iniciais
    Point point = {.x = 0, .y = radius}; // Coordenadas do ponto (0,r)
    GLint d = 1 - radius;                // Variável de decisão (radius inteiro)
    // GLfloat d = 5/4 - radius;         // Variável de decisão (radius real)

    // Plota o ponto inicial de cada quadrante
    plot_circle_points(xc, yc, point);

    // Calcula o próximo ponto e plota em cada octante
    while (point.x < point.y) {
        if (d < 0) // Seleciona o ponto LESTE
            d += 2 * point.x + 3;
        else { // Seleciona o ponto SUDOESTE
            d += 2 * (point.x - point.y) + 5;
            point.y--;
        }
        point.x++;
        plot_circle_points(xc, yc, point);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    midpoint_circle(0, 0, 520);
    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1000.0, 1000.0, -1000.0, 1000.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Algoritmo Midpoint Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}



