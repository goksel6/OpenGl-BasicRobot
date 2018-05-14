#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

static GLint angle = 2; //DÖNME AÇISI
double xr=0.0, yr=0.0, zr = 0.0;
int flag = 5;
GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul, *n, *s; //QUADRİC OBJELER POİNTER DİZİSİ

#pragma region UZUV BOYUTLARI

#define TORSO_HEIGHT 5.0

#define SHOULDER_HEIGHT 0.25
#define SHOULDER_RADIUS 0.3

#define UPPER_ARM_HEIGHT 3.0
#define LOWER_ARM_HEIGHT 2.0

#define UPPER_LEG_RADIUS  0.4
#define LOWER_LEG_RADIUS  0.4

#define LOWER_LEG_HEIGHT 2.0
#define UPPER_LEG_HEIGHT 3.0

#define TORSO_RADIUS 1.0

#define UPPER_ARM_RADIUS  0.4
#define LOWER_ARM_RADIUS  0.4

#define HEAD_HEIGHT 1.5
#define HEAD_RADIUS 1.0

#define NECK_RADIUS 0.25
#define NECK_HEIGHT 0.6

#pragma endregion

#pragma region UZUVLARIN İLK DOĞRULTULARI

/* AÇILAR AYARLANDI. AYAKLAR 180 DERECE, DİĞERLERİ 0 DERECE OLARAK.
ROBOT X EKSENİ DOĞRULTUSUNDA DURMAKTA YANİ Y EKSENİ YATAY EKSENDİR.*/
static GLfloat theta[11] =
{
	0.0,0.0,0.0,0.0,0.0,0.0,0.0,
	180.0,0.0,180.0,0.0
};

#pragma endregion

#pragma region UZUVLAR

void stair()
{
	glPushMatrix();
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
									  // Top face (y = 1.0f)
									  // Define vertices in counter-clockwise (CCW) order with normal pointing out
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube
	glPopMatrix();
}

void torso()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(t, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_shoulder()
{
	glPushMatrix();
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	gluCylinder(s, SHOULDER_RADIUS, SHOULDER_RADIUS,SHOULDER_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_shoulder()
{
	glPushMatrix();
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	gluCylinder(s, SHOULDER_RADIUS, SHOULDER_RADIUS, SHOULDER_HEIGHT, 10, 10);
	glPopMatrix();

}

void neck()
{
	glPushMatrix();
	glTranslatef(0.0, TORSO_HEIGHT, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(n, NECK_RADIUS, NECK_RADIUS, NECK_HEIGHT, 10, 10);
	glPopMatrix();
}

void head()
{
	glPushMatrix();
	glTranslatef(0.0, 0.5 + HEAD_HEIGHT, 0.0);
	glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);	
	gluSphere(h, 1.0, 10, 10);
	glPopMatrix();
}

void left_upper_arm()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_lower_arm()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_upper_arm()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_lower_arm()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_upper_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void left_lower_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_upper_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

void right_lower_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
	glPopMatrix();
}

#pragma endregion


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	//glPushMatrix();
	glLoadIdentity();
	//MERDİVEN
	glTranslatef(0.0, -4.0, 15.0);
	stair();
	glTranslatef(-2.0, 1.0, 0.0);
	glScalef(1.0, 2.0, 1.0);
	stair();
	glTranslatef(-2.0, 0.5, 0.0);
	glScalef(1.0, 1.5, 1.0);
	stair();

	//ROBOT
	glScaled(0.5, 0.2, 1.0);
	glTranslatef(17.0, 0.0, 0.0);
	glTranslated(xr, yr, zr);
	torso();
	glPushMatrix();

	
	

	//TÜM BEDEN
	neck();
	

	glRotatef(theta[0], 0.0, 1.0, 0.0);
	torso();
	glPushMatrix();

	//KAFA
	glTranslatef(0.0, TORSO_HEIGHT + 0.5*HEAD_HEIGHT, 0.0);
	glRotatef(theta[2], 0.0, 1.0, 0.0);
	glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);
	head();
	
	//SAĞ OMUZ
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.9, TORSO_HEIGHT - 0.5, 0.0);
	right_shoulder();

	//SOL OMUZ
	glPopMatrix();
	glPushMatrix();
	glTranslated(1.2, TORSO_HEIGHT - 0.5, 0.0);
	left_shoulder();

	//SOL KOL
	glPopMatrix();
	glPushMatrix();
	glTranslated(-(TORSO_RADIUS + UPPER_ARM_RADIUS), 0.83*TORSO_HEIGHT, 0.0);
	glRotatef(theta[3], 1.0, 0.0, 0.0);
	left_upper_arm();

	glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
	glRotatef(theta[4], 1.0, 0.0, 0.0);
	left_lower_arm();

	//SAĞ KOL
	glPopMatrix();
	glPushMatrix();
	glTranslated(TORSO_RADIUS + UPPER_ARM_RADIUS, 0.83*TORSO_HEIGHT, 0.0);
	glRotatef(theta[5], 1.0, 0.0, 0.0);
	right_upper_arm();

	glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
	glRotatef(theta[6], 1.0, 0.0, 0.0);
	right_lower_arm();

	//SOL AYAK
	glPopMatrix();
	glPushMatrix();
	glTranslated(-(TORSO_RADIUS + UPPER_LEG_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[7], 1.0, 0.0, 0.0);
	left_upper_leg();

	glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[8], 1.0, 0.0, 0.0);
	left_lower_leg();

	//SAĞ AYAK
	glPopMatrix();
	glPushMatrix();
	glTranslated(TORSO_RADIUS + UPPER_LEG_RADIUS, 0.1*UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[9], 1.0, 0.0, 0.0);
	right_upper_leg();

	glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
	glRotatef(theta[10], 1.0, 0.0, 0.0);
	right_lower_leg();


	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void keyboard(unsigned char btn, int x, int y)
{
	//SOLA DÖNÜŞ
	if (btn == 'A' )
	{
		theta[angle] += 5.0;
		if (theta[angle] > 360.0) theta[angle] -= 360.0;
	}
	//SAĞA DÖNÜŞ
	if (btn == 'D')
	{
		theta[angle] -= 5.0;
		if (theta[angle] < 360.0) theta[angle] += 360.0;
	}
	//MERDİVENİ ÇIKMAK
	if (btn== 'W') 
	{
		//MERDİVENİN ÖNÜNE GELİP GELMEDİĞİNİN KONTROLÜ
		if (zr == -1 && xr == -5) 
		{
			yr = yr + 3.3;
			xr = xr - 3.8;
			cout << y << endl;
			glutPostRedisplay();
			flag = 2;
		}
		//MERDİVEN BİTİNCE DURMASINI SAĞLAR
		else if (flag==2 || flag==1)
		{
			yr = yr + 3.3;
			xr = xr - 3.8;
			cout << y << endl;
			glutPostRedisplay();
			flag--;
		}
	}
	
	//ROBOTU BAŞLANGIÇ NOKTASINA GERİ DÖNDÜRÜR
	if (btn=='R')
	{		
			yr = 0;
			xr = 0;
			cout << y << endl;
			glutPostRedisplay();			
	}
	display();
}
void specialkey(int key, int x, int y)
{
	//ROBOTUN YÖN TUŞLARI İLE HAREKETİNİN SAĞLANMASI
	switch (key)
	{
	case GLUT_KEY_UP:
		zr ++;
		cout << y << endl;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		zr --;
		cout << y << endl;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		xr--;
		cout << y << endl;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		xr++;
		cout << y << endl;
		glutPostRedisplay();
		break;
	default:
		break;
	}
	display();

}

