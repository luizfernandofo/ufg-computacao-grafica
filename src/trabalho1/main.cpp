/** 
 * Trabalho de Implementação 1 - Computação Gráfica
 * @date abril 2024
 * @brief Transformações de translação, escala e rotação 2D
 * 
 * @author Eduardo Leocadio Alvarenga
 * @author João Felipe Carlos Rodrigues
 * @author Laura Martins Vieira Gonçalves
 * @author Luiz Fernando de Freitas Oliveira
 * @author Marcos "Regittos" Reges Mota
 * @author Pedro Augusto Serafim Belo
 * @author Pedro Paulo Pereira Souza
 * 
 * @compile:
 * g++ main.cpp -I"../../include/freeglut/include" -L"../../include/freeglut/lib" -lfreeglut -lopengl32 -lglu32 -o ./out/main.exe
 * @execute:
 * ./out/main.exe
 */

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <array>

typedef GLfloat Matrix[3][3];
const GLdouble pi = 3.14159;

// Matriz de transformação
Matrix transformation_matrix;

// Ponto de duas dimensões
class Point {
    public:
        GLfloat x, y;
};

// Tamanho da janela
GLsizei win_width = 800, win_height = 800;
// Posição inicial da janela
GLint win_position_x = 400, win_position_y = 50;
// Limites para as coordenadas do mundo
GLfloat xwc_min = 0.0, xwc_max = 400.0;
GLfloat ywc_min = 0.0, ywc_max = 400.0;

/**
 * @brief Inicializa a janela com as cores de fundo definidas
 */
void initialize(void);

/**
 * @brief Redimensiona a janela
 */
void reshape_window(GLint new_width, GLint new_height);

/**
 * @brief Transforma a matriz em identidade
 */
void set_identity(Matrix matrix);

/**
 * @brief Multiplica a matriz m1 pela matriz m2 e coloca o resultado em m2
 */
void multiply_matrices(Matrix m1, Matrix m2);

/**
 * @brief Realiza a operação de translação
 * 
 * @param tx deslocamento no eixo x
 * @param ty deslocamento no eixo y
 */
void translate(GLfloat tx, GLfloat ty);

/**
 * @brief Realiza a operação de rotação
 * 
 * @param pivot_point ponto em torno do qual a figura será rotacionada
 * @param theta ângulo de rotação em radianos
 */
void rotate(Point pivot_point, GLfloat theta);

/**
 * @brief Realiza a operação de escala
 * 
 * @param sx fator de escala no eixo x
 * @param sy fator de escala no eixo y
 * @param fixed_point ponto em torno do qual a escala será aplicada
 */
void scale(GLfloat sx, GLfloat sy, Point fixed_point);

/**
 * @brief Usa a matriz de transformação para calcular as transformações
 */
void transform_vertices(GLint num_vertices, Point *vertices);

/**
 * @brief Desenha um triângulo
 * @param vertices vértices do triângulo
 */
void draw_triangle(Point *vertices);

/**
 * @brief Desenha um quadrilátero
 * @param vertices vértices do quadrilátero
 */
void draw_square(Point *vertices);

/**
 * @brief Calcula o ponto central de uma figura e o retorna
 */
Point centroid(Point *vertices, int num_vertices);

/**
 * @brief Exibe as figuras na janela
 */
void display();

// Função principal
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(win_width, win_height);
    glutInitWindowPosition(win_position_x, win_position_y);
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

void reshape_window(GLint new_width, GLint new_height) {
    // Redimensiona a janela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwc_min, xwc_max, ywc_min, ywc_max);
    glClear(GL_COLOR_BUFFER_BIT);
}

void set_identity(Matrix matrix) {
    // Transforma a matriz em identidade
    GLint row, col;
    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            matrix[row][col] = (row == col);
}

void multiply_matrices(Matrix m1, Matrix m2) {
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
    // tx: deslocamento no eixo x
    // ty: deslocamento no eixo y
    Matrix translation_matrix = {{1, 0, tx}, 
                                 {0, 1, ty}, 
                                 {0, 0, 1}};
    multiply_matrices(translation_matrix, transformation_matrix);
}

