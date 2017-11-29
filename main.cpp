/*
** Doing CSG with stencil
*/
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>


enum {MENU, PESCOCO, ABDOMEN,
      BRACO_D, ANTEBRACO_D, QUADRIL_D, COXA_D, CANELA_D, PE_D,
      BRACO_E, ANTEBRACO_E, QUADRIL_E, COXA_E, CANELA_E, PE_E};

GLfloat rotX, rotY, rotZ; //variaveis para a camera
int xRot, yRot, zRot = 1; //variaveis para o boneco

int operacao = MENU;
GLfloat lightpos[] = {-25.f, 0.f, 50.f, 1.f};

static int pescocoRotX = 0, bracoERotX = 0, antebracoERotX = 0, bracoDRotX = 0, antebracoDRotX = 0, abdomenRotX = 0;
static int quadrilDRotX = 0, quadrilERotX = 0,coxaERotX = 0, coxaDRotX = 0, canelaERotX = 0, canelaDRotX = 0, peERotX = 0, peDRotX = 0;

static int pescocoRotY = 0, bracoERotY = 0, antebracoERotY = 0, bracoDRotY = 0, antebracoDRotY = 0, abdomenRotY = 0;
static int quadrilDRotY = 0, quadrilERotY = 0,coxaERotY = 0, coxaDRotY = 0, canelaERotY = 0, canelaDRotY = 0, peERotY = 0, peDRotY = 0;

static int pescocoRotZ = 0, bracoERotZ = 0, antebracoERotZ = 0, bracoDRotZ = 0, antebracoDRotZ = 0, abdomenRotZ = 0;
static int quadrilDRotZ = 0, quadrilERotZ = 0,coxaERotZ = 0, coxaDRotZ = 0, canelaERotZ = 0, canelaDRotZ = 0, peERotZ = 0, peDRotZ = 0;

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

void aplicaRotacao(Posicao parte, int x, int y, int z)
{
    glTranslatef(parte.x, parte.y, parte.z);
    glRotatef ((GLfloat) x, 1, 0, 0);
    glRotatef ((GLfloat) y, 0, 1, 0);
    glRotatef ((GLfloat) z, 0, 0, 1);
    glTranslatef(-parte.x, -parte.y, -parte.z);
}

void desenhaPonto(Posicao parte, bool selecionado = false)
{
    glPushMatrix();
    if (selecionado) glColor3f(1.0, 0.0, 0.0);
    else glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex3f(parte.x, parte.y, parte.z);
    glEnd();
    glPopMatrix();
}

