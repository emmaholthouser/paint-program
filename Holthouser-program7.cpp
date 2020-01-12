//Emma Holthouser
//November 5th
//Assignment 7
//This program is a sketching program that allows a user to choose from a palette of colors and draw using that color
//I worked with Dylan Payne and Alex Robinson, and Meghan Grayson


#ifdef __APPLE__
#  include <OpenGL/gl.h>  // definitions for GL graphics routines
#  include <OpenGL/glu.h> // definitions for GL input device handling
#  include <GLUT/glut.h>  // deginitions for the GLUT utility toolkit
#else
#  include <GL/gl.h>      // definitions for GL graphics routines
#  include <GL/glu.h>     // definitions for GL input device handling
#  include <GL/glut.h>    // deginitions for the GLUT utility toolkit
#endif
#include "sketch.h"
#include <iostream>       // definitions for standard I/O routines
#include <cmath>          // definitions for math library
using namespace std;

#define WIDTH       500          // window dimensions
#define HEIGHT      300

#define MENUWIDTH   100          // menu dimensions
#define BOXHEIGHT   (HEIGHT / 10)
#define BOXWIDTH    MENUWIDTH
#define TOOLBOXHIEGHT (HEIGHT / 10)


#define NCOLORS     10           // number of colors
#define NTOOlS      10          //number of tools
#define RGBRED      1, 0, 0      // RGB Colors for menu
#define RGBGREEN    0, 1, 0
#define RGBBLUE     0, 0, 1
#define RGBYELLOW   1, 1, 0
#define RGBTEAL     0, 1, 1
#define RGBWHITE    1, 1, 1
#define RGBPURPLE   1, 0, 1
#define RGBORANGE   1, .5, 0
#define RGBGREY     0.70, 0.70, 0.70   // for screen background
#define DARKPURPLE  .7, 0, 1

#define WLEFT       0
#define WRIGHT      WIDTH
#define WBOTTOM     0
#define WTOP        HEIGHT

#define RGBBLACK    0, 0, 0      // black for screen background

#define R    0
#define G    1
#define B    2

static int tracking = 0;
int prevx;
int prevy;
int dx = WIDTH - MENUWIDTH/2;
short int currenttool = 0;
short int currentcolor = 0;

Sketch mySketch;


/*static float colormenu[][9] = {{RGBRED}, {RGBGREEN}, {RGBBLUE}, {RGBTEAL}, {RGBYELLOW}, {RGBGREY}, {RGBPURPLE}, {RGBORANGE}, {RGBWHITE}, {DARKPURPLE}};


Returns true if point (x, y) is in the window
*/
int inwindow(int x, int y) {
    
    return (x > MENUWIDTH && x < (WIDTH - MENUWIDTH) && y > 0 && y < HEIGHT);
}

/*
 Draw a line to new mouse position
 */



/*
 Returns true if point (x, y) is in the color menu
 */
int incolormenu(int x, int y) {
    
    return (x >= 0 && x <= MENUWIDTH && y >= 0 && y <= HEIGHT);
}


/*
 Returns index of point (x, y) in the color menu
 */
int colormenuindex(int x, int y) {
    
    if(!incolormenu(x, y))
        return -1;
    else
        return(y / BOXHEIGHT);
}


//checking the location
int intoolsmenu(int x, int y){
    return (x >= WIDTH - MENUWIDTH && x<= WIDTH && y >= 0 && y <= HEIGHT);
}

//seeing in in the tool menu
int toolsmenuindex(int x, int y){
    if(!intoolsmenu(x, y))
        return -1;
    else
        currenttool = (y/TOOLBOXHIEGHT);
    //cout << " curretn tool " <<currenttool;
        return(y/BOXHEIGHT);
}






/*
 Watch mouse button presses and handle them
 */
