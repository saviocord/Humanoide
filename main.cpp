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

static int cabecaRot = 0, cotoveloERot = 0, maoERot = 0, cotoveloDRot = 0, maoDRot = 0, troncoRot = 0;
static int virilhaDRot = 0, virilhaERot = 0,joelhoERot = 0, joelhoDRot = 0, tornozeloERot = 0, tornozeloDRot = 0, peERot = 0, peDRot = 0;

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

void aplicaRotacao(Posicao parte, int rotacao)
{
    glTranslatef(parte.x, parte.y, parte.z);
    glRotatef ((GLfloat) rotacao, 0.0, 0.0, 1.0);
    glTranslatef(-parte.x, -parte.y, -parte.z);
}

void desenhaPonto(Posicao parte)
{
    glPushMatrix();
    glBegin(GL_POINTS);
    glVertex3f(parte.x, parte.y, parte.z);
    glEnd();
    glPopMatrix();
}

void desenhaLinha(Posicao parteIni, Posicao parteFim)
{
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3f(parteIni.x, parteIni.y, parteIni.z);
    glVertex3f(parteFim.x, parteFim.y, parteFim.z);
    glEnd();
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
    // glTranslatef(virilha.x, virilha.y, virilha.z);
    // glRotatef ((GLfloat) troncoRot, 0.0, 0.0, 1.0);
    // glTranslatef(-virilha.x, -virilha.y, -virilha.z);
    aplicaRotacao(virilha, troncoRot);
    // glPushMatrix();
    // glBegin(GL_POINTS);
    // glVertex3f(tronco.x, tronco.y, tronco.z);
    // glEnd();
    // glPopMatrix();
    desenhaPonto(tronco);

    glPushMatrix();
    // glTranslatef(tronco.x, tronco.y, tronco.z);
    // glRotatef ((GLfloat) cabecaRot, 0.0, 0.0, 1.0);
    // glTranslatef(-tronco.x, -tronco.y, -tronco.z);
    aplicaRotacao(tronco, cabecaRot);
    // glBegin(GL_POINTS);
    // glVertex3f(cabeca.x, cabeca.y, cabeca.z);
    // glEnd();
    desenhaPonto(cabeca);
    glPopMatrix();

    glPushMatrix();
    // glTranslatef(tronco.x, tronco.y, tronco.z);
    // glRotatef ((GLfloat) cotoveloERot, 0.0, 0.0, 1.0);
    // glTranslatef(-tronco.x, -tronco.y, -tronco.z);
    aplicaRotacao(tronco, cotoveloERot);
    // glPushMatrix();
    // glBegin(GL_POINTS);
    // glVertex3f(cotoveloE.x, cotoveloE.y, cotoveloE.z);
    // glEnd();
    // glPopMatrix();
    desenhaPonto(cotoveloE);

    // glTranslatef(cotoveloE.x, cotoveloE.y, cotoveloE.z);
    // glRotatef ((GLfloat) maoERot, 0.0, 0.0, 1.0);
    // glTranslatef(-cotoveloE.x, -cotoveloE.y, -cotoveloE.z);
    aplicaRotacao(cotoveloE, maoERot);
    // glPushMatrix();
    // glBegin(GL_POINTS);
    // glVertex3f(maoE.x, maoE.y, maoE.z);
    // glEnd();
    // glPopMatrix();
    desenhaPonto(maoE);
    glPopMatrix();

    glPushMatrix();
    // glTranslatef(tronco.x, tronco.y, tronco.z);
    // glRotatef ((GLfloat) cotoveloDRot, 0.0, 0.0, 1.0);
    // glTranslatef(-tronco.x, -tronco.y, -tronco.z);
    aplicaRotacao(tronco, cotoveloDRot);
    // glPushMatrix();
    // glBegin(GL_POINTS);
    // glVertex3f(cotoveloD.x, cotoveloD.y, cotoveloD.z);
    // glEnd();
    // glPopMatrix();
    desenhaPonto(cotoveloD);

    // glTranslatef(cotoveloD.x, cotoveloD.y, cotoveloD.z);
    // glRotatef ((GLfloat) maoDRot, 0.0, 0.0, 1.0);
    // glTranslatef(-cotoveloD.x, -cotoveloD.y, -cotoveloD.z);
    aplicaRotacao(cotoveloD, maoDRot);
    // glPushMatrix();
    // glBegin(GL_POINTS);
    // glVertex3f(maoD.x, maoD.y, maoD.z);
    // glEnd();
    // glPopMatrix();
    desenhaPonto(maoD);
    glPopMatrix();
    glPopMatrix();


    glBegin(GL_POINTS);
    glVertex3f(virilha.x, virilha.y, virilha.z);
    glEnd();

    glPushMatrix();
    // glTranslatef(virilha.x, virilha.y, virilha.z);
    // glRotatef ((GLfloat) virilhaDRot, 0.0, 0.0, 1.0);
    // glTranslatef(-virilha.x, -virilha.y, -virilha.z);
    aplicaRotacao(virilha, virilhaDRot);
    // glPushMatrix();
    // glBegin(GL_POINTS);
    // glVertex3f(virilhaD.x, virilhaD.y, virilhaD.z);
    // glEnd();
    // glPopMatrix();
    desenhaPonto(virilhaD);

    glPushMatrix();
    // glTranslatef(virilhaD.x, virilhaD.y, virilhaD.z);
    // glRotatef ((GLfloat) joelhoDRot, 0.0, 0.0, 1.0);
    // glTranslatef(-virilhaD.x, -virilhaD.y, -virilhaD.z);
    aplicaRotacao(virilhaD, joelhoDRot);
    // glPushMatrix();
    // glBegin(GL_POINTS);
    // glVertex3f(joelhoD.x, joelhoD.y, joelhoD.z);
    // glEnd();
    // glPopMatrix();
    desenhaPonto(joelhoD);

    glPushMatrix();
    aplicaRotacao(joelhoD, tornozeloDRot);
    desenhaPonto(tornozeloD);

    aplicaRotacao(tornozeloD, peDRot);
    desenhaPonto(peD);
    // glBegin(GL_POINTS);
    // glVertex3f(tornozeloD.x, tornozeloD.y, tornozeloD.z);
    // glVertex3f(peD.x, peD.y, peD.z);
    // glEnd();
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glTranslatef(virilha.x, virilha.y, virilha.z);
    // glRotatef ((GLfloat) virilhaERot, 0.0, 0.0, 1.0);
    // glTranslatef(-virilha.x, -virilha.y, -virilha.z);
    aplicaRotacao(virilha, virilhaERot);
    // glPushMatrix();
    // glBegin(GL_POINTS);
    // glVertex3f(virilhaE.x, virilhaE.y, virilhaE.z);
    // glEnd();
    // glPopMatrix();
    desenhaPonto(virilhaE);

    glPushMatrix();
    // glTranslatef(virilhaE.x, virilhaE.y, virilhaE.z);
    // glRotatef ((GLfloat) joelhoERot, 0.0, 0.0, 1.0);
    // glTranslatef(-virilhaE.x, -virilhaE.y, -virilhaE.z);
    aplicaRotacao(virilhaE, joelhoERot);
    // glPushMatrix();
    // glBegin(GL_POINTS);
    // glVertex3f(joelhoE.x, joelhoE.y, joelhoE.z);
    // glEnd();
    // glPopMatrix();
    desenhaPonto(joelhoE);

    glPushMatrix();
    aplicaRotacao(joelhoE, tornozeloERot);
    desenhaPonto(tornozeloE);

    aplicaRotacao(tornozeloE, peERot);
    desenhaPonto(peE);

    // glBegin(GL_POINTS);
    // glVertex3f(tornozeloE.x, tornozeloE.y, tornozeloE.z);
    // glVertex3f(peE.x, peE.y, peE.z);
    // glEnd();
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();



    /*----------------------LINHAS------------------------------------------*/
    glPushMatrix();
    // glTranslatef(virilha.x, virilha.y, virilha.z);
    // glRotatef ((GLfloat) troncoRot, 0.0, 0.0, 1.0);
    // glTranslatef(-virilha.x, -virilha.y, -virilha.z);
    aplicaRotacao(virilha, troncoRot);
    // glPushMatrix();
    // glBegin(GL_LINES);
    // glVertex3f(tronco.x, tronco.y, tronco.z);
    // glVertex3f(virilha.x, virilha.y, virilha.z);
    // glEnd();
    // glPopMatrix();
    desenhaLinha(tronco, virilha);

    glPushMatrix();
    // glTranslatef(tronco.x, tronco.y, tronco.z);
    // glRotatef ((GLfloat) cabecaRot, 0.0, 0.0, 1.0);
    // glTranslatef(-tronco.x, -tronco.y, -tronco.z);
    aplicaRotacao(tronco, cabecaRot);
    // glBegin(GL_LINES);
    // glVertex3f(cabeca.x, cabeca.y, cabeca.z);
    // glVertex3f(tronco.x, tronco.y, tronco.z);
    // glEnd();
    desenhaLinha(cabeca, tronco);
    glPopMatrix();

    glPushMatrix();
    // glTranslatef(tronco.x, tronco.y, tronco.z);
    // glRotatef ((GLfloat) cotoveloERot, 0.0, 0.0, 1.0);
    // glTranslatef(-tronco.x, -tronco.y, -tronco.z);
    aplicaRotacao(tronco, cotoveloERot);
    // glPushMatrix();
    // glBegin(GL_LINES);
    // glVertex3f(tronco.x, tronco.y, tronco.z);
    // glVertex3f(cotoveloE.x, cotoveloE.y, cotoveloE.z);
    // glEnd();
    // glPopMatrix();
    desenhaLinha(tronco, cotoveloE);

    // glTranslatef(cotoveloE.x, cotoveloE.y, cotoveloE.z);
    // glRotatef ((GLfloat) maoERot, 0.0, 0.0, 1.0);
    // glTranslatef(-cotoveloE.x, -cotoveloE.y, -cotoveloE.z);
    aplicaRotacao(cotoveloE, maoERot);
    // glPushMatrix();
    // glBegin(GL_LINES);
    // glVertex3f(cotoveloE.x, cotoveloE.y, cotoveloE.z);
    // glVertex3f(maoE.x, maoE.y, maoE.z);
    // glEnd();
    // glPopMatrix();
    desenhaLinha(cotoveloE, maoE);
    glPopMatrix();

    glPushMatrix();
    // glTranslatef(tronco.x, tronco.y, tronco.z);
    // glRotatef ((GLfloat) cotoveloDRot, 0.0, 0.0, 1.0);
    // glTranslatef(-tronco.x, -tronco.y, -tronco.z);
    aplicaRotacao(tronco, cotoveloDRot);
    // glPushMatrix();
    // glBegin(GL_LINES);
    // glVertex3f(tronco.x, tronco.y, tronco.z);
    // glVertex3f(cotoveloD.x, cotoveloD.y, cotoveloD.z);
    // glEnd();
    // glPopMatrix();
    desenhaLinha(tronco, cotoveloD);

    // glTranslatef(cotoveloD.x, cotoveloD.y, cotoveloD.z);
    // glRotatef ((GLfloat) maoDRot, 0.0, 0.0, 1.0);
    // glTranslatef(-cotoveloD.x, -cotoveloD.y, -cotoveloD.z);
    aplicaRotacao(cotoveloD, maoDRot);
    // glPushMatrix();
    // glBegin(GL_LINES);
    // glVertex3f(cotoveloD.x, cotoveloD.y, cotoveloD.z);
    // glVertex3f(maoD.x, maoD.y, maoD.z);
    // glEnd();
    // glPopMatrix();
    desenhaLinha(cotoveloD, maoD);
    glPopMatrix();
    glPopMatrix();
/*--------------------------------------------------------------*/
    glPushMatrix();
    // glTranslatef(virilha.x, virilha.y, virilha.z);
    // glRotatef ((GLfloat) virilhaDRot, 0.0, 0.0, 1.0);
    // glTranslatef(-virilha.x, -virilha.y, -virilha.z);
    aplicaRotacao(virilha, virilhaDRot);
    // glPushMatrix();
    // glBegin(GL_LINES);
    // glVertex3f(virilha.x, virilha.y, virilha.z);
    // glVertex3f(virilhaD.x, virilhaD.y, virilhaD.z);
    // glEnd();
    // glPopMatrix();
    desenhaLinha(virilha, virilhaD);

    glPushMatrix();
    // glTranslatef(virilhaD.x, virilhaD.y, virilhaD.z);
    // glRotatef ((GLfloat) joelhoDRot, 0.0, 0.0, 1.0);
    // glTranslatef(-virilhaD.x, -virilhaD.y, -virilhaD.z);
    aplicaRotacao(virilhaD, joelhoDRot);
    // glPushMatrix();
    // glBegin(GL_LINES);
    // glVertex3f(virilhaD.x, virilhaD.y, virilhaD.z);
    // glVertex3f(joelhoD.x, joelhoD.y, joelhoD.z);
    // glEnd();
    // glPopMatrix();
    desenhaLinha(virilhaD, joelhoD);

    glPushMatrix();
    aplicaRotacao(joelhoD, tornozeloDRot);
    desenhaLinha(joelhoD, tornozeloD);

    aplicaRotacao(tornozeloD, peDRot);
    desenhaLinha(tornozeloD, peD);
    // glBegin(GL_LINES);
    // glVertex3f(joelhoD.x, joelhoD.y, joelhoD.z);
    // glVertex3f(tornozeloD.x, tornozeloD.y, tornozeloD.z);
    //
    // glVertex3f(tornozeloD.x, tornozeloD.y, tornozeloD.z);
    // glVertex3f(peD.x, peD.y, peD.z);
    // glEnd();
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glTranslatef(virilha.x, virilha.y, virilha.z);
    // glRotatef ((GLfloat) virilhaERot, 0.0, 0.0, 1.0);
    // glTranslatef(-virilha.x, -virilha.y, -virilha.z);
    aplicaRotacao(virilha, virilhaERot);
    // glPushMatrix();
    // glBegin(GL_LINES);
    // glVertex3f(virilha.x, virilha.y, virilha.z);
    // glVertex3f(virilhaE.x, virilhaE.y, virilhaE.z);
    // glEnd();
    // glPopMatrix();
    desenhaLinha(virilha, virilhaE);

    glPushMatrix();
    // glTranslatef(virilhaE.x, virilhaE.y, virilhaE.z);
    // glRotatef ((GLfloat) joelhoERot, 0.0, 0.0, 1.0);
    // glTranslatef(-virilhaE.x, -virilhaE.y, -virilhaE.z);
    aplicaRotacao(virilhaE, joelhoERot);
    // glPushMatrix();
    // glBegin(GL_LINES);
    // glVertex3f(virilhaE.x, virilhaE.y, virilhaE.z);
    // glVertex3f(joelhoE.x, joelhoE.y, joelhoE.z);
    // glEnd();
    // glPopMatrix();
    desenhaLinha(virilhaE, joelhoE);

    glPushMatrix();
    aplicaRotacao(joelhoE, tornozeloERot);
    desenhaLinha(joelhoE, tornozeloE);

    aplicaRotacao(tornozeloE, peERot);
    desenhaLinha(tornozeloE, peE);
    // glBegin(GL_LINES);
    // glVertex3f(joelhoE.x, joelhoE.y, joelhoE.z);
    // glVertex3f(tornozeloE.x, tornozeloE.y, tornozeloE.z);
    //
    // glVertex3f(tornozeloE.x, tornozeloE.y, tornozeloE.z);
    // glVertex3f(peE.x, peE.y, peE.z);
    // glEnd();
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();



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
            cotoveloERot = (cotoveloERot + 5) % 360;
            std::cout<<"+"<<std::endl;
            glutPostRedisplay();
            break;
        case '-':
            cotoveloERot = (cotoveloERot - 5) % 360;
            std::cout<<"-"<<std::endl;
            glutPostRedisplay();
            break;
        case 'a':
            maoERot = (maoERot + 5) % 360;
            std::cout<<"a"<<std::endl;
            glutPostRedisplay();
            break;
        case 'A':
            maoERot = (maoERot - 5) % 360;
            std::cout<<"A"<<std::endl;
            glutPostRedisplay();
            break;
        case 'd':
            cotoveloDRot = (cotoveloDRot + 5) % 360;
            std::cout<<"d"<<std::endl;
            glutPostRedisplay();
            break;
        case 'D':
            cotoveloDRot = (cotoveloDRot - 5) % 360;
            std::cout<<"D"<<std::endl;
            glutPostRedisplay();
            break;
        case 'f':
            maoDRot = (maoDRot + 5) % 360;
            std::cout<<"f"<<std::endl;
            glutPostRedisplay();
            break;
        case 'F':
            maoDRot = (maoDRot - 5) % 360;
            std::cout<<"F"<<std::endl;
            glutPostRedisplay();
            break;
        case 'c':
            cabecaRot = (cabecaRot + 5) % 360;
            std::cout<<"c"<<std::endl;
            glutPostRedisplay();
            break;
        case 'C':
            cabecaRot = (cabecaRot - 5) % 360;
            std::cout<<"C"<<std::endl;
            glutPostRedisplay();
            break;
        case 't':
            troncoRot = (troncoRot + 5) % 360;
            std::cout<<"t"<<std::endl;
            glutPostRedisplay();
            break;
        case 'T':
            troncoRot = (troncoRot - 5) % 360;
            std::cout<<"T"<<std::endl;
            glutPostRedisplay();
            break;
        case 'p':
            virilhaDRot = (virilhaDRot + 5) % 360;
            std::cout<<"p"<<std::endl;
            glutPostRedisplay();
            break;
        case 'P':
            virilhaDRot = (virilhaDRot - 5) % 360;
            std::cout<<"P"<<std::endl;
            glutPostRedisplay();
            break;
        case 'o':
            virilhaERot = (virilhaERot + 5) % 360;
            std::cout<<"o"<<std::endl;
            glutPostRedisplay();
            break;
        case 'O':
            virilhaERot = (virilhaERot - 5) % 360;
            std::cout<<"O"<<std::endl;
            glutPostRedisplay();
            break;
        case 'l':
            joelhoDRot = (joelhoDRot + 5) % 360;
            std::cout<<"l"<<std::endl;
            glutPostRedisplay();
            break;
        case 'L':
            joelhoDRot = (joelhoDRot - 5) % 360;
            std::cout<<"L"<<std::endl;
            glutPostRedisplay();
            break;
        case 'k':
            joelhoERot = (joelhoERot + 5) % 360;
            std::cout<<"k"<<std::endl;
            glutPostRedisplay();
            break;
        case 'K':
            joelhoERot = (joelhoERot - 5) % 360;
            std::cout<<"K"<<std::endl;
            glutPostRedisplay();
            break;
        case 'i':
            tornozeloDRot = (tornozeloDRot + 5) % 360;
            std::cout<<"i"<<std::endl;
            glutPostRedisplay();
            break;
        case 'I':
            tornozeloDRot = (tornozeloDRot - 5) % 360;
            std::cout<<"I"<<std::endl;
            glutPostRedisplay();
            break;
        case 'u':
            peDRot = (peDRot + 5) % 360;
            std::cout<<"u"<<std::endl;
            glutPostRedisplay();
            break;
        case 'U':
            peDRot = (peDRot - 5) % 360;
            std::cout<<"U"<<std::endl;
            glutPostRedisplay();
            break;

        case 'y':
            tornozeloERot = (tornozeloERot + 5) % 360;
            std::cout<<"y"<<std::endl;
            glutPostRedisplay();
            break;
        case 'Y':
            tornozeloERot = (tornozeloERot - 5) % 360;
            std::cout<<"Y"<<std::endl;
            glutPostRedisplay();
            break;
        case 'h':
            peERot = (peERot + 5) % 360;
            std::cout<<"h"<<std::endl;
            glutPostRedisplay();
            break;
        case 'H':
            peERot = (peERot - 5) % 360;
            std::cout<<"H"<<std::endl;
            glutPostRedisplay();
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
    glutCreateWindow("Humanoide");
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
