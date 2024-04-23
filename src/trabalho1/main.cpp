/** Trabalho de Implementação 1 - Computação Gráfica
 * @date abril 2024
 * @brief Transformações de translação, escala e rotação 2D
 * 
 * @author [Nome dos participantes]
 * @author ...
 * 
 * @compile:
 * g++ main.cpp -I"../../include/freeglut/include" -L"../../include/freeglut/lib" -lfreeglut -lopengl32  -lglu32 -o ./out/main
 * @execute:
 * ./out/main
 */

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Janela inicial
GLsizei win_width = 600, win_height = 600;
// Limites para as coordenadas do mundo
GLfloat xwc_min = 0.0, xwc_max = 255.0;
GLfloat ywc_min = 0.0, ywc_max = 255.0;

typedef GLfloat Matrix[3][3];
const GLdouble pi = 3.14159;

class Point {
    public:
        GLfloat x, y;
};

Matrix composite_matrix;

void initialize(void);

void set_identity(Matrix matIdent3x3);

/**
 * @brief Multiplica a matriz m1 por matriz m2 e coloca o resultado em m2
 */
void pre_multiply(Matrix m1, Matrix m2);

void translate(GLfloat tx, GLfloat ty);

void rotate(Point pivot_point, GLfloat theta);

void scale(GLfloat sx, GLfloat sy, Point fixed_point);

/**
 * @brief Usa a matriz composta para calcular as transformadas
 */
void transform_vertices(GLint nVerts, Point *verts);

void draw_triangle(Point *vertices);

void draw_square(Point *vertices);

void display();

void reshape_window(GLint new_width, GLint new_height);


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(win_width, win_height);
    glutInitWindowPosition(50, 50);

    /**
     * @todo Colocar as opções de figuras geométricas / operações
     * 
     */


    glutCreateWindow("Transformacoes");
    initialize();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape_window);
    glutMainLoop();
}


void initialize(void) {
    // glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearColor(0.1, 0.1, 0.1, 0.0);
}

void set_identity(Matrix identity_matrix) {
    GLint row, col;
    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            identity_matrix[row][col] = (row == col);
}

void pre_multiply(Matrix m1, Matrix m2) {
    GLint row, col;
    Matrix matTemp;

    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            matTemp[row][col] = m1[row][0] * m2[0][col] + 
                                m1[row][1] * m2[1][col] + 
                                m1[row][2] * m2[2][col];

    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            m2[row][col] = matTemp[row][col];
}

void translate(GLfloat tx, GLfloat ty) {
    Matrix translation_matrix = {{1, 0, tx}, 
                                 {0, 1, ty}, 
                                 {0, 0, 1}};
    pre_multiply(translation_matrix, composite_matrix);
}

void rotate(Point pivot_point, GLfloat theta) {
    GLfloat sin_theta = sin(theta), cos_theta = cos(theta);
    Matrix rotation_matrix = {{cos_theta, -sin_theta, pivot_point.x * (1 - cos_theta) + (pivot_point.y * sin_theta)}, 
                              {sin_theta, cos_theta,  pivot_point.y * (1 - cos_theta) - (pivot_point.x * sin_theta)},
                              {0,         0,          1}};
    pre_multiply(rotation_matrix, composite_matrix);
}

void scale(GLfloat sx, GLfloat sy, Point fixed_point) {
    Matrix scaling_matrix = {{sx, 0,  (1 - sx) * fixed_point.x}, 
                             {0,  sy, (1 - sy) * fixed_point.y},
                             {0,  0,  1}};
    pre_multiply(scaling_matrix, composite_matrix);
}

void transform_vertices(GLint nVerts, Point *verts) {
    GLint k;
    GLfloat temp;
    for (k = 0; k < nVerts; k++)
    {
        temp = composite_matrix[0][0] * verts[k].x + composite_matrix[0][1] * verts[k].y + composite_matrix[0][2];
        verts[k].y = composite_matrix[1][0] * verts[k].x + composite_matrix[1][1] * verts[k].y + composite_matrix[1][2];
        verts[k].x = temp;
    }
}

void draw_triangle(Point *vertices) {
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i < 3; i++)
        glVertex2f(vertices[i].x, vertices[i].y);
    glEnd();
}

void draw_square(Point *vertices) {
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i < 4; i++)
        glVertex2f(vertices[i].x, vertices[i].y);
    glEnd();
}

void display() {
    // Define a posição inicial do triangulo
    GLint num_vertices = 3;
    Point vertices[3] = {{50.0, 25.0}, {150.0, 25.0}, {100.0, 100.0}};
    // Calcula a posição do centróide do triangulo

    /**
     * @todo criar uma função para realizar esse cálculo
     * 
     */
    Point centroid_point;
    GLint k;
    GLfloat x_sum = 0, y_sum = 0;

    for (k = 0; k < num_vertices; k++) {
        x_sum += vertices[k].x;
        y_sum += vertices[k].y;
    }

    centroid_point.x = x_sum / GLfloat(num_vertices);
    centroid_point.y = y_sum / GLfloat(num_vertices);

    // Estabelece parâmetros da transformação geométrica
    Point pivot_point, fixed_point;
    pivot_point = centroid_point;
    fixed_point = centroid_point;
    GLfloat tx = 0.0, ty = 100.0;
    GLfloat sx = 0.5, sy = 0.5;
    GLdouble theta = pi / 2.0;

    glClear(GL_COLOR_BUFFER_BIT);       // limpa a janela de visão (display window)
    glColor3f(0.0, 0.0, 1.0);           // estalebece a cor de preenchimento inicial com o azul
    draw_triangle(vertices);            // Exibe triângulo

    // inicializa a matriz de composição para a identidade
    set_identity(composite_matrix);

    // Constrói a matriz de composição para a sequência de transformações
    scale(sx, sy, fixed_point);
    rotate(pivot_point, theta);
    translate(tx, ty);
    
    // Aplica a matriz de transformação nos vértices do triângulo
    transform_vertices(num_vertices, vertices);
    glColor3f(1.0, 0.0, 0.0);
    draw_triangle(vertices); // Exibe triângulo transformado

    glFlush();
}

void reshape_window(GLint new_width, GLint new_height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwc_min, xwc_max, ywc_min, ywc_max);
    glClear(GL_COLOR_BUFFER_BIT);
}