void rotate(Point pivot_point, GLfloat theta) {
    // Realiza a operação de rotação
    // pivot_point: ponto em torno do qual a figura será rotacionada
    // theta: ângulo de rotação em radianos
    GLfloat sin_theta = sin(theta), cos_theta = cos(theta);
    Matrix rotation_matrix = {{cos_theta, -sin_theta, pivot_point.x * (1 - cos_theta) + (pivot_point.y * sin_theta)}, 
                              {sin_theta, cos_theta,  pivot_point.y * (1 - cos_theta) - (pivot_point.x * sin_theta)},
                              {0,         0,          1}};
    multiply_matrices(rotation_matrix, transformation_matrix);
}

void scale(GLfloat sx, GLfloat sy, Point fixed_point) {
    // Realiza a operação de escala
    // sx: fator de escala no eixo x
    // sy: fator de escala no eixo y
    // fixed_point: ponto em torno do qual a escala será aplicada
    Matrix scaling_matrix = {{sx, 0,  (1 - sx) * fixed_point.x}, 
                             {0,  sy, (1 - sy) * fixed_point.y},
                             {0,  0,  1}};
    multiply_matrices(scaling_matrix, transformation_matrix);
}

void transform_vertices(GLint num_vertices, Point *vertices) {
    // Aplica todas as transformações da matriz no conjunto de vértices
    GLfloat temp;
    for (GLint i = 0; i < num_vertices; i++) {
        temp = transformation_matrix[0][0] * vertices[i].x + transformation_matrix[0][1] * vertices[i].y + transformation_matrix[0][2];
        vertices[i].y = transformation_matrix[1][0] * vertices[i].x + transformation_matrix[1][1] * vertices[i].y + transformation_matrix[1][2];
        vertices[i].x = temp;
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

Point centroid(Point *vertices, int num_vertices) {
    // Calcula o ponto central de uma figura
    GLfloat x_sum = 0, y_sum = 0;
    Point centroid;

    for (int i = 0; i < num_vertices; i++) {
        x_sum += vertices[i].x;
        y_sum += vertices[i].y;
    }
    
    centroid.x = x_sum / GLfloat(num_vertices);
    centroid.y = y_sum / GLfloat(num_vertices);

    return centroid;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpa a janela de visão (display window)
    GLfloat tx, ty, sx, sy, theta;

    /*
     * TRIÂNGULO
     */

    // Define a posição inicial do triângulo
    Point triangle[] = {{220.0, 50.0}, {260.0, 120.0}, {300.0, 50.0}};
    // Calcula o ponto central do triângulo
    Point centroid_triangle = centroid(triangle, 3);
    // Inicializa a matriz de composições como sendo uma matriz identidade
    set_identity(transformation_matrix);

    // Exibe o triângulo inicialmente (azul)
    glColor3f(0.0, 0.0, 1.0);
    draw_triangle(triangle);

    // Define os parâmetros da transformação geométrica
    theta = pi / 2.0;       // Rotação
    tx = -50.0; ty = 150.0; // Translação
    sx = 0.5; sy = 0.5;     // Escala

    // Constrói a matriz de composição para a sequência de transformações
    rotate(centroid_triangle, theta);
    translate(tx, ty);
    scale(sx, sy, centroid_triangle);
    
    // Aplica a matriz de transformação nos vértices do triângulo
    transform_vertices(3, triangle);

    // Exibe o triângulo após as transformações (vermelho)
    glColor3f(1.0, 0.0, 0.0);
    draw_triangle(triangle);

    /*
     * QUADRADO
     */

    // Define a posição inicial do quadrado
    Point square[] = {{50.0, 50.0}, {50.0, 90.0}, {90.0, 90.0}, {90.0, 50.0}};
    // Calcula o ponto central do quadrado
    Point centroid_square = centroid(square, 4);
    // Inicializa a matriz de composições como sendo uma matriz identidade
    set_identity(transformation_matrix);

    // Exibe o quadrado inicialmente (azul)
    glColor3f(0.0, 0.0, 1.0);
    draw_square(square);

    // Define os parâmetros da transformação geométrica
    sx = 2.0; sy = 2.0;     // Escala
    theta = pi / 4.0;       // Rotação
    tx = 80.0; ty = 150.0;  // Translação

    // Aplica a sequência de transformações Constrói a matriz de composição para a sequência de transformações
    scale(sx, sy, centroid_square);
    rotate(centroid_square, theta);
    translate(tx, ty);
    
    // Aplica a matriz de transformação nos vértices do quadrado
    transform_vertices(4, square);

    // Exibe o quadrado após as transformações (vermelho)
    glColor3f(1.0, 0.0, 0.0);
    draw_square(square);

    glFlush(); // Esvazia os buffers para que os comandos sejam executados
}
