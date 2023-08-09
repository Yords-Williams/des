#include <cmath>
#include <GL/glut.h>
#define PI 3.141516
#include <iostream>
#include <sstream>
using namespace std;
void line(float x0, float y0, float x1, float y1){
  glBegin(GL_LINES);
    glVertex3f(x0, y0, 0.0);
    glVertex3f(x1, y1, 0.0);
  glEnd();
}
void circle(float cx, float cy, float r){
  int n = 35;
  glBegin(GL_POLYGON);
    for(int i = 0; i<n;i++){
      float rad = i*360.0/n;
      float a = rad*PI/180.0;
      float x = cx+r*cos(a);
      float y = cy+r*sin(a);
      glVertex3f(x, y, 0.0);
    }
  glEnd();
}
void text(float x, float y, const char* string){
  glColor3f(1.0f, 1.0f, 1.0f);
  int i=0;
  while(string[i]!='\0'){
    glRasterPos2f(x+i*0.07, y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i++]);
  }
}


struct Node{
  int dato;
  Node* link;

  Node(int val, Node* n=0){
    dato = val;
    link = n;
  }
};

struct List{
  Node* ini;

  List(){ini=0;}

  void add(int a){
    if(!ini) ini = new Node(a, 0);
    else ini = new Node(a, ini);
  }

  void del(int val){
    Node* t = ini;
    while(t){
      Node* s = t->link;
      if(s && (s->dato == val)){
        t->link = s->link;
      }
      t = t->link;
    }
    if (ini->dato == val)
      ini = ini->link;
  }

  void print(){
    Node* i=ini;
    float x = -0.8;
    float y = 0.0;
    float r = 0.12;
    float cw = 0.07;
    while(i){
      glColor3f(1.0f, 1.0f, 0.0f);
      line(x,y,x+2.8*r,y);
      glColor3f(0.0f, 0.0f, 1.0f);
      circle(x, y, r);
      stringstream ss;
      ss<<i->dato;
      text(x-cw*0.5,y-cw*0.5,ss.str().c_str());
      i=i->link;
      x += 4*r;
    }
  }
};

List L;

void display() {
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  L.print();
  glutSwapBuffers();
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {

  // Use a single buffered window in RGB mode (as opposed to a double-buffered
  // window or color-index mode).
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  // Position window at (80,80)-(480,380) and give it a title.
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(400, 300);
  glutCreateWindow("A Simple Triangle");
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

  L.add(7);
  L.add(17);
  L.add(27);
  L.add(5);
  // Tell GLUT that whenever the main window needs to be repainted that it
  // should call the function display().
  glutDisplayFunc(display);

  // Tell GLUT to start reading and processing events.  This function
  // never returns; the program only exits when the user closes the main
  // window or kills the process.
  glutMainLoop();
}