void handleButton(int button, int state, int x, int y){
    
    static int menuindex = -1;
    static int toolsindex = -1;
    
    y = HEIGHT - y;   // reverse y, so zero at bottom, and max at top
    
    if(button != GLUT_LEFT_BUTTON)   // ignore all but left button
        return;
    
    /*
     if button pressed and released in same menu box, then update
     the color of the large square
     */
    if(state == GLUT_DOWN){
        if(incolormenu(x, y))
        {
            currentcolor = colormenuindex(x, y); }
        
               //if(toolsmenuindex)
        
            
       else if(inwindow(x, y)) {
            tracking = 1;
            
            
            //glEnd();
           //creatomg the object based on tool type
            switch(currenttool)
            {
                case 0:
                    //cout << "0";
                    mySketch.createObject(currentcolor, currenttool, x, y, prevx, prevy);
                    cout << "created an object";
                    break;
                case 1:
                   mySketch.createObject(currentcolor, currenttool,  x, y, prevx, prevy);
                    break;
                case 2:
                   mySketch.createObject(currentcolor, currenttool, x, y, 0);
                    break;
                case 3:
                     mySketch.createObject(currentcolor, currenttool, x, y, 0);
                    break;
                case 4:
                    mySketch.createObject(currentcolor, currenttool,  x, y, prevx, prevy);
                    break;
                case 5:
                    mySketch.createObject(currentcolor, currenttool,  x, y, prevx, prevy);
                    break;
                    
            }
            
            prevx = x;
            prevy = y;
        }
   //checking to see if in the tools menu
    else if(intoolsmenu(x, y)){
        int toolsindex = toolsmenuindex(x, y);
        
        switch(toolsindex)
        {
            case 0:
                //cout << "0";
                currenttool = toolsindex;
                break;
            case 1:
                //cout << "1";
                currenttool = toolsindex;
                break;
            case 2:
                //cout << "2";
                currenttool = toolsindex;
                
                break;
            case 3:
                //cout << "3";
                currenttool = toolsindex;
                
                break;
            case 4:
                //cout << "4";
                currenttool = toolsindex;
                break;
            case 5:
               // cout << "5";
                currenttool = toolsindex;
                break;
            case 6:
                //cout << "6";
                if(mySketch.load())
                {
                    cout << "sketch is loading";
                    glutPostRedisplay();
                }
                
                break;
            case 7:
                //cout << "7";
                mySketch.save();
                break;
            case 8:
                //cout << "8";
                mySketch.clear();
                glutPostRedisplay();
                break;
            case 9:
                //cout << "9";
                exit(0);
                break;
        }
    }
    else{
        if(incolormenu(x, y) && colormenuindex(x, y) == menuindex){
            glColor3f(colormenu[menuindex][R], colormenu[menuindex][G],
                      colormenu[menuindex][B]);
        }
        
        }
}
    
}

/*
 Draw the colored box and the color menu
 */

void m_Motion(int x, int y) {
    
    y = WTOP - y;
    
    if(tracking && inwindow(x, y)) {
        /*glBegin(GL_LINES);
         glVertex2i(prevx, prevy);
         glVertex2i(x, y);
       */
     
        switch(currenttool)
        {
            case 0:
                mySketch.updateObject(x, y);
                break;
            case 1:
                mySketch.updateObject(x, y);
                break;
            case 2:
                mySketch.updateObject(x, y);
                break;
            case 3:
                mySketch.updateObject(x, y);
                break;
            case 4:
                mySketch.updateObject(x, y);
                break;
            case 5:
                mySketch.updateObject(x, y);
                mySketch.createObject(currentcolor, currenttool, prevx, prevy, x, y);
               
                break;
                
        }
        
        
    }
    prevx = x;
    prevy = y;
    glutPostRedisplay();
}


