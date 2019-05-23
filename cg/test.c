#include <stdio.h>
#include <GL/glut.h>

GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = 0.0, xwcMax = 130.0;
GLfloat ywcMin = 0.0, ywcMax = 130.0;

typedef struct point
{
    GLfloat x, y, z;
};

void bino(int *c, int n)
{
    for (int k = 0; k <= n; k++)
    {
        c[k] = 1;
        for (int j = n; j >= k + 1; j--)
            c[k] = c[k] * j;
        for (int j = k; j >= 2; j--)
            c[k] = c[k] / j;
    }
}

void bezier

void displayFcn()
{
}

void winReshapeFun(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Prg. 8 Bezier Curve");
    CreateMenu();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFun);
    glutMainLoop();
    return 0;
}