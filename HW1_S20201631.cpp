#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

int dot_cnt = 0;															// count the number of dots
int polymode = 0, rclicked = 0, rotmode = 0;								// flag of polygon formed, and right click, and rotation
int winw = 450, winh = 300;													// half of the window size width, height
int xpre, ypre;																// coordinates of the right-clicked mouse
GLfloat xcom, ycom;															// coordinates of the center of mass
float r = 236.0f / 255.0f, g = 235.0f / 255.0f, b = 189.0f / 255.0f;		// background color : spring green
float dots[128][2];															// info of the dots' originall coordinates
GLfloat dotsf[128][2];														// info of the dots' coordinates (gl version)

// change coordinate into gl version
void coord_change(void) {
	for (int i = 0; i < dot_cnt; i++) {
		dotsf[i][0] = (GLfloat)(dots[i][0] - winw) / winw;					// change x-coordinate to gl version
		dotsf[i][1] = (GLfloat)(winh - dots[i][1]) / winh;					// change y-coordinate to gl version
	}
}

// rotate dots when rotate mode is activated
void rotate_dots(void)
{
	float tran[2], rot[2];

	for (int i = 0; i < dot_cnt; i++) {
		tran[0] = dotsf[i][0] - xcom;										// translate com point to (0,0)
		tran[1] = dotsf[i][1] - ycom;
		rot[0] = tran[0] * 0.99619470 - tran[1] * 0.08715574;				// rotate translated points 10 degrees
		rot[1] = tran[0] * 0.08715574 + tran[1] * 0.99619470;				// sin 10 = 0.08715574 , cos 10 = 0.99619470
		dotsf[i][0] = rot[0] + xcom;										// translate (0,0) to com point and reassign
		dotsf[i][1] = rot[1] + ycom;
	}
}

// do things that should be repeated in short period
void timer(int value) {
	rotate_dots();															// change dot coordinates to rotated version
	glutPostRedisplay();
	if (rotmode)															// if the polygon is rotating :
		glutTimerFunc(10, timer, 0);										// call timer function every 10 milliseconds
}

// draw dots to the screen
void draw_dots(void)
{
	glPointSize(5.0f);														// set dot size to 5.0
	glBegin(GL_POINTS);														// start drawing dots
	if (rotmode) {															// if the polygon is rotating :
		glColor3f(0.0f, 0.0f, 1.0f);										// set com color to green
		glVertex2f(xcom, ycom);												// draw center of mass at the screen
	}
	glColor3f(0.0f, 0.0f, 0.0f);											// set dot color to black
	for (int i = 0; i < dot_cnt; i++)
		glVertex2fv(dotsf[i]);												// draw dots at the screen
	glEnd();																// end drawing dots
}

// draw lines to the screen
void draw_lines(void)
{
	glColor3f(1.0f, 0.0f, 0.0f);											// set line color to red
	glLineWidth(2.0f);														// set line width to 2.0
	glBegin(GL_LINE_STRIP);													// start drawing lines
	for (int i = 0; i < dot_cnt - 1; i++) {
		glVertex2fv(dotsf[i]);												// connect i-th dot and the (i+1)-th dot
		glVertex2fv(dotsf[i + 1]);											//
	}
	if (polymode) {															// if the polygon is formed :
		glVertex2fv(dotsf[0]);												// connect last dot and the first dot
		glVertex2fv(dotsf[dot_cnt - 1]);									//
	}
	glEnd();																// end drawing lines
}

// calculate center of mass
GLfloat cal_com(int cmd)
{
	float com = 0;

	for (int i = 0; i < dot_cnt; i++)
		com += dots[i][cmd];												// add every coordinate of the dot to com

	return (GLfloat)(com/dot_cnt);											// reture the center of mass value
}

// display
void display(void)
{
	glClearColor(r, g, b, 1.0f);											// set background color
	glClear(GL_COLOR_BUFFER_BIT);

	draw_dots();															// draw every dots to the screen
	if (dot_cnt > 1)														// if there are 2 or more dots :
		draw_lines();														// draw every lines to the screen

	glFlush();
}

// keyboard input
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'f' :
		glutLeaveMainLoop();												// end program
		break;
	case 'p' :
		if (dot_cnt < 3)													// if there are 2 or less dots :
			fprintf(stdout, "Warning : Choose at least three points!\n");	// error message
		else {																// if there are more than three dots :
			polymode = 1;													// form polygon
			glutPostRedisplay();
		}
		break;
	case 'c' :
		if (!rotmode) {														// if the polygon is not rotating :
			dot_cnt = 0;													// reset dot number
			polymode = 0;													// dismiss polygon
			glutPostRedisplay();
		}
		break;
	case 'r' :
		if (polymode) {														// if the polygon is formed :
			if (rotmode)													// if the polygon is rotating :
				rotmode = 0;												// stop rotate
			else {															// if the polygon is not rotating :
				xcom = (GLfloat)(cal_com(0) - winw) / winw;					// calculate the x-coordinate of center of mass
				ycom = (GLfloat)(winh - cal_com(1)) / winh;					// calculate the y-coordinate of center of mass
				rotmode = 1;												// start rotate
				glutTimerFunc(10, timer, 0);								// start timer function after 10 milliseconds
			}
			glutPostRedisplay();
		}
		break;
	}

}

