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

static int cabecaRot = 0;

struct Posicao {
    float x, y, z;
    Posicao(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) { }
};

Posicao cabeca(0, 6, 0);
Posicao tronco(0, 4, 0);

Posicao virilha(0, 0, 0);
Posicao virilhaD(1, 0, 0);
Posicao virilhaE(-1, 0, 0);

Posicao cotoveloD(2, 4, 0);
Posicao maoD(3, 4, 0);

Posicao cotoveloE(-2, 4, 0);
Posicao maoE(-3, 4, 0);

Posicao joelhoD(1, -2, 0);
Posicao tornozeloD(1, -4, 0);
Posicao peD(1, -4, 1);

Posicao joelhoE(-1, -2, 0);
Posicao tornozeloE(-1, -4, 0);
Posicao peE(-1, -4, 1);


void iniHumanoide(){

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
        glPointSize(8);
        glLineWidth(3);

            glPushMatrix();
                glTranslatef(tronco.x, tronco.y, tronco.z);
                glRotatef ((GLfloat) cabecaRot, 0.0, 0.0, 1.0);
                glTranslatef(-tronco.x, -tronco.y, -tronco.z);
                glBegin(GL_POINTS);
                    glVertex3f(cabeca.x, cabeca.y, cabeca.z);
                glEnd();
            glPopMatrix();
        glBegin(GL_POINTS);
//            glVertex3f(cabeca.x, cabeca.y, cabeca.z);

            glVertex3f(tronco.x, tronco.y, tronco.z);
            glVertex3f(virilha.x, virilha.y, virilha.z);

            glVertex3f(virilhaD.x, virilhaD.y, virilhaD.z);
            glVertex3f(virilhaE.x, virilhaE.y, virilhaE.z);

            glVertex3f(joelhoD.x, joelhoD.y, joelhoD.z);
            glVertex3f(joelhoE.x, joelhoE.y, joelhoE.z);

            glVertex3f(tornozeloD.x, tornozeloD.y, tornozeloD.z);
            glVertex3f(tornozeloE.x, tornozeloE.y, tornozeloE.z);

            glVertex3f(peD.x, peD.y, peD.z);
            glVertex3f(peE.x, peE.y, peE.z);

            glVertex3f(cotoveloD.x, cotoveloD.y, cotoveloD.z);
            glVertex3f(cotoveloE.x, cotoveloE.y, cotoveloE.z);

            glVertex3f(maoD.x, maoD.y, maoD.z);
            glVertex3f(maoE.x, maoE.y, maoE.z);
        glEnd();

        glPushMatrix();
            glTranslatef(tronco.x, tronco.y, tronco.z);
            glRotatef ((GLfloat) cabecaRot, 0.0, 0.0, 1.0);
            glTranslatef(-tronco.x, -tronco.y, -tronco.z);
            glBegin(GL_LINES);
                glVertex3f(cabeca.x, cabeca.y, cabeca.z);
                glVertex3f(tronco.x, tronco.y, tronco.z);
            glEnd();
        glPopMatrix();

        glBegin(GL_LINES);
//            glVertex3f(cabeca.x, cabeca.y, cabeca.z);
//            glVertex3f(tronco.x, tronco.y, tronco.z);

            glVertex3f(tronco.x, tronco.y, tronco.z);
            glVertex3f(virilha.x, virilha.y, virilha.z);

            glVertex3f(virilha.x, virilha.y, virilha.z);
            glVertex3f(virilhaD.x, virilhaD.y, virilhaD.z);

            glVertex3f(virilha.x, virilha.y, virilha.z);
            glVertex3f(virilhaE.x, virilhaE.y, virilhaE.z);

            glVertex3f(virilhaD.x, virilhaD.y, virilhaD.z);
            glVertex3f(joelhoD.x, joelhoD.y, joelhoD.z);

            glVertex3f(virilhaE.x, virilhaE.y, virilhaE.z);
            glVertex3f(joelhoE.x, joelhoE.y, joelhoE.z);

            glVertex3f(joelhoD.x, joelhoD.y, joelhoD.z);
            glVertex3f(tornozeloD.x, tornozeloD.y, tornozeloD.z);

            glVertex3f(joelhoE.x, joelhoE.y, joelhoE.z);
            glVertex3f(tornozeloE.x, tornozeloE.y, tornozeloE.z);

            glVertex3f(tornozeloD.x, tornozeloD.y, tornozeloD.z);
            glVertex3f(peD.x, peD.y, peD.z);

            glVertex3f(tornozeloE.x, tornozeloE.y, tornozeloE.z);
            glVertex3f(peE.x, peE.y, peE.z);

            glVertex3f(tronco.x, tronco.y, tronco.z);
            glVertex3f(cotoveloD.x, cotoveloD.y, cotoveloD.z);

            glVertex3f(tronco.x, tronco.y, tronco.z);
            glVertex3f(cotoveloE.x, cotoveloE.y, cotoveloE.z);

            glVertex3f(cotoveloD.x, cotoveloD.y, cotoveloD.z);
            glVertex3f(maoD.x, maoD.y, maoD.z);

            glVertex3f(cotoveloE.x, cotoveloE.y, cotoveloE.z);
            glVertex3f(maoE.x, maoE.y, maoE.z);

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
        case '+':
            cabecaRot = (cabecaRot + 5) % 360;
            std::cout<<"+"<<std::endl;
            break;
        case '-':
            cabecaRot = (cabecaRot - 5) % 360;
            std::cout<<"-"<<std::endl;
            break;
    }
    draw();
}

void mouse(int botao, int estado, int x, int y){
    std::cout<<" x:"<<x<<" y:"<<y<<" estado:"<<estado<<" botao:"<<botao<<std::endl;
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

    glEnable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);

    glutMainLoop();

    return 0;
}
