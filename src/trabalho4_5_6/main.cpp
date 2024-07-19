#include <GL/glut.h>

GLfloat angle, fAspect;
int projectionType = 1; // 0 para ortogonal, 1 para perspectiva
bool wireframe_mode = false;
bool backface_ativado = true;

// Variáveis para rotação com o mouse
bool mouseDown = false;
float xRot = 0.0f, yRot = 0.0f;
float xDiff = 0.0f, yDiff = 0.0f;

void Desenha(void)
{
  // Limpa a janela e o depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.0f, 0.0f, 1.0f);

  glLoadIdentity();
  gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);

  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  if (wireframe_mode)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glBegin(GL_QUADS);

  // Face posterior - Azul
  // glColor3f(0.0, 0.0, 1.0);
  // glNormal3f(0.0, 0.0, 1.0); // Normal da face
  // glVertex3f(40.0, 40.0, 40.0);
  // glVertex3f(-40.0, 40.0, 40.0);
  // glVertex3f(-40.0, -40.0, 40.0);
  // glVertex3f(40.0, -40.0, 40.0);

  // // Face frontal - Verde
  if (backface_ativado) {
    glColor3f(0.0, 1.0, 0.0);
    glNormal3f(0.0, 0.0, -1.0); // Normal da face
    glVertex3f(40.0, 40.0, -40.0);
    glVertex3f(40.0, 0.0, -40.0);
    glVertex3f(-40.0, 0.0, -40.0);
    glVertex3f(-40.0, 40.0, -40.0);
  }
  
  glColor3f(0.0, 1.0, 0.0);
  glNormal3f(0.0, 0.0, 1.0); // Normal da face
  glVertex3f(40.0, 0.0, -40.0);
  glVertex3f(40.0, -40.0, -40.0);
  glVertex3f(-40.0, -40.0, -40.0);
  glVertex3f(-40.0, 0.0, -40.0);

  // Face lateral esquerda - Vermelho
  glColor3f(1.0, 0.0, 0.0);
  glNormal3f(-1.0, 0.0, 0.0); // Normal da face
  glVertex3f(-40.0, 40.0, 40.0);
  glVertex3f(-40.0, 40.0, -40.0);
  glVertex3f(-40.0, -40.0, -40.0);
  glVertex3f(-40.0, -40.0, 40.0);

  // Face lateral direita - Amarelo
  glColor3f(1.0, 1.0, 0.0);
  glNormal3f(1.0, 0.0, 0.0); // Normal da face
  glVertex3f(40.0, 40.0, 40.0);
  glVertex3f(40.0, -40.0, 40.0);
  glVertex3f(40.0, -40.0, -40.0);
  glVertex3f(40.0, 40.0, -40.0);

  // Face superior - Magenta
  glColor3f(1.0, 0.0, 1.0);
  glNormal3f(0.0, 1.0, 0.0); // Normal da face
  glVertex3f(-40.0, 40.0, -40.0);
  glVertex3f(-40.0, 40.0, 40.0);
  glVertex3f(40.0, 40.0, 40.0);
  glVertex3f(40.0, 40.0, -40.0);

  // Face inferior - Ciano
  glColor3f(0.0, 1.0, 1.0);
  glNormal3f(0.0, -1.0, 0.0); // Normal da face
  glVertex3f(-40.0, -40.0, -40.0);
  glVertex3f(40.0, -40.0, -40.0);
  glVertex3f(40.0, -40.0, 40.0);
  glVertex3f(-40.0, -40.0, 40.0);

  glEnd();

  if (wireframe_mode)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
  GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
  GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0};    // "cor"
  GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
  GLfloat posicaoLuz[4] = {0.0, 50.0, 50.0, 1.0};
  
  GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
  GLint especMaterial = 60;

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
  glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

  glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
  glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
  glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  angle = 45;
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projectionType == 0)
  {
    // Projeção ortogonal
    GLdouble left, right, bottom, top;
    bottom = -100.0;
    left = bottom;
    right = top = bottom * -1.0;

    glOrtho(left, right, bottom, top, -200.0, 300.0);
  }
  else
  {
    // Projeção perspectiva
    gluPerspective(angle, fAspect, 0.1, 500);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
  if (h == 0)
    h = 1;
  glViewport(0, 0, w, h);
  fAspect = (GLfloat)w / (GLfloat)h;
  EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos de movimento do mouse
void GerenciaMovimentoMouse(int x, int y)
{
  if (mouseDown)
  {
    yRot = (x - xDiff);
    xRot = (y - yDiff);
    glutPostRedisplay();
  }
}

// Função callback chamada para gerenciar eventos de clique do mouse
void GerenciaCliqueMouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    mouseDown = true;
    xDiff = x - yRot;
    yDiff = y - xRot;
  }
  else
  {
    mouseDown = false;
  }

  if (button == 3 || button == 4) {
    if (state == GLUT_UP)
      return;
    
    button == 3 ? angle -= 5.f : angle += 5.f;
    angle < 5.f ? angle = 5.f : angle > 175.f ? angle = 175.f : angle;

    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
  }
    
}

// Função callback chamada para gerenciar eventos do teclado
void GerenciaTeclado(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'p':
  case 'P':
    angle = 45.f;
    projectionType = 1; // Projeção perspectiva
    break;
    
  case 'o':
  case 'O':
    projectionType = 0; // Projeção ortogonal
    break;
  
  case 'w':
  case 'W':
    wireframe_mode = !wireframe_mode;
    break;

  case 'b':
    backface_ativado = !backface_ativado;
    break;
  }
  EspecificaParametrosVisualizacao();
  glutPostRedisplay();
}

// Programa Principal
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(900, 700);
  glutCreateWindow("Projeção ortogonal e perspectiva e back-face detection");
  glutDisplayFunc(Desenha);
  glutReshapeFunc(AlteraTamanhoJanela);
  glutMouseFunc(GerenciaCliqueMouse);
  glutMotionFunc(GerenciaMovimentoMouse);
  glutKeyboardFunc(GerenciaTeclado);
  Inicializa();
  glutMainLoop();
}