void desenhaLinha(Posicao parteIni, Posicao parteFim, bool selecionado = false)
{
    glPushMatrix();
    if (selecionado) glColor3f(1.0, 0.0, 0.0);
    else glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(parteIni.x, parteIni.y, parteIni.z);
    glVertex3f(parteFim.x, parteFim.y, parteFim.z);
    glEnd();
    glPopMatrix();
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
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
    aplicaRotacao(virilha, abdomenRotX, abdomenRotY, abdomenRotZ);
    desenhaPonto(tronco, ((operacao == ABDOMEN)||(operacao == PESCOCO)||(operacao == BRACO_D)||(operacao == BRACO_E)));

    glPushMatrix();
    aplicaRotacao(tronco, pescocoRotX, pescocoRotY, pescocoRotZ);
    desenhaPonto(cabeca, (operacao == PESCOCO));
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(tronco, bracoERotX, bracoERotY, bracoERotZ);
    desenhaPonto(cotoveloE, ((operacao == BRACO_E)||(operacao == ANTEBRACO_E)));

    aplicaRotacao(cotoveloE, antebracoERotX, antebracoERotY, antebracoERotZ);
    desenhaPonto(maoE, (operacao == ANTEBRACO_E));
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(tronco, bracoDRotX, bracoDRotY, bracoDRotZ);
    desenhaPonto(cotoveloD, ((operacao == BRACO_D)||(operacao == ANTEBRACO_D)));

    aplicaRotacao(cotoveloD, antebracoDRotX, antebracoDRotY, antebracoDRotZ);
    desenhaPonto(maoD, (operacao == ANTEBRACO_D));
    glPopMatrix();
    glPopMatrix();


    desenhaPonto(virilha, ((operacao == ABDOMEN)||(operacao == QUADRIL_D)||(operacao == QUADRIL_E)));

    glPushMatrix();
    aplicaRotacao(virilha, quadrilDRotX, quadrilDRotY, quadrilDRotZ);
    desenhaPonto(virilhaD, ((operacao == QUADRIL_D)||(operacao == COXA_D)));

    glPushMatrix();
    aplicaRotacao(virilhaD, coxaDRotX, coxaDRotY, coxaDRotZ);
    desenhaPonto(joelhoD, ((operacao == COXA_D)||(operacao == CANELA_D)));

    glPushMatrix();
    aplicaRotacao(joelhoD, canelaDRotX, canelaDRotY, canelaDRotZ);
    desenhaPonto(tornozeloD, ((operacao == CANELA_D)||(operacao == PE_D)));

    aplicaRotacao(tornozeloD, peDRotX, peDRotY, peDRotZ);
    desenhaPonto(peD, (operacao == PE_D));
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(virilha, quadrilERotX, quadrilERotY, quadrilERotZ);
    desenhaPonto(virilhaE, ((operacao == QUADRIL_E)||(operacao == COXA_E)));

    glPushMatrix();
    aplicaRotacao(virilhaE, coxaERotX, coxaERotY, coxaERotZ);
    desenhaPonto(joelhoE, ((operacao == COXA_E)||(operacao == CANELA_E)));

    glPushMatrix();
    aplicaRotacao(joelhoE, canelaERotX, canelaERotY, canelaERotZ);
    desenhaPonto(tornozeloE, ((operacao == CANELA_E)||(operacao == PE_E)));

    aplicaRotacao(tornozeloE, peERotX, peERotY, peERotZ);
    desenhaPonto(peE, (operacao == PE_E));

    glPopMatrix();

    glPopMatrix();
    glPopMatrix();



    /*----------------------LINHAS------------------------------------------*/
    glPushMatrix();
    aplicaRotacao(virilha, abdomenRotX, abdomenRotY, abdomenRotZ);
    desenhaLinha(tronco, virilha, operacao == ABDOMEN);

    glPushMatrix();
    aplicaRotacao(tronco, pescocoRotX, pescocoRotY, pescocoRotZ);
    desenhaLinha(cabeca, tronco, operacao == PESCOCO);
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(tronco, bracoERotX, bracoERotY, bracoERotZ);
    desenhaLinha(tronco, cotoveloE, operacao == BRACO_E);

    aplicaRotacao(cotoveloE, antebracoERotX, antebracoERotY, antebracoERotZ);
    desenhaLinha(cotoveloE, maoE, operacao == ANTEBRACO_E);
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(tronco, bracoDRotX, bracoDRotY, bracoDRotZ);
    desenhaLinha(tronco, cotoveloD, operacao == BRACO_D);

    aplicaRotacao(cotoveloD, antebracoDRotX, antebracoDRotY, antebracoDRotZ);
    desenhaLinha(cotoveloD, maoD, operacao == ANTEBRACO_D);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(virilha, quadrilDRotX, quadrilDRotY, quadrilDRotZ);
    desenhaLinha(virilha, virilhaD, operacao == QUADRIL_D);

    glPushMatrix();
    aplicaRotacao(virilhaD, coxaDRotX, coxaDRotY, coxaDRotZ);
    desenhaLinha(virilhaD, joelhoD, operacao == COXA_D);

    glPushMatrix();
    aplicaRotacao(joelhoD, canelaDRotX, canelaDRotY, canelaDRotZ);
    desenhaLinha(joelhoD, tornozeloD, operacao == CANELA_D);

    aplicaRotacao(tornozeloD, peDRotX, peDRotY, peDRotZ);
    desenhaLinha(tornozeloD, peD, operacao == PE_D);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(virilha, quadrilERotX, quadrilERotY, quadrilERotZ);
    desenhaLinha(virilha, virilhaE, operacao == QUADRIL_E);

    glPushMatrix();
    aplicaRotacao(virilhaE, coxaERotX, coxaERotY, coxaERotZ);
    desenhaLinha(virilhaE, joelhoE, operacao == COXA_E);

    glPushMatrix();
    aplicaRotacao(joelhoE, canelaERotX, canelaERotY, canelaERotZ);
    desenhaLinha(joelhoE, tornozeloE, operacao == CANELA_E);

    aplicaRotacao(tornozeloE, peERotX, peERotY, peERotZ);
    desenhaLinha(tornozeloE, peE, operacao == PE_E);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();


    glPopMatrix();

    glutSwapBuffers();
}

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

