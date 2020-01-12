
//I worked with jonas simposn, an dylan payne, and Alex robinson, and Amanda



#ifdef __APPLE__
#  include <OpenGL/gl.h>  // definitions for GL graphics routines
#  include <OpenGL/glu.h> // definitions for GL input device handling
#  include <GLUT/glut.h>  // deginitions for the GLUT utility toolkit
#else
#  include <GL/gl.h>      // definitions for GL graphics routines
#  include <GL/glu.h>     // definitions for GL input device handling
#  include <GL/glut.h>    // deginitions for the GLUT utility toolkit
#endif
#include <string>
#include <iostream>       // definitions for standard I/O routines
#include <cmath>          // definitions for math library
#include <fstream>


double PI = 3.1415926536;     //mathematical pi, not apple pie

#include "sketch.h"

//distance formula
int distance(int x1, int y1, int x2, int y2)
{
    return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}
//creating rectangle and lines objects
void Sketch::createObject(short int c, short int t, int x1, int y1, int x2, int y2 )
{
    objects[n].colorType = c;
    objects[n].toolType = t;
    objects[n].tool.endpoints.pt1.x = x1;
    objects[n].tool.endpoints.pt1.y = y1;
    objects[n].tool.endpoints.pt2.x = x2;
    objects[n].tool.endpoints.pt2.y = y2;
    n++;
}
//creating circle objects
void Sketch::createObject(short int c, short int t, int x1, int y1, int r)
{
    objects[n].colorType = c;
    objects[n].toolType = t;
    objects[n].tool.circle.center.x = x1;
    objects[n].tool.circle.center.y = y1;
    objects[n].tool.circle.radius = r;
    n++;
}
//changing the size of the object
void Sketch::updateObject(int x2, int y2)
{
    if(objects[n-1].toolType == 2 || objects[n-1].toolType == 3)
    {
        objects[n -1].tool.circle.radius = distance(objects[n-1].tool.circle.center.x, objects[n-1].tool.circle.center.y, x2, y2);
    }
    else
    {
        objects[n-1].tool.endpoints.pt2.x = x2;
        objects[n-1].tool.endpoints.pt2.y = y2;
    }

}

//drawing the object to the screen

void Sketch::draw()
{
    for(int i = 0; i < n; i++)
    {
        int c = objects[i].colorType;
        glColor3f(colormenu[c][R], colormenu[c][G], colormenu[c][B]);
        switch(objects[i].toolType)
        {
          case 0:
            dRectangle(GL_LINE_LOOP, objects[i].tool.endpoints.pt1.x, objects[i].tool.endpoints.pt1.y, objects[i].tool.endpoints.pt2.x, objects[i].tool.endpoints.pt2.y);
            break;
          case 1:
            dRectangle(GL_POLYGON, objects[i].tool.endpoints.pt1.x, objects[i].tool.endpoints.pt1.y, objects[i].tool.endpoints.pt2.x, objects[i].tool.endpoints.pt2.y);
            break;
          case 2:
            dCircle(GL_LINE_LOOP, objects[i].tool.endpoints.pt1.x, objects[i].tool.endpoints.pt1.y, objects[i].tool.circle.radius);
            break;
          case 3:
            dCircle(GL_POLYGON, objects[i].tool.endpoints.pt1.x, objects[i].tool.endpoints.pt1.y, objects[i].tool.circle.radius);
            break;
         case 4:
                dLine(GL_LINE, objects[i].tool.endpoints.pt1.x, objects[i].tool.endpoints.pt1.y, objects[i].tool.endpoints.pt2.x, objects[i].tool.endpoints.pt2.y);
            break;
        case 5:
                 dLine(GL_LINE, objects[i].tool.endpoints.pt1.x, objects[i].tool.endpoints.pt1.y, objects[i].tool.endpoints.pt2.x, objects[i].tool.endpoints.pt2.y);
            break;
            
            
        }
    }
}

//circle formula
void circle(int num, GLint dType)
{
    int i = num;
    int ainc = 2 * PI / i;
    
    glBegin(dType);
    for(int k = 0; k < 36; k++)
    {
        int angle = k * ainc;
        glVertex2f(cos(angle), sin(angle));
        glEnd();
    }
}
//drawing rectangle
void Sketch::dRectangle(GLint drawType, int x1, int y1, int x2, int y2)
{
    glBegin(drawType);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();

}
//drawing circle
void Sketch::dCircle(GLint drawType, int x1, int y1, int r)
{
    //cout << "circle fun";
    glBegin(drawType);
    for(int i = 0; i < 36; i++)
    {
        float angle = i * ((2* 3.141592) / 36);
        glVertex2f(r * cos(angle) + x1, r * sin(angle) + y1);
    }
    glEnd();
}
//drawing line
void Sketch::dLine(GLint drawType, int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    
}
//load functions
bool Sketch::load()
{
    string filename;
    ifstream fin;
    int i;
    cout << "Enter a file to load";
    cin >> filename;
    fin.open(filename.c_str());
    if(fin.is_open())
    {
        fin >> n;
        for(i = 0; i < n; i++)
        {
           fin >> objects[i].colorType >> objects[i].toolType;
            if(objects[i].toolType == 2 || objects[i].toolType == 3)
            {
               fin >> objects[i].tool.circle.center.x >> objects[i].tool.circle.center.y >> objects[i].tool.circle.radius;
            }
            else
            {
                fin >> objects[i].tool.endpoints.pt1.x >> objects[i].tool.endpoints.pt1.y >> objects[i].tool.endpoints.pt2.x >> objects[i].tool.endpoints.pt2.y;
                
            }
            return 1;
        }
        fin.close();
    }
    else
    {
        return 0;
    }
}
//save function using input stream
void Sketch::save()
{
    string filename;
    ofstream fout;
    int i;
    cout << "Enter a file to save";
    cin >> filename;
    fout.open(filename.c_str());
    if(fout.is_open())
    {
        //entering information into the stream
        fout << n << endl;
        for(i = 0; i < n; i++)
        {
            fout << objects[i].colorType << " " <<  objects[i].toolType << " ";
            if(objects[i].toolType == 2 || objects[i].toolType == 3)
            {
                fout << objects[i].tool.circle.center.x << " " << objects[i].tool.circle.center.y << " " << objects[i].tool.circle.radius << endl;
            }
            else
            {
                fout << objects[i].tool.endpoints.pt1.x << " " << objects[i].tool.endpoints.pt1.y << " " << objects[i].tool.endpoints.pt2.x << " " << objects[i].tool.endpoints.pt2.y << endl;
                
            }
        }
        fout.close();
    }
    else
    {
        cout << "not valid";
    }
}
//clear function
void Sketch::clear()
        {
            n = 0;
            
        }

