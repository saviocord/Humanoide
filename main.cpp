/*
** Doing CSG with stencil
*/
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>


enum {HELP, PESCOCO, ABDOMEN,
      BRACO_D, ANTEBRACO_D, QUADRIL_D, COXA_D, CANELA_D, PE_D,
      BRACO_E, ANTEBRACO_E, QUADRIL_E, COXA_E, CANELA_E, PE_E};

GLfloat rotX, rotY, rotZ; //variaveis para a camera
GLfloat xRot, yRot, zRot = 1.0; //variaveis para o boneco
int operacao = HELP;
GLfloat lightpos[] = {-25.f, 0.f, 50.f, 1.f};

static int pescocoRot = 0, bracoERot = 0, antebracoERot = 0, bracoDRot = 0, antebracoDRot = 0, abdomenRot = 0;
static int quadrilDRot = 0, quadrilERot = 0,coxaERot = 0, coxaDRot = 0, canelaERot = 0, canelaDRot = 0, peERot = 0, peDRot = 0;

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
    glRotatef ((GLfloat) rotacao, xRot, yRot, zRot);
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
    /* clear stencil each time */
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
    aplicaRotacao(virilha, abdomenRot);
    desenhaPonto(tronco, ((operacao == ABDOMEN)||(operacao == PESCOCO)||(operacao == BRACO_D)||(operacao == BRACO_E)));

    glPushMatrix();
    aplicaRotacao(tronco, pescocoRot);
    desenhaPonto(cabeca, (operacao == PESCOCO));
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(tronco, bracoERot);
    desenhaPonto(cotoveloE, ((operacao == BRACO_E)||(operacao == ANTEBRACO_E)));

    aplicaRotacao(cotoveloE, antebracoERot);
    desenhaPonto(maoE, (operacao == ANTEBRACO_E));
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(tronco, bracoDRot);
    desenhaPonto(cotoveloD, ((operacao == BRACO_D)||(operacao == ANTEBRACO_D)));

    aplicaRotacao(cotoveloD, antebracoDRot);
    desenhaPonto(maoD, (operacao == ANTEBRACO_D));
    glPopMatrix();
    glPopMatrix();


    desenhaPonto(virilha, ((operacao == ABDOMEN)||(operacao == QUADRIL_D)||(operacao == QUADRIL_E)));

    glPushMatrix();
    aplicaRotacao(virilha, quadrilDRot);
    desenhaPonto(virilhaD, ((operacao == QUADRIL_D)||(operacao == COXA_D)));

    glPushMatrix();
    aplicaRotacao(virilhaD, coxaDRot);
    desenhaPonto(joelhoD, ((operacao == COXA_D)||(operacao == CANELA_D)));

    glPushMatrix();
    aplicaRotacao(joelhoD, canelaDRot);
    desenhaPonto(tornozeloD, ((operacao == CANELA_D)||(operacao == PE_D)));

    aplicaRotacao(tornozeloD, peDRot);
    desenhaPonto(peD, (operacao == PE_D));
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(virilha, quadrilERot);
    desenhaPonto(virilhaE, ((operacao == QUADRIL_E)||(operacao == COXA_E)));

    glPushMatrix();
    aplicaRotacao(virilhaE, coxaERot);
    desenhaPonto(joelhoE, ((operacao == COXA_E)||(operacao == CANELA_E)));

    glPushMatrix();
    aplicaRotacao(joelhoE, canelaERot);
    desenhaPonto(tornozeloE, ((operacao == CANELA_E)||(operacao == PE_E)));

    aplicaRotacao(tornozeloE, peERot);
    desenhaPonto(peE, (operacao == PE_E));

    glPopMatrix();

    glPopMatrix();
    glPopMatrix();



    /*----------------------LINHAS------------------------------------------*/
    glPushMatrix();
    aplicaRotacao(virilha, abdomenRot);
    desenhaLinha(tronco, virilha, operacao == ABDOMEN);

    glPushMatrix();
    aplicaRotacao(tronco, pescocoRot);
    desenhaLinha(cabeca, tronco, operacao == PESCOCO);
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(tronco, bracoERot);
    desenhaLinha(tronco, cotoveloE, operacao == BRACO_E);

    aplicaRotacao(cotoveloE, antebracoERot);
    desenhaLinha(cotoveloE, maoE, operacao == ANTEBRACO_E);
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(tronco, bracoDRot);
    desenhaLinha(tronco, cotoveloD, operacao == BRACO_D);

    aplicaRotacao(cotoveloD, antebracoDRot);
    desenhaLinha(cotoveloD, maoD, operacao == ANTEBRACO_D);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(virilha, quadrilDRot);
    desenhaLinha(virilha, virilhaD, operacao == QUADRIL_D);

    glPushMatrix();
    aplicaRotacao(virilhaD, coxaDRot);
    desenhaLinha(virilhaD, joelhoD, operacao == COXA_D);

    glPushMatrix();
    aplicaRotacao(joelhoD, canelaDRot);
    desenhaLinha(joelhoD, tornozeloD, operacao == CANELA_D);

    aplicaRotacao(tornozeloD, peDRot);
    desenhaLinha(tornozeloD, peD, operacao == PE_D);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    aplicaRotacao(virilha, quadrilERot);
    desenhaLinha(virilha, virilhaE, operacao == QUADRIL_E);

    glPushMatrix();
    aplicaRotacao(virilhaE, coxaERot);
    desenhaLinha(virilhaE, joelhoE, operacao == COXA_E);

    glPushMatrix();
    aplicaRotacao(joelhoE, canelaERot);
    desenhaLinha(joelhoE, tornozeloE, operacao == CANELA_E);

    aplicaRotacao(tornozeloE, peERot);
    desenhaLinha(tornozeloE, peE, operacao == PE_E);
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

