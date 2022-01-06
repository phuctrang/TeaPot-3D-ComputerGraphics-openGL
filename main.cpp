#include <gl\glut.h>
#include <math.h>
#include<stdio.h>
#include <stdarg.h>
#include <math.h>
#include <windows.h>
#define GL_GLEXT_PROTOTYPES

GLuint teapotList;
float g_x = 0.0;
float g_z = 0.0;
float lz = -10.0;
float lx = 0.0;
float angle = 0.0; 
 
float deltaAngle = 0.0f;
int xOrigin = -1;
bool g_is_rotate = false;

// các tọa độ ấm trà
long patchdata[][16] =
{
	{102, 103, 104, 105, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
	{12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,24, 25, 26, 27},
	{24, 25, 26, 27, 29, 30, 31, 32, 33, 34, 35, 36,37, 38, 39, 40},
	{96, 96, 96, 96, 97, 98, 99, 100, 101, 101, 101,101, 0, 1, 2, 3,},
	{0, 1, 2, 3, 106, 107, 108, 109, 110, 111, 112,113, 114, 115, 116, 117},
	     /* đế ấm */
	{118, 118, 118, 118, 124, 122, 119, 121, 123, 126,125, 120, 40, 39, 38, 37},
	     /* tay cầm */
	{41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,53, 54, 55, 56},
	{53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,28, 65, 66, 67},
	     /* ngòi ấm */
	{68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,80, 81, 82, 83},
	{80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,92, 93, 94, 95}
};

float cpdata[][3] =
{
     {0.2, 0, 2.7}, {0.2, -0.112, 2.7}, {0.112, -0.2, 2.7}, {0,
     -0.2, 2.7}, {1.3375, 0, 2.53125}, {1.3375, -0.749, 2.53125},
     {0.749, -1.3375, 2.53125}, {0, -1.3375, 2.53125}, {1.4375,
     0, 2.53125}, {1.4375, -0.805, 2.53125}, {0.805, -1.4375,
     2.53125}, {0, -1.4375, 2.53125}, {1.5, 0, 2.4}, {1.5, -0.84,
     2.4}, {0.84, -1.5, 2.4}, {0, -1.5, 2.4}, {1.75, 0, 1.875},
     {1.75, -0.98, 1.875}, {0.98, -1.75, 1.875}, {0, -1.75,
     1.875}, {2, 0, 1.35}, {2, -1.12, 1.35}, {1.12, -2, 1.35},
     {0, -2, 1.35}, {2, 0, 0.9}, {2, -1.12, 0.9}, {1.12, -2,
     0.9}, {0, -2, 0.9}, {-2, 0, 0.9}, {2, 0, 0.45}, {2, -1.12,
     0.45}, {1.12, -2, 0.45}, {0, -2, 0.45}, {1.5, 0, 0.225},
     {1.5, -0.84, 0.225}, {0.84, -1.5, 0.225}, {0, -1.5, 0.225},
     {1.5, 0, 0.15}, {1.5, -0.84, 0.15}, {0.84, -1.5, 0.15}, {0,
     -1.5, 0.15}, {-1.6, 0, 2.025}, {-1.6, -0.3, 2.025}, {-1.5,
     -0.3, 2.25}, {-1.5, 0, 2.25}, {-2.3, 0, 2.025}, {-2.3, -0.3,
     2.025}, {-2.5, -0.3, 2.25}, {-2.5, 0, 2.25}, {-2.7, 0,
     2.025}, {-2.7, -0.3, 2.025}, {-3, -0.3, 2.25}, {-3, 0,
     2.25}, {-2.7, 0, 1.8}, {-2.7, -0.3, 1.8}, {-3, -0.3, 1.8},
     {-3, 0, 1.8}, {-2.7, 0, 1.575}, {-2.7, -0.3, 1.575}, {-3,
     -0.3, 1.35}, {-3, 0, 1.35}, {-2.5, 0, 1.125}, {-2.5, -0.3,
     1.125}, {-2.65, -0.3, 0.9375}, {-2.65, 0, 0.9375}, {-2,
     -0.3, 0.9}, {-1.9, -0.3, 0.6}, {-1.9, 0, 0.6}, {1.7, 0,
     1.425}, {1.7, -0.66, 1.425}, {1.7, -0.66, 0.6}, {1.7, 0,
     0.6}, {2.6, 0, 1.425}, {2.6, -0.66, 1.425}, {3.1, -0.66,
     0.825}, {3.1, 0, 0.825}, {2.3, 0, 2.1}, {2.3, -0.25, 2.1},
     {2.4, -0.25, 2.025}, {2.4, 0, 2.025}, {2.7, 0, 2.4}, {2.7,
     -0.25, 2.4}, {3.3, -0.25, 2.4}, {3.3, 0, 2.4}, {2.8, 0,
     2.475}, {2.8, -0.25, 2.475}, {3.525, -0.25, 2.49375},
     {3.525, 0, 2.49375}, {2.9, 0, 2.475}, {2.9, -0.15, 2.475},
     {3.45, -0.15, 2.5125}, {3.45, 0, 2.5125}, {2.8, 0, 2.4},
     {2.8, -0.15, 2.4}, {3.2, -0.15, 2.4}, {3.2, 0, 2.4}, {0, 0,
     3.15}, {0.8, 0, 3.15}, {0.8, -0.45, 3.15}, {0.45, -0.8,
     3.15}, {0, -0.8, 3.15}, {0, 0, 2.85}, {1.4, 0, 2.4}, {1.4,
     -0.784, 2.4}, {0.784, -1.4, 2.4}, {0, -1.4, 2.4}, {0.4, 0,
     2.55}, {0.4, -0.224, 2.55}, {0.224, -0.4, 2.55}, {0, -0.4,
     2.55}, {1.3, 0, 2.55}, {1.3, -0.728, 2.55}, {0.728, -1.3,
     2.55}, {0, -1.3, 2.55}, {1.3, 0, 2.4}, {1.3, -0.728, 2.4},
     {0.728, -1.3, 2.4}, {0, -1.3, 2.4}, {0, 0, 0}, {1.425,
     -0.798, 0}, {1.5, 0, 0.075}, {1.425, 0, 0}, {0.798, -1.425,
     0}, {0, -1.5, 0.075}, {0, -1.425, 0}, {1.5, -0.84, 0.075},
     {0.84, -1.5, 0.075}
};
float ver[8][3] = 
{
    {-0.05,-0.05,0.05},
    {-0.05,0.05,0.05},
    {0.05,0.05,0.05},
    {0.05,-0.05,0.05},
    {-0.05,-0.05,-0.05},
    {-0.05,0.05,-0.05},
    {0.05,0.05,-0.05},
    {0.05,-0.05,-0.05},
};
GLfloat color[8][3] = 
{
    {0.0,0.0,0.0},
    {1.0,0.0,0.0},
    {1.0,1.0,0.0},
    {0.0,1.0,0.0},
    {0.0,0.0,1.0},
    {1.0,0.0,1.0},
    {1.0,1.0,1.0},
    {0.0,1.0,1.0},
};
void Init()
{
  g_x = 10 * sin(angle);
  g_z = 10 * cos(angle);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_LIGHTING_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  
  GLfloat light_pos[] = { 0.0, 0.0, 10.0, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  
  GLfloat ambient[] = { 1.0, 1.0, 1.0, 2.0 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
 
  GLfloat diff_use[] = {0.1, 0.2, 0.3, 1.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

  GLfloat specular[] = { 0.0, 1.0, 1.0, 1.0 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  GLfloat shininess = 50.0f;
  glMateriali(GL_FRONT, GL_SHININESS, shininess);
 
}
static float tex[2][2][2] =
{
   { {0, 0},
     {1, 0}},
   { {0, 1},
     {1, 1}}
};
void quad(int a,int b,int c,int d)
{
    glBegin(GL_QUADS);
    glColor3fv(color[a]);
    glVertex3fv(ver[a]);

    glColor3fv(color[b]);
    glVertex3fv(ver[b]);

    glColor3fv(color[c]);
    glVertex3fv(ver[c]);

    glColor3fv(color[d]);
    glVertex3fv(ver[d]);
    glEnd();
}
void colorcube()
{
    quad(0,3,2,1);
    quad(2,3,7,6);
    quad(0,4,7,3);
    quad(1,2,6,5);
    quad(4,5,6,7);
    quad(0,1,5,4);
}

//Hàm vẽ ấm trà
static void teapot(GLint grid, GLdouble scale, GLenum type)
{
   float p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
   long i, j, k, l;
 
   glPushAttrib(GL_ENABLE_BIT | GL_EVAL_BIT);
   glEnable(GL_AUTO_NORMAL);
   glEnable(GL_NORMALIZE);
   glEnable(GL_MAP2_VERTEX_3);
   glEnable(GL_MAP2_TEXTURE_COORD_2);
   glPushMatrix();
   glRotatef(270.0, 1.0, 0.0, 0.0);
   glScalef(0.5 * scale, 0.5 * scale, 0.5 * scale);
   glTranslatef(0.0, 0.0, -1.5);
   for (i = 0; i < 10; i++) {
     for (j = 0; j < 4; j++) {
       for (k = 0; k < 4; k++) {
         for (l = 0; l < 3; l++) {
           p[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
           q[j][k][l] = cpdata[patchdata[i][j * 4 + (3 - k)]][l];
           if (l == 1)
             q[j][k][l] *= -1.0;
           if (i < 6) {
             r[j][k][l] =
               cpdata[patchdata[i][j * 4 + (3 - k)]][l];
             if (l == 0)
               r[j][k][l] *= -1.0;
             s[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
             if (l == 0)
               s[j][k][l] *= -1.0;
             if (l == 1)
               s[j][k][l] *= -1.0;
           }
         }
       }
     }
     glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2,
       &tex[0][0][0]);
     glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
       &p[0][0][0]);
     glMapGrid2f(grid, 0.0, 1.0, grid, 0.0, 1.0);
     glEvalMesh2(type, 0, grid, 0, grid);
     glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
       &q[0][0][0]);
     glEvalMesh2(type, 0, grid, 0, grid);
     if (i < 6) {
       glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
         &r[0][0][0]);
       glEvalMesh2(type, 0, grid, 0, grid);
       glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
         &s[0][0][0]);
       glEvalMesh2(type, 0, grid, 0, grid);
     }
   }
   glPopMatrix();
   glPopAttrib();
}

void glutSolidTeapot1(GLdouble scale)
{
   teapot(14, scale, GL_FILL);
}

void Tea(GLdouble scale)
{
	teapot(100, scale, GL_LINE);
}

// Đế bàn trà
void wall(double thickness)
{
    glPushMatrix();
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(3.0,thickness,3.0);
    glutSolidCube(2.0);
    glPopMatrix();
}
// Chân bàn
void tableLeg(double thick,double len)
{
    glPushMatrix();
    glTranslated(0,len/2,0);
    glScaled(thick,len,thick);
    glutSolidCube(1.0);
    glPopMatrix();
}
// Bàn
void table(double topWid,double topThick,double legThick,double legLen)
{
    glPushMatrix();
    glTranslated(0,legLen,0);
    glScaled(topWid,topThick,topWid);
    glutSolidCube(1.5);
    glPopMatrix();
    double dist=0.95*topWid/2.0-legThick/2.0;
    glPushMatrix();
    glTranslated(dist,0,dist);
    tableLeg(legThick,legLen);
    glTranslated(0,0,-2*dist);
    tableLeg(legThick,legLen);
    glTranslated(-2*dist,0,2*dist);
    tableLeg(legThick,legLen);
    glTranslated(0,0,-2*dist);
    tableLeg(legThick,legLen);
    glPopMatrix();
}
void ReShape(int width, int height)
{
  glViewport(0, 0, width, height);
  float ratio = (float)width / (float)height;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, ratio, 1, 100.0);
  glMatrixMode(GL_MODELVIEW);
}
void OnKeyDown(int key, int xx, int yy) {
  switch (key)
  {
  case GLUT_KEY_LEFT:
    g_x -= 0.1;
    break;
  case GLUT_KEY_RIGHT:
    g_x += 0.1;
    break;
  case GLUT_KEY_UP:
    g_z -= 0.1;
    break;
  case GLUT_KEY_DOWN:
    g_z += 0.1;
    break;
  }
}
void mouseButton(int button, int state, int x, int y)
{
  // only start motion if the left button is pressed
  if (button == GLUT_RIGHT_BUTTON)
  {
    // when the button is released
    if (state == GLUT_UP)
    {
      angle += deltaAngle;
      xOrigin = -1;
      g_is_rotate = false;
    }
    else
    {
      g_is_rotate = true;
      deltaAngle = 0.0;
      xOrigin = x;
    }
  }
}
void mouseMove(int x, int y)
{
  if (g_is_rotate)
  {
    deltaAngle += (x - xOrigin) * 0.0005f;
    g_x = 10 * sin(angle + deltaAngle);
    g_z = 10 * cos(angle + deltaAngle);
  }
}
double rotate_y = 0;                              		
double rotate_x = 0;
void DrawCoordinate()
{
  glDisable(GL_LIGHTING);
  //glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-100.0, 0.0, 0.0);
  glVertex3f(100.0, 0.0, 0.0);
  glEnd();
  //glBegin(GL_LINES);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, -100.0, 0.0);
  glVertex3f(0.0, 100.0, 0.0);
  glEnd();
  //glBegin(GL_LINES);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 0.0, -100.0);
  glVertex3f(0.0, 0.0, 100.0);
  glEnd();
	// Cây cắm hoa
	glBegin(GL_POLYGON);	
   	glColor4f( 1.0 , 1.0, 1.0, 0.3);
	glVertex3f(-0.01 , 0.8, 0.0);
        glVertex3f(0.01, 0.8, 0.0);
	glVertex3f(0.01,-0.69, 0.0);
	glVertex3f(-0.01,-0.69, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);	
   	glColor4f( 1.0 , 1.0, 1.0, 0.3);
	glVertex3f(-0.21 , 0.75, 0.0);
	glVertex3f(-0.19 , 0.75, 0.0);
       	glVertex3f(0.0 , 0.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);	
   	glColor4f( 1.0 , 1.0, 1.0, 0.3);
	glVertex3f( 0.28 , 0.75, 0.0);
	glVertex3f( 0.31 , 0.75, 0.0);
       	glVertex3f(0.0 , 0.2, 0.0);
	glEnd();

	glBegin(GL_POLYGON);	
   	glColor4f( 1.0 , 1.0, 1.0, 0.3);
	glVertex3f(-0.21 , 0.75, 0.0);
	glVertex3f(-0.19 , 0.75, 0.0);
       	glVertex3f(0.0 , 0.0, 0.0);
	glEnd();
	
   glBegin(GL_POLYGON);						//Front-T
   glColor4f(1.0, 0.0, 0.0, 0.3	);
   glVertex3f(-0.05,0.05, -0.3);
   glVertex3f(-0.3,0.5, -0.2);
   glVertex3f(0.3,0.5, -0.2);
   glVertex3f(0.05,0.05, -0.3);
   glEnd();

   glBegin(GL_POLYGON);						//Front-B
   glColor4f( 1.0, 0.0, 0.0, 0.6);
   glVertex3f(-0.3,-0.7, -0.2);
   glVertex3f(-0.05, -0.05, -0.3);
   glVertex3f(0.05,-0.05, -0.3);
   glVertex3f(0.3,-0.7, -0.2);
   glEnd();

   glBegin(GL_POLYGON);						//Front-R
   glColor4f( 0.76, 0.0, 0.0, 0.6);
   glVertex3f(0.05, 0.05, -0.3);
   glVertex3f(0.3, 0.5, -0.2);
   glVertex3f(0.3,-0.7, -0.2);
   glVertex3f(0.05,-0.05, -0.3);
   glEnd();

   glBegin(GL_POLYGON);		
   glColor4f( 0.76, 0.0, 0.0, 0.6);				//Front-L
   glVertex3f(-0.3,0.5, -0.2);
   glVertex3f(-0.05,0.05, -0.3);
   glVertex3f(-0.05,-0.05, -0.3);
   glVertex3f(-0.3,-0.7, -0.2);
   glEnd();

   glBegin(GL_POLYGON);						//RIGHT-T
   glColor4f( 1.0, 0.0, 0.0, 0.3);
   glVertex3f(0.4,0.05, -0.05);
   glVertex3f(0.3,0.5, -0.2);
   glVertex3f(0.3,0.5, 0.2);
   glVertex3f(0.4,0.05, 0.05);
   glEnd();

   glBegin(GL_POLYGON);						//RIGHT-B
   glColor4f( 1.0, 0.0, 0.0, 0.6);
   glVertex3f(0.3,-0.7, -0.2);
   glVertex3f(0.4,-0.05, -0.05);
   glVertex3f(0.4,-0.05, 0.05);
   glVertex3f(0.3,-0.7, 0.2);
   glEnd();

   glBegin(GL_POLYGON);						//RIGHT-R
   glColor4f( 0.76, 0.0, 0.0, 0.6);
   glVertex3f(0.4,0.05, 0.05);
   glVertex3f(0.3,0.5, 0.2);
   glVertex3f(0.3,-0.7, 0.2);
   glVertex3f(0.4,-0.05, 0.05);
   glEnd();

   glBegin(GL_POLYGON);		
   glColor4f( 0.76, 0.0, 0.0, 0.6);				//RIGHT-L
   glVertex3f(0.3,0.5, -0.2);
   glVertex3f(0.4,0.05, -0.05);
   glVertex3f(0.4,-0.05, -0.05);
   glVertex3f(0.3,-0.7, -0.2);
   glEnd();

   glBegin(GL_POLYGON);						//BACK-T
   glColor4f( 1.0, 0.0, 0.0, 0.3);
   glVertex3f(-0.05,0.05, 0.3);
   glVertex3f(-0.3,0.5, 0.2);
   glVertex3f(0.3,0.5, 0.2);
   glVertex3f(0.05,0.05, 0.3);
   glEnd();

   glBegin(GL_POLYGON);						//BACK-B
   glColor4f( 1.0, 0.0, 0.0, 0.6);
   glVertex3f(-0.3,-0.7, 0.2);
   glVertex3f(-0.05, -0.05, 0.3);
   glVertex3f(0.05,-0.05, 0.3);
   glVertex3f(0.3,-0.7, 0.2);
   glEnd();

   glBegin(GL_POLYGON);						//BACK-R
   glColor4f( 0.76, 0.0, 0.0, 0.6);
   glVertex3f(0.05, 0.05, 0.3);
   glVertex3f(0.3, 0.5, 0.2);
   glVertex3f(0.3,-0.7, 0.2);
   glVertex3f(0.05,-0.05, 0.3);
   glEnd();

   glBegin(GL_POLYGON);		
   glColor4f( 0.76, 0.0, 0.0, 0.6);				//BACK-L
   glVertex3f(-0.3,0.5, 0.2);
   glVertex3f(-0.05,0.05, 0.3);
   glVertex3f(-0.05,-0.05, 0.3);
   glVertex3f(-0.3,-0.7, 0.2);
   glEnd();


   glBegin(GL_POLYGON);						//LEFT-T
   glColor4f( 1.0, 0.0, 0.0, 0.3);
   glVertex3f(-0.4,0.05, -0.05);
   glVertex3f(-0.3,0.5, -0.2);
   glVertex3f(-0.3,0.5, 0.2);
   glVertex3f(-0.4,0.05, 0.05);
   glEnd();

   glBegin(GL_POLYGON);						//LEFT-B
   glColor4f( 1.0, 0.0, 0.0, 0.6);
   glVertex3f(-0.3,-0.7, -0.2);
   glVertex3f(-0.4,-0.05, -0.05);
   glVertex3f(-0.4,-0.05, 0.05);
   glVertex3f(-0.3,-0.7, 0.2);
   glEnd();

   glBegin(GL_POLYGON);						//LEFT-R
   glColor4f( 0.76, 0.0, 0.0, 0.6);
   glVertex3f(-0.4,0.05, 0.05);
   glVertex3f(-0.3,0.5, 0.2);
   glVertex3f(-0.3,-0.7, 0.2);
   glVertex3f(-0.4,-0.05, 0.05);
   glEnd();

   glBegin(GL_POLYGON);		
   glColor4f( 0.76, 0.0, 0.0, 0.6);				//LEFT-L
   glVertex3f(-0.3,0.5, -0.2);
   glVertex3f(-0.4,0.05, -0.05);
   glVertex3f(-0.4,-0.05, -0.05);
   glVertex3f(-0.3,-0.7, -0.2);
   glEnd();

   glBegin(GL_POLYGON);	
   glColor4f( 0.4, 0.13, 0.245, 1.0);	   				//BASE
   glVertex3f(-0.3,-0.7, -0.2);
   glVertex3f(-0.3,-0.7, 0.2);
   glVertex3f(0.3,-0.7, 0.2);
   glVertex3f(0.3,-0.7, -0.2);
   glEnd();
        // Flower one ---
        glColor3f(0.1, 0.72, 0.32);
        glPushMatrix();
        glTranslatef(0.25,0.7,0.0);
	glutSolidSphere(0.07,30,30);
        glPopMatrix();
    
	glColor3f(0.34, 0.21, 0.52);
        glPushMatrix();
        glTranslatef(0.3,0.76,0.0);
	glutSolidSphere(0.03,30,30);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.2,0.76,0.0);
	glutSolidSphere(0.03,30,30);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.25,0.76,0.0);
	glutSolidSphere(0.03,30,30);
        glPopMatrix();
 								//Flower two
        glBegin(GL_POLYGON);	
   	glColor4f( 0.35, 0.13, 0.245, 1.0);	   				
	glVertex3f(-0.35,0.75,0.0);
	glVertex3f(-0.3,0.8,-0.02);
	glVertex3f(-0.2,0.75,0.0);
	glVertex3f(-0.3,0.7,-0.02);
   	glEnd();

        glBegin(GL_POLYGON);
   	glColor4f( 0.4, 0.13, 0.245, 1.0);	   				
	glVertex3f(-0.2,0.75,0.0);
	glVertex3f(-0.1,0.8,-0.02);
	glVertex3f(-0.05,0.75,0.0);
	glVertex3f(-0.1,0.7,-0.02);
   	glEnd();

        glBegin(GL_POLYGON);
   	glColor4f( 0.45, 0.13, 0.245, 1.0);	   				
	glVertex3f(-0.2,0.75,0.0);
	glVertex3f(-0.25,0.85,-0.02);
	glVertex3f(-0.2,0.9,0.0);
	glVertex3f(-0.15,0.85,-0.02);
   	glEnd();

	glColor4f(0.0, 0.72, 0.32,0.2);
        glPushMatrix();
        glTranslatef(0.0,0.9,0.0);
	glutSolidSphere(0.1,90,90);
        glPopMatrix();
	
  glEnable(GL_LIGHTING);
}
// Hàm hiển thị
void RenderScene()
{
  glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt
  	(g_x, 1.0, g_z, 
	  0, 1.0, 0, 
	  0, 1, 0);
	
	DrawCoordinate();
	glTranslated(0.0,-1.5,0.1);
	
  glPushMatrix();
    glTranslated(0.4,0.4,0.6);
    glRotated(45,0,0,1);
    glScaled(0.08,0.08,0.08);
    glPopMatrix();
    glPushMatrix();
  	glTranslated(0.8,1.2,0.8);
    glRotated(20,0,1,0);
	
  Tea(0.4);
  glPopMatrix();
  glPushMatrix();
  glTranslated(0.25,0.42,0.35);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.5,0,0.5);
  table(1.5,0.06,0.06,0.8);
  
  glPopMatrix();
  wall(0.08);
  glPushMatrix();
  glRotated(90.0,0.0,0.0,1.0);    
	
  glPopMatrix();

  glPushMatrix();
  glRotated(-90.0,1.0,0.0,0.0);  
	
  glPopMatrix();
   glPushMatrix();
   
  	glTranslated(0.3,0.38,0.5);
    glRotated(30,0,1,0);

     glPopMatrix();

     glFlush();
}
int main()
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Ban tra 3D su dung Opengl");
  Init();
  glutReshapeFunc(ReShape);
  glutDisplayFunc(RenderScene);
  glutIdleFunc(RenderScene);
  glutSpecialFunc(OnKeyDown);
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove);
  glutMainLoop();
 
  return 0;
}
