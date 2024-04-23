/** 
 * Trabalho de Implementação 1 - Computação Gráfica
 * @date abril 2024
 * @brief Transformações de translação, escala e rotação 2D
 * 
 * @author Eduardo
 * @author João
 * @author Laura
 * @author Luiz Fernando de Freitas Oliveira
 * @author Marcos "Regittos" Reges Mota
 * @author Pedro Augusto Serafim Belo
 * @author Pedro Paulo Pereira Souza
 * 
 * @compile:
 * g++ main.cpp -I"../../include/freeglut/include" -L"../../include/freeglut/lib" -lfreeglut -lopengl32  -lglu32 -o ./out/main.exe
 * @execute:
 * ./out/main.exe
 */

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <array>

typedef GLfloat Matrix[3][3];
const GLdouble pi = 3.14159;

// Matriz de composições
Matrix composite_matrix;

class Point {
    public:
        GLfloat x, y;
};

// Janela inicial
GLsizei win_width = 600, win_height = 600;
// Limites para as coordenadas do mundo
GLfloat xwc_min = 0.0, xwc_max = 300.0;
GLfloat ywc_min = 0.0, ywc_max = 300.0;

/**
 * @brief Inicializa a janela com as cores de fundo definidas
 */
void initialize(void);

/**
 * @brief Transforma a matriz em identidade
 */
void set_identity(Matrix matrix);

/**
 * @brief Multiplica a matriz m1 pela matriz m2 e coloca o resultado em m2
 */
void pre_multiply(Matrix m1, Matrix m2);

/**
 * @brief Realiza a operação de translação
 * 
 * @param tx 
 * @param ty 
 */
void translate(GLfloat tx, GLfloat ty);

/**
 * @brief 
 * 
 * @param pivot_point 
 * @param theta 
 */
void rotate(Point pivot_point, GLfloat theta);

/**
 * @brief 
 * 
 * @param sx 
 * @param sy 
 * @param fixed_point 
 */
void scale(GLfloat sx, GLfloat sy, Point fixed_point);

/**
 * @brief Usa a matriz composta para calcular as transformadas
 */
void transform_vertices(GLint num_vertices, Point *vertices);

/**
 * @brief 
 * 
 * @param vertices 
 */
void draw_triangle(Point *vertices);

/**
 * @brief 
 * 
 * @param vertices 
 */
void draw_square(Point *vertices);

/**
 * @brief 
 * 
 */
void display();

/**
 * @brief 
 * 
 * @param new_width 
 * @param new_height 
 */
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
    // Muda a cor do fundo
    glClearColor(0.1, 0.1, 0.1, 0.0);
}

void set_identity(Matrix matrix) {
    // Transforma a matriz em identidade
    GLint row, col;
    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            matrix[row][col] = (row == col);
}

void pre_multiply(Matrix m1, Matrix m2) {
    // Realiza a mutiplicação de matrizes
    // m2 = m1 * m2
    GLint row, col;
    Matrix temp_matrix;

    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            temp_matrix[row][col] = m1[row][0] * m2[0][col] + 
                                m1[row][1] * m2[1][col] + 
                                m1[row][2] * m2[2][col];

    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            m2[row][col] = temp_matrix[row][col];
}

void translate(GLfloat tx, GLfloat ty) {
    // Realiza a operação de translação
    Matrix translation_matrix = {{1, 0, tx}, 
                                 {0, 1, ty}, 
                                 {0, 0, 1}};
    pre_multiply(translation_matrix, composite_matrix);
}

void rotate(Point pivot_point, GLfloat theta) {
    // Realiza a operação de rotação
    GLfloat sin_theta = sin(theta), cos_theta = cos(theta);
    Matrix rotation_matrix = {{cos_theta, -sin_theta, pivot_point.x * (1 - cos_theta) + (pivot_point.y * sin_theta)}, 
                              {sin_theta, cos_theta,  pivot_point.y * (1 - cos_theta) - (pivot_point.x * sin_theta)},
                              {0,         0,          1}};
    pre_multiply(rotation_matrix, composite_matrix);
}