void drawTools()
{
    int i;
    int dx = 200;
    int dy = 200;
    
    // draw the color menu
    for(i = 0; i < 10; i++){
                glColor3f(.7, .7, .7);
                glRecti(WIDTH- MENUWIDTH, TOOLBOXHIEGHT * i + 1,
                WIDTH + MENUWIDTH, TOOLBOXHIEGHT * (i + 1) - 1);
    }
    //drawing the unfilled square icon
    
    glLineWidth(1);
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(450,15 , 0);
    glScalef(20, 10, 1);
    mySketch.dRectangle(2, -1, -1, 1, 1);
    glPopMatrix();
    //drawing the filled square icon
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(450,45 , 0);
    glScalef(20, 10, 1);
    mySketch.dRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();
    //unfilled circle icon
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(460,85 , 0);
    glScalef(10, 10, 1);
    mySketch.dCircle(GL_LINE_LOOP, -1, -1, 1);
    glPopMatrix();
    //filled cirlce icon
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(460,115 , 0);
    glScalef(10, 10, 1);
    mySketch.dCircle(GL_POLYGON, -1, -1, 1);
    glPopMatrix();
    
    //straight line
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(450,135 , 0);
    glScalef(10, 10, 1);
    mySketch.dLine(GL_LINE, -1, -1, 1, 1);
    glPopMatrix();
    
    //free form line
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(438, 162, 0);
    glScalef(6, 5, 1);
    mySketch.dLine(GL_LINE, -1, -1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(461, 165, 0);
    glScalef(5, 8, 1);
    mySketch.dLine(GL_LINE, -1, -1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(450, 163, 0);
    glScalef(6, 7, 1);
    mySketch.dLine(GL_LINE, -1, 1, 1, -1);
    glPopMatrix();
    
    
    
    
    //x for clear icon
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(450,285 , 0);
    glScalef(10, 10, 1);
    mySketch.dLine(GL_LINE, -1, -1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(450,285 , 0);
    glScalef(10, 10, 1);
    mySketch.dLine(GL_LINE, -1, 1, 1, -1);
    glPopMatrix();
    
    //clear
    glPushMatrix();
    glLineWidth(3);
    glColor3f(1, 1, 1);
    glTranslatef(460,265 , 0);
    glScalef(10, 10, 1);
    mySketch.dCircle(GL_LINE_LOOP, -1, -1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(.7, .7, .7);
    glTranslatef(467,257 , 0);
    glScalef(10, 10, 1);
    mySketch.dRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();
    
    //l for load
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(450,195 , 0);
    glScalef(10, 10, 1);
    mySketch.dLine(GL_LINE, -1, -1, -1, 1);
    glPopMatrix();
    //bottom of L
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(450,195 , 0);
    glScalef(10, 10, 1);
    mySketch.dLine(GL_LINE, -1, -1, 1, -1);
    glPopMatrix();
    
    //save - floppy disk icon
    glLineWidth(1);
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(450,225 , 0);
    glScalef(10, 10, 1);
    mySketch.dRectangle(2, -1, -1, 1, 1);
    glPopMatrix();
    //little square for floppy disk
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(450,220, 0);
    glScalef(3, 3, 1);
    mySketch.dRectangle(2, -1, -1, 1, 1);
    glPopMatrix();
   
}

void drawMenu() {
    
    int i;
    
    // clear window
    //glClear(GL_COLOR_BUFFER_BIT);
    
    // draw the color menu
    for(i = 0; i < NCOLORS; i++){
        glColor3f(colormenu[i][R], colormenu[i][G], colormenu[i][B]);
        glRecti(1, BOXHEIGHT * i + 1,
                BOXWIDTH - 1, BOXHEIGHT * (i + 1) - 1);
    }
    
    
    /*for(i = 0; i < NCOLORS/2; i++){
     glColor3f(colormenu[i][R], colormenu[i][G], colormenu[i][B]);
     glRecti(, BOXHEIGHT * i + 1,
     BOXWIDTH - 1, BOXHEIGHT * (i + 1) - 1);
     }*/
    
}

void drawMouse()
{
    int i;
    glClearColor(RGBBLACK, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(colormenu[i][R], colormenu[i][G], colormenu[i][B]);
    
}

               
void drawScene(){
    glClear(GL_COLOR_BUFFER_BIT);
    mySketch.draw();
    drawMenu();
    drawTools();
    glutSwapBuffers();
}

/*
 Main program
 */
int main(int argc, char* argv[]) {
    
    glutInit(&argc, argv);
    
    // open window and establish coordinate system on it
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Color Menu");
    //glutCreateWindow("mouse motion");
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    
    // register display and mouse-button callback routines
    //glutDisplayFunc(drawTools);
    
    glutDisplayFunc(drawMouse);
    glutMouseFunc(handleButton);
    glutMotionFunc(m_Motion);
    glutDisplayFunc(drawScene);
    // Set up to clear screen to black
    glClearColor(RGBBLACK, 1);
    
    glutMainLoop();
    
    return 0;
}