void rotaciona(char key){
    int angulo = key == '+' ? 5 : -5;

    std::cout<<"x:"<<xRot<<" y:"<<yRot<<" z:"<<zRot<<std::endl;

    switch (operacao) {
        case PESCOCO:
            if(xRot)
                pescocoRotX = (pescocoRotX + angulo) % 360;
            else if(yRot)
                pescocoRotY = (pescocoRotY + angulo) % 360;
            else if(zRot)
                pescocoRotZ = (pescocoRotZ + angulo) % 360;
        break;

        case ABDOMEN:
            if(xRot)
                abdomenRotX = (abdomenRotX + angulo) % 360;
            else if(yRot)
                abdomenRotY = (abdomenRotY + angulo) % 360;
            else if(zRot)
                abdomenRotZ = (abdomenRotZ + angulo) % 360;
        break;

        case BRACO_D:
            if(xRot)
                bracoDRotX = (bracoDRotX + angulo) % 360;
            else if(yRot)
                bracoDRotY = (bracoDRotY + angulo) % 360;
            else if(zRot)
                bracoDRotZ = (bracoDRotZ + angulo) % 360;
        break;

        case ANTEBRACO_D:
            if(xRot)
                antebracoDRotX = (antebracoDRotX + angulo) % 360;
            else if(yRot)
                antebracoDRotY = (antebracoDRotY + angulo) % 360;
            else if(zRot)
                antebracoDRotZ = (antebracoDRotZ + angulo) % 360;
        break;

        case BRACO_E:
            if(xRot)
                bracoERotX = (bracoERotX + angulo) % 360;
            else if(yRot)
                bracoERotY = (bracoERotY + angulo) % 360;
            else if(zRot)
                bracoERotZ = (bracoERotZ + angulo) % 360;
        break;

        case ANTEBRACO_E:
            if(xRot)
                antebracoERotX = (antebracoERotX + angulo) % 360;
            else if(yRot)
                antebracoERotY = (antebracoERotY + angulo) % 360;
            else if(zRot)
                antebracoERotZ = (antebracoERotZ + angulo) % 360;
        break;

        case QUADRIL_D:
            if(xRot)
                quadrilDRotX = (quadrilDRotX + angulo) % 360;
            else if(yRot)
                quadrilDRotY = (quadrilDRotY + angulo) % 360;
            else if(zRot)
                quadrilDRotZ = (quadrilDRotZ + angulo) % 360;
        break;

        case COXA_D:
            if(xRot)
                coxaDRotX = (coxaDRotX + angulo) % 360;
            else if(yRot)
                coxaDRotY = (coxaDRotY + angulo) % 360;
            else if(zRot)
                coxaDRotZ = (coxaDRotZ + angulo) % 360;
        break;

        case CANELA_D:
            if(xRot)
                canelaDRotX = (canelaDRotX + angulo) % 360;
            else if(yRot)
                canelaDRotY = (canelaDRotY + angulo) % 360;
            else if(zRot)
                canelaDRotZ = (canelaDRotZ + angulo) % 360;
        break;

        case PE_D:
            if(xRot)
                peDRotX = (peDRotX + angulo) % 360;
            else if(yRot)
                peDRotY = (peDRotY + angulo) % 360;
            else if(zRot)
                peDRotZ = (peDRotZ + angulo) % 360;
        break;

        case QUADRIL_E:
            if(xRot)
                quadrilERotX = (quadrilERotX + angulo) % 360;
            else if(yRot)
                quadrilERotY = (quadrilERotY + angulo) % 360;
            else if(zRot)
                quadrilERotZ = (quadrilERotZ + angulo) % 360;
        break;

        case COXA_E:
            if(xRot)
                coxaERotX = (coxaERotX + angulo) % 360;
            else if(yRot)
                coxaERotY = (coxaERotY + angulo) % 360;
            else if(zRot)
                coxaERotZ = (coxaERotZ + angulo) % 360;
        break;

        case CANELA_E:
            if(xRot)
                canelaERotX = (canelaERotX + angulo) % 360;
            else if(yRot)
                canelaERotY = (canelaERotY + angulo) % 360;
            else if(zRot)
                canelaERotZ = (canelaERotZ + angulo) % 360;
        break;

        case PE_E:
            if(xRot)
                peERotX = (peERotX + angulo) % 360;
            else if(yRot)
                peERotY = (peERotY + angulo) % 360;
            else if(zRot)
                peERotZ = (peERotZ + angulo) % 360;
        break;
    }
}

void key(unsigned char key, int, int) {
    switch(key) {
        case 'q':
            exit(0);
        case '+':
            rotaciona('+');
            break;
        case '-':
            rotaciona('-');
            break;
        case 'x':
            xRot = 1;
            yRot = 0;
            zRot = 0;
            break;
        case 'y':
            xRot = 0;
            yRot = 1;
            zRot = 0;
            break;
        case 'z':
            xRot = 0;
            yRot = 0;
            zRot = 1;
            break;
    }
    glutPostRedisplay();
    draw();
}

void menu(int csgop) {
    operacao = csgop;
    glutPostRedisplay();
}

void menuCallback(void){

    glutCreateMenu(menu);
    glutAddMenuEntry("MENU", MENU);
    glutAddMenuEntry("Pescoco", PESCOCO);
    glutAddMenuEntry("Abdomen", ABDOMEN);
    glutAddMenuEntry("Braco D", BRACO_D);
    glutAddMenuEntry("Braco E", BRACO_E);
    glutAddMenuEntry("Antebraco D", ANTEBRACO_D);
    glutAddMenuEntry("Antebraco E", ANTEBRACO_E);
    glutAddMenuEntry("Quadril D", QUADRIL_D);
    glutAddMenuEntry("Quadril E", QUADRIL_E);
    glutAddMenuEntry("Coxa D", COXA_D);
    glutAddMenuEntry("Coxa E", COXA_E);
    glutAddMenuEntry("Canela D", CANELA_D);
    glutAddMenuEntry("Canela E", CANELA_E);
    glutAddMenuEntry("Pe D", PE_D);
    glutAddMenuEntry("Pe E", PE_E);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int botao, int estado, int x, int y){
    //std::cout<<" x:"<<x<<" y:"<<y<<" estado:"<<estado<<" botao:"<<botao<<std::endl;
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE);
    glutCreateWindow("Humanoide");
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

//    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);

    glutMainLoop();

    return 0;
}
