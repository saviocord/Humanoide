/*
** Doing CSG with stencil
*/
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>


enum {CSG_HELP};

GLfloat rotX, rotY, rotZ;
int csg_op = CSG_HELP;
GLfloat lightpos[] = {-25.f, 0.f, 50.f, 1.f};

struct Posicao {
    float x, y, z;
    Posicao(float x, float y, float z) : x(x), y(y), z(z) { }
};

void iniHumanoide(){
    Posicao cabeca();
    Posicao tronco();

    Posicao virilha();
    Posicao virilhaD();
    Posicao virilhaE();

    Posicao cotoveloD();
    Posicao maoD();

    Posicao cotoveloE();
    Posicao maoE();

    Posicao joelhoD();
    Posicao calcanharD();

    Posicao joelhoE();
    Posicao calcanharE();
}

void drawBitmapText(char *string,float x,float y,float z)
{
    glPushMatrix();
    glLoadIdentity();
    char *c;
    glRasterPos3f(x, y,z);

    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
    glPopMatrix();
}

void draw() {
    /* clear stencil each time */
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);


    glPushMatrix();
        //glTranslated(-(x/2), 0, 0);
        glRotatef(-45, 0, 1, 0);
        glColor3f(0.0, 0.0, 0.0);
        glPointSize(5);
        glBegin(GL_POINTS);
            glVertex3f(0, 6, 0);//cabeça

            glVertex3f(-3, 4, 0);
            glVertex3f(-2, 4, 0);
            glVertex3f(0, 4, 0);//tronco
            glVertex3f(2, 4, 0);
            glVertex3f(3, 4, 0);

            glVertex3f(0, 0, 0);//virilha
            glVertex3f(1, 0, 0);
            glVertex3f(-1, 0, 0);

            glVertex3f(1, -2, 0);//coxaDireita
            glVertex3f(-1, -2, 0);//coxaEsquerda

            glVertex3f(1, -4, 0);//canelaDireita
            glVertex3f(-1, -4, 0);//canelaEsquerda

            glVertex3f(1, -4, 1);//péDireito
            glVertex3f(-1, -4, 1);//péEsquerdo
        glEnd();
        glBegin(GL_LINES);
           //virilha-tronco
           glVertex3f(0, 0, 0);
           glVertex3f(0, 4, 0);
           //tronco-cabeça
           glVertex3f(0, 4, 0);
           glVertex3f(0, 6, 0);
           //tronco-braçoDireito
           glVertex3f(0, 4, 0);
           glVertex3f(2, 4, 0);
           //braçoDireito-antebraço
           glVertex3f(2, 4, 0);
           glVertex3f(3, 4, 0);
           //tronco-braçoEsquerdo
           glVertex3f(0, 4, 0);
           glVertex3f(-2, 4, 0);
           //braçoEsquerdo-antebraço
           glVertex3f(-2, 4, 0);
           glVertex3f(-3, 4, 0);

           //virilha-inicioPernaDireta
           glVertex3f(0, 0, 0);
           glVertex3f(1, 0, 0);
           //virilha-inicioPernaEsquerda
           glVertex3f(0, 0, 0);
           glVertex3f(-1, 0, 0);
           //inicioPernaDireita-coxaDireita
           glVertex3f(1, 0, 0);
           glVertex3f(1, -2, 0);
           //inicioPernaEsquerda-coxaEsquerda
           glVertex3f(-1, 0, 0);
           glVertex3f(-1, -2, 0);
           //coxaDireita-canelaDireta
           glVertex3f(1, -2, 0);
           glVertex3f(1, -4, 0);
           //coxaEsquerda-canelaEsquerda
           glVertex3f(-1, -2, 0);
           glVertex3f(-1, -4, 0);
           //canelaDireita-péDireto
           glVertex3f(1, -4, 0);
           glVertex3f(1, -4, 1);
           //canelaEsqueda-péEsquedo
           glVertex3f(-1, -4, 0);
           glVertex3f(-1, -4, 1);
       glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

/* special keys, like array and F keys */
void specialKey(int key, int, int) {
    switch(key) {
        case GLUT_KEY_LEFT:
            rotY -= 1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            rotY += 1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            rotX -= 1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            rotX += 1;
            glutPostRedisplay();
            break;
    }
}

void key(unsigned char key, int, int) {
    switch(key) {
        case 'q':
            exit(0);
        case '-':
            rotZ -= 1;
            glutPostRedisplay();
            break;
        case '+':
            rotZ += 1;
            glutPostRedisplay();
            break;
        case 'a':
            rotY -= 1;
            glutPostRedisplay();
            break;
        case 'd':
            rotY += 1;
            glutPostRedisplay();
            break;
        case 'w':
            rotX -= 1;
            glutPostRedisplay();
            break;
        case 's':
            rotX += 1;
            glutPostRedisplay();
            break;
    }
}

void menu(int csgop) {
    csg_op = csgop;
    glutPostRedisplay();
}

void menuCallback(void){

    glutCreateMenu(menu);
    glutAddMenuEntry("Help", CSG_HELP);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void  mouse(int key, int state, int x, int y) {

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_STENCIL|GLUT_DEPTH|GLUT_DOUBLE);
    glutCreateWindow("CSG");
    glClearColor(1, 1, 1, 0);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-10, 10, -10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(draw);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutMouseFunc(mouse);
    menuCallback();

    glEnable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);

    glutMainLoop();

    return 0;
}