void scale(GLfloat sx, GLfloat sy, Point fixed_point) {
    // Realiza a operação de escala
    Matrix scaling_matrix = {{sx, 0,  (1 - sx) * fixed_point.x}, 
                             {0,  sy, (1 - sy) * fixed_point.y},
                             {0,  0,  1}};
    pre_multiply(scaling_matrix, composite_matrix);
}

void transform_vertices(GLint num_vertices, Point *vertices) {
    // Aplica todas as transformações da matriz no conjunto de vértices
    GLint k;
    GLfloat temp;
    for (k = 0; k < num_vertices; k++) {
        temp = composite_matrix[0][0] * vertices[k].x + composite_matrix[0][1] * vertices[k].y + composite_matrix[0][2];
        vertices[k].y = composite_matrix[1][0] * vertices[k].x + composite_matrix[1][1] * vertices[k].y + composite_matrix[1][2];
        vertices[k].x = temp;
    }
}

void draw_triangle(Point *vertices) {
    // Desenha um triângulo
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i < 3; i++)
        glVertex2f(vertices[i].x, vertices[i].y);
    glEnd();
}

void draw_square(Point *vertices) {
    // Desenha um quadrilátero
    glBegin(GL_QUADS);
    for (GLint i = 0; i < 4; i++)
        glVertex2f(vertices[i].x, vertices[i].y);
    glEnd();
}

Point centroid(Point * vertices, int num_vertices) {
    GLfloat x_sum = 0, y_sum = 0;
    Point centroid;

    for (int k = 0; k < num_vertices; k++) {
        x_sum += vertices[k].x;
        y_sum += vertices[k].y;
    }
    
    centroid.x = x_sum / GLfloat(num_vertices);
    centroid.y = y_sum / GLfloat(num_vertices);

    return centroid;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);   // Limpa a janela de visão (display window)
    GLfloat tx, ty, sx, sy, theta;

    // Define a posição inicial do triângulo
    Point triangle[] = {{50.0, 25.0}, {150.0, 25.0}, {100.0, 100.0}};
    // Calcula o ponto central do triângulo
    Point centroid_triangle = centroid(triangle, 3);
    // "Reconstrói" a matriz de composições
    set_identity(composite_matrix);

    // Define os parâmetros da transformação geométrica
    tx = 0.0; ty = 100.0;
    sx = 0.5; sy = 0.5;
    theta = pi / 2.0;

    // Exibe o triângulo inicialmente (azul)
    glColor3f(0.0, 0.0, 1.0);
    draw_triangle(triangle);


    // Constrói a matriz de composição para a sequência de transformações
    scale(sx, sy, centroid_triangle);
    rotate(centroid_triangle, theta);
    translate(tx, ty);
    
    // Aplica a matriz de transformação nos vértices do triângulo
    transform_vertices(3, triangle);

    glColor3f(1.0, 0.0, 0.0);
    draw_triangle(triangle); // Exibe triângulo transformado
    set_identity(composite_matrix);

    // ---------------

    // Define a posição inicial do quadrado
    Point square[] = {{50.0, 50.0}, {50.0, 80.0}, {80.0, 80.0}, {80.0, 50.0}};
    // Calcula o ponto central do quadrado
    Point centroid_square = centroid(square, 4);

    // Define os parâmetros da transformação geométrica
    tx = 0.0; ty = 100.0;
    sx = 0.5; sy = 0.5;
    theta = pi / 2.0;

    // glClear(GL_COLOR_BUFFER_BIT);       // Limpa a janela de visão (display window)
    glColor3f(0.0, 0.0, 1.0);           // Estalebece a cor de preenchimento inicial com o azul
    draw_square(square);            // Exibe quadrado

    // Constrói a matriz de composição para a sequência de transformações
    scale(sx, sy, centroid_square);
    rotate(centroid_square, theta);
    translate(tx, ty);
    
    // Aplica a matriz de transformação nos vértices do quadrado
    transform_vertices(4, square);

    glColor3f(1.0, 0.0, 0.0);
    draw_square(square); // Exibe quadrado transformado

    glFlush();
}

void reshape_window(GLint new_width, GLint new_height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwc_min, xwc_max, ywc_min, ywc_max);
    glClear(GL_COLOR_BUFFER_BIT);
}