void rotaciona(char key){
    switch (operacao) {
        case PESCOCO:
            if(key=='+'){
                pescocoRot = (pescocoRot + 5) % 360;
            }else{
                pescocoRot = (pescocoRot - 5) % 360;
            }
        break;

        case ABDOMEN:
            if(key=='+'){
                abdomenRot = (abdomenRot + 5) % 360;
            }else{
                abdomenRot = (abdomenRot - 5) % 360;
            }
        break;

        case BRACO_D:
            if(key=='+'){
                bracoDRot = (bracoDRot + 5) % 360;
            }else{
                bracoDRot = (bracoDRot - 5) % 360;
            }

        break;
        case ANTEBRACO_D:
            if(key=='+'){
                antebracoDRot = (antebracoDRot + 5) % 360;
            }else{
                antebracoDRot = (antebracoDRot - 5) % 360;
            }

        break;
        case BRACO_E:
            if(key=='+'){
                bracoERot = (bracoERot + 5) % 360;
            }else{
                bracoERot = (bracoERot - 5) % 360;
            }

        break;
        case ANTEBRACO_E:
            if(key=='+'){
                antebracoERot = (antebracoERot + 5) % 360;
            }else{
                antebracoERot = (antebracoERot - 5) % 360;
            }

        break;
        case QUADRIL_D:
            if(key=='+'){
                quadrilDRot = (quadrilDRot + 5) % 360;
            }else{
                quadrilDRot = (quadrilDRot - 5) % 360;
            }

        break;
        case COXA_D:
            if(key=='+'){
                coxaDRot = (coxaDRot + 5) % 360;
            }else{
                coxaDRot = (coxaDRot - 5) % 360;
            }

        break;
        case CANELA_D:
            if(key=='+'){
                canelaDRot = (canelaDRot + 5) % 360;
            }else{
                canelaDRot = (canelaDRot - 5) % 360;
            }

        break;
        case PE_D:
            if(key=='+'){
                peDRot = (peDRot + 5) % 360;
            }else{
                peDRot = (peDRot - 5) % 360;
            }

        break;
        case QUADRIL_E:
            if(key=='+'){
                quadrilERot = (quadrilERot + 5) % 360;
            }else{
                quadrilERot = (quadrilERot - 5) % 360;
            }

        break;
        case COXA_E:
            if(key=='+'){
                coxaERot = (coxaERot + 5) % 360;
            }else{
                coxaERot = (coxaERot - 5) % 360;
            }

        break;
        case CANELA_E:
            if(key=='+'){
                canelaERot = (canelaERot + 5) % 360;
            }else{
                canelaERot = (canelaERot - 5) % 360;
            }

        break;
        case PE_E:
            if(key=='+'){
                peERot = (peERot + 5) % 360;
            }else{
                peERot = (peERot - 5) % 360;
            }


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
            xRot = 1.0;
            yRot = 0.0;
            zRot = 0.0;
            break;
        case 'y':
            xRot = 0.0;
            yRot = 1.0;
            zRot = 0.0;
            break;
        case 'z':
            xRot = 0.0;
            yRot = 0.0;
            zRot = 1.0;
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
    glutAddMenuEntry("Help", HELP);
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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);

    glutMainLoop();

    return 0;
}