// keyboard input - for special keys
void specialkey(int key, int x, int y)
{
	if (polymode && !rotmode) {												// if the polygon is formed and not rotating :
		int i;
		GLfloat tick = 0.02f;												// tick : amount of movement when arrow keys are pressed
		switch (key) {
		case GLUT_KEY_LEFT:
			for (i = 0; i < dot_cnt; i++)
				dotsf[i][0] -= tick;										// go left by tick size
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			for (i = 0; i < dot_cnt; i++)
				dotsf[i][0] += tick;										// go right by tick size
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
			for (i = 0; i < dot_cnt; i++)
				dotsf[i][1] += tick;										// go up by tick size							
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			for (i = 0; i < dot_cnt; i++)
				dotsf[i][1] -= tick;										// go down by tick size
			glutPostRedisplay();
			break;
		}
		
	}
}

// press mouse
void mouse(int button, int state, int x, int y)
{
	if (!polymode) {														// if the polygon is not formed :
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && glutGetModifiers() && GLUT_ACTIVE_SHIFT) {
																			// if left-clicked and Shift is pressed :
			dots[dot_cnt][0] = x;											// assign x-coordinate
			dots[dot_cnt][1] = y;											// assign y-coordinate
			dot_cnt++;														// increase number of dots
			coord_change();													// update gl version coordinate
		}
	}
	else {																	// if the polygon is formed :
		if (!rotmode) {														// if the polygon is not rotating :
			if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {	// if right-clicked :
				rclicked = 1;												// start rclick move
				xpre = x;													// save present location of the mouse
				ypre = y;													//
			}
			else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP))	// if right click released :
				rclicked = 0;												// stop rclick move
		}
	}
	glutPostRedisplay();
}

// move mouse
void motion(int x, int y)
{
	if (rclicked) {															// if right-clicked :
		int xdist = x - xpre;												// distance between present mouse location and the previous one
		int ydist = y - ypre;												//
		for (int i = 0; i < dot_cnt; i++) {
			dots[i][0] += xdist;											// update distance
			dots[i][1] += ydist;											//
			coord_change();													// update gl version coordinate
		}
		xpre = x;															// update present mouse location
		ypre = y;															//
		glutPostRedisplay();
	}
}

// reshape window
void reshape(int width, int height)
{
	float rw = (float)width / (winw * 2);									// the width ratio
	float rh = (float)height / (winh * 2);									// the height ratio
	winw = width / 2;														// update window size
	winh = height / 2;														//
	
	glViewport(0, 0, width, height);										// update gl viewport size to changed window size

	for (int i = 0; i < dot_cnt; i++) {
		dots[i][0] *= rw;													// change the coordinate by the ratio
		dots[i][1] *= rh;													//
	}
	coord_change();															// update gl version coordinate

	glutPostRedisplay();
}

// close
void close(void)
{
	fprintf(stdout, "*** Program finished. Bye! ***\n");					// show that the program ended
}

// register callbacks
void register_callbacks(void)
{
	glutDisplayFunc(display);												// when display should be updated
	glutKeyboardFunc(keyboard);												// when keyboard keys is pressed
	glutSpecialFunc(specialkey);											// when special keys (not ASCII) is pressed
	glutMouseFunc(mouse);													// when mouse is pressed
	glutMotionFunc(motion);													// when mouse is moved
	glutReshapeFunc(reshape);												// when window is reshaped
	glutCloseFunc(close);													// when program is closed
}

// initialize glew
void initialize_glew(void)
{
	GLenum error;

	glewExperimental = TRUE;
	error = glewInit();
	if (error != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));			// show error messages
		exit(-1);
	}

	fprintf(stdout, "*********************************************************\n");
	fprintf(stdout, " - GLEW version supported: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, " - OpenGL renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, " - OpenGL version supported: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "*********************************************************\n\n");
}

// print greeting messages to the console screen
void greetings(char* program_name, char messages[][256], int n_message_lines) {
	fprintf(stdout, "**************************************************************\n\n");
	fprintf(stdout, "  PROGRAM NAME: %s\n\n", program_name);				// show program names

	for (int i = 0; i < n_message_lines; i++)
		fprintf(stdout, "%s\n", messages[i]);								// show messages
	fprintf(stdout, "\n**************************************************************\n\n");

	initialize_glew();
}

// initialize renderer
void initialize_renderer(void) {
	register_callbacks();
}

#define N_MESSAGE_LINES 4
void main(int argc, char* argv[])
{
	char program_name[64] = "CSE4170 Homework1 - 20201631";					// title of the program
	char messages[N_MESSAGE_LINES][256] = {									// instruction of the program
		"    - Keys used : 'c', 'f', 'p', 'r' ",							// used key information
		"    - Special keys used : LEFT, RIGHT, UP, DOWN",					// used special key information
		"    - Mouse used : SHIFT + L-click, R-click and move",				// used mouse actions
		"    - Other operations : window size change"						// extra operations
	};

	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_RGBA);

	glutInitWindowSize(winw * 2, winh * 2);									// set the size of window
	glutInitWindowPosition(300, 100);										// set the position of window
	glutCreateWindow(program_name);											// create window with title of program_name

	greetings(program_name, messages, N_MESSAGE_LINES);						// show greeting messages
	initialize_renderer();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
}