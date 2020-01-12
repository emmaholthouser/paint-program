#include <iostream>
using namespace std;

#define NCOLORS     10           // number of colors

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


#define RGBBLACK 0, 0, 0 //black

#define R 0
#define G 1
#define B 2

static float colormenu[][9] = {{RGBRED}, {RGBGREEN}, {RGBBLUE}, {RGBTEAL}, {RGBYELLOW}, {RGBGREY}, {RGBPURPLE}, {RGBORANGE}, {RGBWHITE}, {DARKPURPLE}};


// Point is used for x,y coordinate
struct Point
{
    int x, y;
};

// EndPoint is used for line segments and rectangles
struct EndPoint
{
    Point pt1, pt2;
};

// Circle is used for circles
struct Circle
{
    Point center;
    int radius;
};

// Tool is used for either endpoints or circles
union Tool
{
    EndPoint endpoints;
    Circle circle;
};

// Object contains the information stored for each object
struct Object
{
    short int colorType;   // index of color of the object
    short int toolType;    // index of tool of the object (line segment,rectangle,circle)
    Tool tool;             // tool (line segment,rectangle,circle)
};

class Sketch
{
    Object objects[100];
    int n;
    
   public:
    //declaring sketch functions
    Sketch() {n= 0;}
    void createObject(short int, short int, int, int, int, int);
    void createObject(short int, short int, int, int, int);
    void updateObject(int, int);
    void dRectangle(GLint, int, int, int, int);
    void dCircle(GLint, int, int, int);
    void dLine(GLint, int, int, int, int);
    void draw();
    bool load();
    void clear();
    void save();
    void quit();
  
    
};