void menu(int id)
{
	if (id <11) 
		angle = id;
	else if (id == 11)
		exit(0);
}

void myReshape(int w, int h)
{
	glViewport(0, 0,(GLsizei) w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	if (w <= h)
		glOrtho(-10.0, 10.0, -10.0 * (GLfloat)h / (GLfloat)w,
			10.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-10.0 * (GLfloat)w / (GLfloat)h,
			10.0 * (GLfloat)w / (GLfloat)h, 0.0, 10.0, -10.0, 10.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void myinit()
{
	//IŞIK VE AYDINLATMA AYARLARI
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess = { 100.0 };

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);

	/* allocate quadrics with filled drawing style */

	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	n = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	s = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	t = gluNewQuadric();
	gluQuadricDrawStyle(t, GLU_FILL);
	lua = gluNewQuadric();
	gluQuadricDrawStyle(lua, GLU_FILL);
	lla = gluNewQuadric();
	gluQuadricDrawStyle(lla, GLU_FILL);
	rua = gluNewQuadric();
	gluQuadricDrawStyle(rua, GLU_FILL);
	rla = gluNewQuadric();
	gluQuadricDrawStyle(rla, GLU_FILL);
	lul = gluNewQuadric();
	gluQuadricDrawStyle(lul, GLU_FILL);
	lll = gluNewQuadric();
	gluQuadricDrawStyle(lll, GLU_FILL);
	rul = gluNewQuadric();
	gluQuadricDrawStyle(rul, GLU_FILL);
	rll = gluNewQuadric();
	gluQuadricDrawStyle(rll, GLU_FILL);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Robot");
	myinit();
	glutSpecialFunc(specialkey);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	

	glutCreateMenu(menu);
	glutAddMenuEntry("torso", 0);
	glutAddMenuEntry("head", 2);
	glutAddMenuEntry("right_upper_arm", 3);
	glutAddMenuEntry("right_lower_arm", 4);
	glutAddMenuEntry("left_upper_arm", 5);
	glutAddMenuEntry("left_lower_arm", 6);
	glutAddMenuEntry("right_upper_leg", 7);
	glutAddMenuEntry("right_lower_leg", 8);
	glutAddMenuEntry("left_upper_leg", 9);
	glutAddMenuEntry("left_lower_leg", 10);
	glutAddMenuEntry("quit", 11);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutMainLoop();
}