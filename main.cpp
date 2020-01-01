/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <bits/stdc++.h>

#include "RGBPixmap.h"
#define PI 3.14159265

using namespace std;

static int slices = 16;
static int stacks = 16;

float degree=0, degree1=0, degree2=0, scalex=2, scaley=1, scalez=1,YAW=0,ROLL=0,PITCH=0,tx=0,ty=-5.5,tz=-10,eX=0,eY=0,eZ=5, spx=1.0, spy=0.0, spz=15.0, ap=90;
bool pointLight=true, spotLight=true;
int windowW=1360,windowH=720;


const GLfloat matHaliAmb[]= {0.0f,0.0f,0.0f,1.0f};
const GLfloat matHaliDiff[]= {1.0f,0.0f,0.0f,1.0f};
const GLfloat matHaliSpec[]= {1.0f,1.0f,1.0f,1.0f};
const GLfloat matHaliShin[]= {100.0f};


const GLfloat matWallAmb[]= {0.0f,0.0f,0.0f,1.0f};
const GLfloat matWallDiff[]= {0.0f,1.0f,0.0f,1.0f};
const GLfloat matWallSpec[]= {1.0f,1.0f,1.0f,1.0f};
const GLfloat matWallShin[]= {100.0f};

const GLfloat ligAmb[]= {.0f,.0f,.0f,1.0f};
const GLfloat ligDiff[]= {1.0f,1.0f,1.0f,1.0f};
const GLfloat ligSpec[]= {1.0f,1.0f,1.0f,1.0f};
const GLfloat ligPos[]= {0,20,10,10.0f};


const GLfloat lig2Amb[]= {.0f,.0f,.0f,1.0f};
const GLfloat lig2Diff[]= {1.0f,1.0f,1.0f,1.0f};
const GLfloat lig2Spec[]= {1.0f,1.0f,1.0f,1.0f};
const GLfloat lig2Pos[]= {1.0f,0.0f,15.0f,1.0f};
const GLfloat lig2Dir[] = { 0.0f, 0.0f, -7.0f };
const GLfloat lig2Cut[] = {20.0f };
const GLfloat lig2Exp[] = {12.0f };



int pt=0;
//1=translation
//2=scale
//3=yaw,pitch,roll
//4=rotation
//5=zoom
//6=camera eye
//7=circular motion
//8=light

/* GLUT callback Handlers */


void ownScale(double x, double y, double z)
{
    GLfloat m[16];
    for(int i=0;i<16;i++)
    {
        m[i]=0;
    }
    m[0]=x;
    m[5]=y;
    m[10]=z;
    m[15]=1;

    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(m);

}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    windowH = height;
    windowW = width;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
     glViewport(0, 0, windowW, windowH);
}


void halfCircle()
{


    vector<pair<float, float> > points; //points for half circle

    float x, z, r=.5;
    for(int i=0; i<=180; i+=10)
    {
        x=r * cos(-PI*i/180);
        z=r * sin(-PI*i/180);
        points.push_back(make_pair(x,z));
    }


    glBegin(GL_POLYGON);




    for(int i=0; i<points.size(); i++)
    {
        glTexCoord2f(points[i].first, 1);
        glVertex3f(points[i].first,1,points[i].second);
    }

    glEnd();

    glBegin(GL_POLYGON);


    for(int i=points.size()-1; i>=0; i--)
    {
        glTexCoord2f(points[i].first, 0);
        glVertex3f(points[i].first,0,points[i].second);
    }

    glEnd();

    glBegin(GL_QUAD_STRIP);



    for(int i=points.size()-1; i>=0; i--)
    {
        glTexCoord2f(points[i].first, 0);
        glVertex3f(points[i].first,0,points[i].second);
        glTexCoord2f(points[i].first, 1);
        glVertex3f(points[i].first,1,points[i].second);
    }

    glEnd();


    glBegin(GL_POLYGON);

    for(int i=points.size()-1; i>=0; i--)
    {
        glTexCoord2f(-points[i].first, 1);
        glVertex3f(-points[i].first,1,points[i].second);
    }

    glEnd();


    glBegin(GL_POLYGON);


    for(int i=0; i<points.size(); i++)
    {
        glTexCoord2f(-points[i].first, 0);
        glVertex3f(-points[i].first,0,points[i].second);
    }

    glEnd();


    glBegin(GL_QUAD_STRIP);



    for(int i=0; i<points.size(); i++)
    {
        glTexCoord2f(-points[i].first, 0);
        glVertex3f(-points[i].first,0,points[i].second);
        glTexCoord2f(-points[i].first, 1);
        glVertex3f(-points[i].first,1,points[i].second);
    }

    glEnd();


}

void cube()
{
    /*
    glBegin(GL_QUADS);


    glVertex3f(0,0,1);
    glVertex3f(1,0,1);
    glVertex3f(1,1,1);
    glVertex3f(0,1,1);


    glVertex3f(0,0,1);
    glVertex3f(0,1,1);
    glVertex3f(0,1,0);
    glVertex3f(0,0,0);


    glVertex3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glVertex3f(1,1,0);


    glVertex3f(1,0,0);
    glVertex3f(1,1,0);
    glVertex3f(1,1,1);
    glVertex3f(1,0,1);


    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,0,1);
    glVertex3f(0,0,1);



    glVertex3f(0,1,1);
    glVertex3f(1,1,1);
    glVertex3f(1,1,0);
    glVertex3f(0,1,0);
    glEnd();*/
     glBegin(GL_QUADS);
        //glColor3f(r, g, b);
        glTexCoord2f(0.0, 0.0);glVertex3f(0,0,1);
        glTexCoord2f(1.0, 0.0);glVertex3f(1,0,1);
        glTexCoord2f(1.0, 1.0);glVertex3f(1,1,1);
        glTexCoord2f(0.0, 1.0);glVertex3f(0,1,1);


        //glColor3f(r-.2, 1, b);
        glTexCoord2f(0.0, 0.0);glVertex3f(0,0,1);
        glTexCoord2f(1.0, 0.0);glVertex3f(0,1,1);
        glTexCoord2f(1.0, 1.0);glVertex3f(0,1,0);
        glTexCoord2f(0.0, 1.0);glVertex3f(0,0,0);

        //glColor3f(r, g+.2, b);
        glTexCoord2f(0.0, 0.0);glVertex3f(1,0,0);
        glTexCoord2f(1.0, 0.0);glVertex3f(0,0,0);
        glTexCoord2f(1.0, 1.0);glVertex3f(0,1,0);
        glTexCoord2f(0.0, 1.0);glVertex3f(1,1,0);

        //glColor3f(r, g, b+.2);

        glTexCoord2f(0.0, 0.0);glVertex3f(1,0,0);
        glTexCoord2f(1.0, 0.0);glVertex3f(1,1,0);
        glTexCoord2f(1.0, 1.0);glVertex3f(1,1,1);
        glTexCoord2f(0.0, 1.0);glVertex3f(1,0,1);

        //glColor3f(r-.2, g+.2, b);
        glTexCoord2f(0.0, 0.0);glVertex3f(0,0,0);
        glTexCoord2f(1.0, 0.0);glVertex3f(1,0,0);
        glTexCoord2f(1.0, 1.0);glVertex3f(1,0,1);
        glTexCoord2f(0.0, 1.0);glVertex3f(0,0,1);

        //glColor3f(r-.2, g, b+.2);
        glTexCoord2f(0.0, 0.0);glVertex3f(0,1,1);
        glTexCoord2f(1.0, 0.0);glVertex3f(1,1,1);
        glTexCoord2f(1.0, 1.0);glVertex3f(1,1,0);
        glTexCoord2f(0.0, 1.0);glVertex3f(0,1,0);
    glEnd();
}

void cylinder()
{
    float x,z,r=.5;
    vector<pair<float, float> > points; //points for circle
    for(int i=0; i<=360; i+=10)
    {
        x=r * cos(-PI*i/180);
        z=r * sin(-PI*i/180);
        points.push_back(make_pair(x,z));
    }

    glBegin(GL_POLYGON);


    for(int i=points.size()-1; i>=0; i--)
    {
        glTexCoord2f(points[i].first, 0);
        glVertex3f(points[i].first,0,points[i].second);
    }

    glEnd();

    glBegin(GL_POLYGON);


    for(int i=0; i<points.size(); i++)

    {
        glTexCoord2f(points[i].first, 1);
        glVertex3f(points[i].first,1,points[i].second);
    }

    glEnd();

    glBegin(GL_QUAD_STRIP);



    for(int i=points.size()-1; i>=0; i--)
    {
        glTexCoord2f(points[i].first, 0);
        glVertex3f(points[i].first,0,points[i].second);
        glTexCoord2f(points[i].first, 1);
        glVertex3f(points[i].first,1,points[i].second);
    }

    glEnd();
}

void side()
{


    glBegin(GL_POLYGON);

glTexCoord2f(0, 0);
    glVertex3f(0,0,0);
    glTexCoord2f(1, 0);
    glVertex3f(1,0,0);
    glTexCoord2f(1, 1);
    glVertex3f(1,1,0);
    glTexCoord2f(.7, 1);
    glVertex3f(.7,1,0);
    glTexCoord2f(0, .2);
    glVertex3f(0,.2,0);
glTexCoord2f(0, 0);
    glVertex3f(0,0,0);
    glTexCoord2f(0, .2);
    glVertex3f(0,.2,0);
    glTexCoord2f(0.7, 1);
    glVertex3f(.7,1,0);
    glTexCoord2f(1, 1);
    glVertex3f(1,1,0);
    glTexCoord2f(1, 0);
    glVertex3f(1,0,0);


    glEnd();

    glBegin(GL_POLYGON);

glTexCoord2f(0, 0);
    glVertex3f(0,0,1);
    glTexCoord2f(1, 0);
    glVertex3f(1,0,1);
    glTexCoord2f(1, 1);
    glVertex3f(1,1,1);
    glTexCoord2f(.7, 1);
    glVertex3f(.7,1,1);
    glTexCoord2f(0, .2);
    glVertex3f(0,.2,1);

    glEnd();

    glBegin(GL_QUAD_STRIP);

glTexCoord2f(0, 0);
    glVertex3f(0,0,1);
    glTexCoord2f(0, 0);
    glVertex3f(0,0,0);
    glTexCoord2f(1, 0);
    glVertex3f(1,0,1);
    glTexCoord2f(1, 0);
    glVertex3f(1,0,0);
glTexCoord2f(1, 1);
    glVertex3f(1,1,1);
    glTexCoord2f(1, 1);
    glVertex3f(1,1,0);
    glTexCoord2f(.7, 1);
    glVertex3f(.7,1,1);
    glTexCoord2f(.7, 1);
    glVertex3f(.7,1,0);
    glTexCoord2f(0, .2);
    glVertex3f(0,.2,1);
        glTexCoord2f(0, .2);
    glVertex3f(0,.2,0);
        glTexCoord2f(0, 0);
    glVertex3f(0,0,1);
    glTexCoord2f(0, 0);
    glVertex3f(0,0,0);
    glEnd();
}

void traingle()
{

    glBegin(GL_TRIANGLES);

    glVertex3f(0,0,0);
    glVertex3f(1,1,0);
    glVertex3f(1,0,0);



    glVertex3f(0,0,1);
    glVertex3f(1,0,1);
    glVertex3f(1,1,1);

    glEnd();


    glBegin(GL_QUAD_STRIP);


    glVertex3f(1,0,0);
    glVertex3f(1,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1);
    glVertex3f(1,1,0);
    glVertex3f(1,1,1);
    glVertex3f(1,0,0);
    glVertex3f(1,0,1);


    glEnd();

}


void setMaterial(float r, float g, float b)
{
    GLfloat cus[]= {r,g,b,1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT,   matWallAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   cus);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  matWallSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matWallShin);

}

void setLight(float r, float g, float b)
{
    GLfloat cus[]= {r,g,b,1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ligAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,cus);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cus);
    glLightfv(GL_LIGHT0, GL_POSITION, ligPos);



    glLightfv(GL_LIGHT1,GL_SPOT_CUTOFF, lig2Cut);
    glLightfv(GL_LIGHT1, GL_POSITION, lig2Pos);

    glLightfv(GL_LIGHT1, GL_DIFFUSE,cus);
    glLightfv(GL_LIGHT1, GL_SPECULAR, cus);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lig2Dir);
    glLightfv(GL_LIGHT1,GL_SPOT_EXPONENT, lig2Exp);


}

int Depth=3;

void drawkoch(GLfloat x,GLfloat y, GLfloat len, GLint iter) {

	if (iter == -1) {
        return;
	}
	else {

		iter--;

		drawkoch(x,y, len/3.0, iter);
		drawkoch(x+len/3.0,y, len/3.0, iter);
		drawkoch(x+2.0*len/3.0,y, len/3.0, iter);

		drawkoch(x,y+len/3.0, len/3.0, iter);
	//	drawkoch(x+len/3.0,y/3.0, len/3.0, iter); //here, already drawn the large one
		drawkoch(x+2.0*len/3.0,y+len/3.0, len/3.0, iter);

        drawkoch(x,y+2.0*len/3.0, len/3.0, iter);
		drawkoch(x+len/3.0,y+2.0*len/3.0, len/3.0, iter);
		drawkoch(x+2.0*len/3.0,y+2.0*len/3.0, len/3.0, iter);

		glBegin(GL_QUADS);
            glVertex2f(x+len/3.0, y+2.0*len/3.0);
            glVertex2f(x+len/3.0, y+len/3.0);
            glVertex2f(x+2.0*len/3.0, y+len/3.0);
            glVertex2f(x+2.0*len/3.0, y+2.0*len/3.0);
		glEnd();


	}
}

void KochCurve(int depth) {
	glClear(GL_COLOR_BUFFER_BIT);

	drawkoch(0,0,12, depth);

	glFlush();
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 100.0;

    const double a = t*90.0;

    if(pt==7)
    {
        float r=5;
        eX=-15*sin(t*10*PI/180);
        eZ=15*cos(t*10*PI/180);
        cout<<eX<<" "<<eZ<<endl;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glLightfv(GL_LIGHT0, GL_AMBIENT, ligAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ligDiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, ligSpec);
    glLightfv(GL_LIGHT0, GL_POSITION, ligPos);


     //GLfloat tp[]={spx,spy,spz,1.0f};

    glLightfv(GL_LIGHT1,GL_SPOT_CUTOFF, lig2Cut);
    glLightfv(GL_LIGHT1, GL_POSITION, lig2Pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lig2Diff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lig2Spec);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lig2Dir);
    glLightfv(GL_LIGHT1,GL_SPOT_EXPONENT, lig2Exp);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity() ;
    gluPerspective(ap,(float)windowW/(float)windowH,1,50);



    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eX, eY, eZ,10*sin(YAW/180*PI), 10*sin(PITCH / 180 * PI), -1,sin(ROLL/180*PI), 1, 0);
    /*
        gluLookAt(
      ///This one handles the actual viewer position:
      0, 0, -2,
      ///This one handles viewer direction - Yaw and Pitch
      0 + sin(YAW / 180 * PI), 0 + sin(PITCH / 180 * PI), 0 + sin(YAW / 180 * PI) + cos(PITCH / 180 * PI),
      ///This one handles viewer orientation - Pitch and Roll
      ///The algorithm must eliminate pitch alteration,
      ///as this element appears both in centerXYZ and upXYZ
      0, 0 + cos(PITCH / 180 * PI), 0 + sin(PITCH / 180 * PI));
    */


   // glBindTexture(GL_TEXTURE_2D, 2);

glViewport(0,0,windowW/2,windowH);

    glPushMatrix();





        glTranslated(tx,0,0);
        glTranslated(0,ty,0);
        glTranslated(0,0,tz);
        ownScale(scalex,1,1);
        ownScale(1,scaley,1);
        ownScale(1,1,scalez);
        glRotated(degree,1,0,0);
        glRotated(degree1,0,1,0);
        glRotated(degree2,0,0,1);





        glPushMatrix();
            glTranslated(-4.99,0.5,7);
            glRotated(90,0,1,0);
            KochCurve(Depth);
        glPopMatrix();



        //wall1
            glMaterialfv(GL_FRONT, GL_AMBIENT,   matWallAmb);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,   matWallDiff);
            glMaterialfv(GL_FRONT, GL_SPECULAR,  matWallSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matWallShin);
        glPushMatrix();


            glTranslated(-5.4,0,-5.4);
            ownScale(12.4,12.4,.4);
            cube();

        glPopMatrix();



        glPushMatrix();


            glTranslated(-5.4,0,7);
            glRotated(90,0,1,0);
            ownScale(12,12.4,.4);
            cube();

        glPopMatrix();

        setMaterial(0,1,.9);
        glPushMatrix();


            glTranslated(-5,0,7);
            glRotated(90,0,1,0);
            ownScale(12,.4,12);
            cube();

        glPopMatrix();







        //table
        setMaterial(0,1,1);

        glPushMatrix();

            glTranslated(-3,2,-2);
            ownScale(8,.2,5);
            cube();

        glPopMatrix();
        //table legs
        glPushMatrix();
            setMaterial(1,.1,.1);
            ownScale(.3,2,.3);
            glTranslated(-7,0,-4);
            cube();
        glPopMatrix();

        glPushMatrix();
            setMaterial(1,.1,.1);
            ownScale(.3,2,.3);
            glTranslated(-7,0,6);
            cube();
        glPopMatrix();

        glPushMatrix();
            setMaterial(1,.1,.1);
            ownScale(.3,2,.3);
            glTranslated(12,0,6);
            cube();
        glPopMatrix();


        glPushMatrix();
            setMaterial(1,.1,.1);
            ownScale(.3,2,.3);
            glTranslated(12,0,-4);
            cube();
        glPopMatrix();

    //jack

        glPushMatrix();
            glTranslated(3,2.8,0);
            ownScale(.5,.5,.5);
            glPushMatrix();
                glTranslated(-1,-1,-1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();

            glPushMatrix();
                glTranslated(1,-1,-1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();


            glPushMatrix();
                glTranslated(0,-1,1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();

            //upper side of jack
            glPushMatrix();
                glTranslated(0,1,-1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();

            glPushMatrix();
                glTranslated(-1,1,1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();


            glPushMatrix();
                glTranslated(1,1,1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();
    //jack connectors

            glPushMatrix();
                glRotated(-45,1,0,0);
                glRotated(55,0,1,0);
                ownScale(1.9,.2,.2);
                glutSolidSphere(1,16,16);
            glPopMatrix();



            glPushMatrix();
                glRotated(-45,1,0,0);
                glRotated(55,0,1,0);
                ownScale(.2,1.9,.2);
                glutSolidSphere(1,16,16);
            glPopMatrix();

            glPushMatrix();
                glRotated(-45,1,0,0);
                glRotated(35,0,1,0);
                ownScale(.2,.2,1.9);
                glutSolidSphere(1,16,16);
            glPopMatrix();
        glPopMatrix();


        //helicopter

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT,   matHaliAmb);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,   matHaliDiff);
            glMaterialfv(GL_FRONT, GL_SPECULAR,  matHaliSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matHaliShin);

            glTranslated(-1,2.4,0);
            ownScale(.2,.2,.2);
            //wing1
            glPushMatrix();
                glRotated(a,0,1,0);
                glPushMatrix();
                    glPushMatrix();
                    glTranslated(0,4.5,-4);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(0,4.5,4);
                    glRotated(180,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(-.5,4.5,-4);
                    glScalef(1,.2,8);
                    cube();
                glPopMatrix();

                //wing2
                glPushMatrix();
                    glTranslated(-4,4.7,0);
                    glRotated(90,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(4,4.7,0);
                    glRotated(-90,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(-4,4.7,-.5);
                    glScalef(8,.2,1);
                    cube();
                glPopMatrix();

                //wing connector
                glPushMatrix();
                    glTranslated(0,3,0);
                    glScalef(.3,1.5,.3);
                    cylinder();
                glPopMatrix();
            glPopMatrix();
            //body
            glPushMatrix();
                glTranslated(-7,0,2);
                glScalef(8,3,.2);
                side();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-7,0,-2);
                glScalef(8,3,.2);
                side();
            glPopMatrix();


            glPushMatrix();
                glTranslated(1,0,-2);
                glScalef(.2,3,4.2);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-7,-.2,-2);
                glScalef(8.2,.2,4.2);
                cube();
            glPopMatrix();


            glPushMatrix();
                glTranslated(-7.2,-.2,-2);
                glScalef(.2,.8,4.2);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-1.4,3,-2);
                glScalef(2.6,.2,4.2);
                cube();
            glPopMatrix();


            glPushMatrix();
                glTranslated(-7,.6,-2);
                glRotated(23,0,0,1);
                glScalef(2.5,.2,4.2);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-3,2.3,-2);
                glRotated(22.5,0,0,1);
                glScalef(1.9,.2,4.2);
                cube();
            glPopMatrix();

            //leg one
            glPushMatrix();
                glTranslated(-3.5,-1,1.6);
                glScalef(2.5,1,.2);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-4.2,-1,.8);
                glScalef(4,.2,1.4);
                cube();
            glPopMatrix();


            //leg two
            glPushMatrix();
                glTranslated(-3.5,-1,-1.6);
                glScalef(2.5,1,.2);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-4.2,-1,-2);
                glScalef(4,.2,1.4);
                cube();
            glPopMatrix();

            //tail container

            glPushMatrix();
                glTranslated(1,.7,-.5);
                glScalef(6,1,1);
                cube();
            glPopMatrix();


            //tail
            glPushMatrix();
                glTranslated(7,.7,-.5);
                glRotated(45,0,0,1);
                glScalef(2,1,1);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(8,2.4,-.5);
                glRotated(-45,0,0,1);
                glRotated(90,1,0,0);
                glScalef(1,1,1);
                halfCircle();
            glPopMatrix();

            glPushMatrix();
                glTranslated(1.2,0,0.4);
                glRotated(180,1,1,0);
                glScalef(1,2,.8);
                traingle();
            glPopMatrix();


            glPushMatrix();
            //glRotated(90,1,0,0);
            //  glTranslated(6.5,-2,0);
            //  glRotated(90,1,0,0);
                glTranslated(8,2.4,-3.85);
                glRotated(a,0,0,1);
                glRotated(90,1,0,0);
                glScalef(.2,1,.2);
                //  glRotated(a,0,1,0);

                glPushMatrix();
                    glTranslated(0,4.5,-4);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();

                glTranslated(0,4.5,4);
                    glRotated(180,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(-.5,4.5,-4);
                    glScalef(1,.2,8);
                    cube();
                glPopMatrix();

                //wing2
                glPushMatrix();
                    glTranslated(-4,4.7,0);
                    glRotated(90,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();

                glTranslated(4,4.7,0);
                    glRotated(-90,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(-4,4.7,-.5);
                    glScalef(8,.2,1);
                    cube();
                glPopMatrix();

                //wing connector
                glPushMatrix();
                    glTranslated(0,4.3,0);
                    glScalef(.5,.2,.5);
                    cylinder();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();






































 glViewport(windowW/2,0,windowW/2,windowH);
    glPushMatrix();





        glTranslated(tx,0,0);
        glTranslated(0,ty,0);
        glTranslated(0,0,tz);
        ownScale(scalex,1,1);
        ownScale(1,scaley,1);
        ownScale(1,1,scalez);
        glRotated(degree,1,0,0);
        glRotated(degree1,0,1,0);
        glRotated(degree2,0,0,1);





        //wall1

        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 1);

            glTranslated(-5.4,0,-5.4);
            ownScale(12.4,12.4,.4);
            cube();
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();



        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 1);
            glMaterialfv(GL_FRONT, GL_AMBIENT,   matWallAmb);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,   matWallDiff);
            glMaterialfv(GL_FRONT, GL_SPECULAR,  matWallSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matWallShin);
            glTranslated(-5.4,0,7);
            glRotated(90,0,1,0);
            ownScale(12,12.4,.4);
            cube();
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        setMaterial(1,1,1);
        glPushMatrix();

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 2);
            glTranslated(-5,0,7);
            glRotated(90,0,1,0);
            ownScale(12,.4,12);
            cube();
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        //koch



        //window
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 3);
            glTranslated(-1.4,3,-5);
            ownScale(5,5,.1);
            cube();
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();


        //table
        setMaterial(0,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 4);
        glPushMatrix();

            glTranslated(-3,2,-2);
            ownScale(8,.2,5);
            cube();

        glPopMatrix();
        //table legs
        glPushMatrix();
            setMaterial(1,.1,.1);
            ownScale(.3,2,.3);
            glTranslated(-7,0,-4);
            cube();
        glPopMatrix();

        glPushMatrix();
            setMaterial(1,.1,.1);
            ownScale(.3,2,.3);
            glTranslated(-7,0,6);
            cube();
        glPopMatrix();

        glPushMatrix();
            setMaterial(1,.1,.1);
            ownScale(.3,2,.3);
            glTranslated(12,0,6);
            cube();
        glPopMatrix();


        glPushMatrix();
            setMaterial(1,.1,.1);
            ownScale(.3,2,.3);
            glTranslated(12,0,-4);
            cube();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    //jack
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 6);
        glPushMatrix();
            glTranslated(3,2.8,0);
            ownScale(.5,.5,.5);
            glPushMatrix();
                glTranslated(-1,-1,-1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();

            glPushMatrix();
                glTranslated(1,-1,-1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();


            glPushMatrix();
                glTranslated(0,-1,1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();

            //upper side of jack
            glPushMatrix();
                glTranslated(0,1,-1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();

            glPushMatrix();
                glTranslated(-1,1,1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();


            glPushMatrix();
                glTranslated(1,1,1);
                glutSolidSphere(.2,16,16);
            glPopMatrix();
    //jack connectors

            glPushMatrix();
                glRotated(-45,1,0,0);
                glRotated(55,0,1,0);
                ownScale(1.9,.2,.2);
                glutSolidSphere(1,16,16);
            glPopMatrix();



            glPushMatrix();
                glRotated(-45,1,0,0);
                glRotated(55,0,1,0);
                ownScale(.2,1.9,.2);
                glutSolidSphere(1,16,16);
            glPopMatrix();

            glPushMatrix();
                glRotated(-45,1,0,0);
                glRotated(35,0,1,0);
                ownScale(.2,.2,1.9);
                glutSolidSphere(1,16,16);
            glPopMatrix();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        //helicopter
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 5);
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT,   matHaliAmb);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,   matHaliDiff);
            glMaterialfv(GL_FRONT, GL_SPECULAR,  matHaliSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matHaliShin);

            glTranslated(-1,2.4,0);
            ownScale(.2,.2,.2);
            //wing1
            glPushMatrix();
                glRotated(a,0,1,0);
                glPushMatrix();
                    glPushMatrix();
                    glTranslated(0,4.5,-4);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(0,4.5,4);
                    glRotated(180,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(-.5,4.5,-4);
                    glScalef(1,.2,8);
                    cube();
                glPopMatrix();

                //wing2
                glPushMatrix();
                    glTranslated(-4,4.7,0);
                    glRotated(90,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(4,4.7,0);
                    glRotated(-90,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(-4,4.7,-.5);
                    glScalef(8,.2,1);
                    cube();
                glPopMatrix();

                //wing connector
                glPushMatrix();
                    glTranslated(0,3,0);
                    glScalef(.3,1.5,.3);
                    cylinder();
                glPopMatrix();
            glPopMatrix();
            //body
            glPushMatrix();
                glTranslated(-7,0,2);
                glScalef(8,3,.2);
                side();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-7,0,-2);
                glScalef(8,3,.2);
                side();
            glPopMatrix();


            glPushMatrix();
                glTranslated(1,0,-2);
                glScalef(.2,3,4.2);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-7,-.2,-2);
                glScalef(8.2,.2,4.2);
                cube();
            glPopMatrix();


            glPushMatrix();
                glTranslated(-7.2,-.2,-2);
                glScalef(.2,.8,4.2);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-1.4,3,-2);
                glScalef(2.6,.2,4.2);
                cube();
            glPopMatrix();


            glPushMatrix();
                glTranslated(-7,.6,-2);
                glRotated(23,0,0,1);
                glScalef(2.5,.2,4.2);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-3,2.3,-2);
                glRotated(22.5,0,0,1);
                glScalef(1.9,.2,4.2);
                cube();
            glPopMatrix();

            //leg one
            glPushMatrix();
                glTranslated(-3.5,-1,1.6);
                glScalef(2.5,1,.2);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-4.2,-1,.8);
                glScalef(4,.2,1.4);
                cube();
            glPopMatrix();


            //leg two
            glPushMatrix();
                glTranslated(-3.5,-1,-1.6);
                glScalef(2.5,1,.2);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(-4.2,-1,-2);
                glScalef(4,.2,1.4);
                cube();
            glPopMatrix();

            //tail container

            glPushMatrix();
                glTranslated(1,.7,-.5);
                glScalef(6,1,1);
                cube();
            glPopMatrix();


            //tail
            glPushMatrix();
                glTranslated(7,.7,-.5);
                glRotated(45,0,0,1);
                glScalef(2,1,1);
                cube();
            glPopMatrix();

            glPushMatrix();
                glTranslated(8,2.4,-.5);
                glRotated(-45,0,0,1);
                glRotated(90,1,0,0);
                glScalef(1,1,1);
                halfCircle();
            glPopMatrix();

            glPushMatrix();
                glTranslated(1.2,0,0.4);
                glRotated(180,1,1,0);
                glScalef(1,2,.8);
                traingle();
            glPopMatrix();


            glPushMatrix();
            //glRotated(90,1,0,0);
            //  glTranslated(6.5,-2,0);
            //  glRotated(90,1,0,0);
                glTranslated(8,2.4,-3.85);
                glRotated(a,0,0,1);
                glRotated(90,1,0,0);
                glScalef(.2,1,.2);
                //  glRotated(a,0,1,0);

                glPushMatrix();
                    glTranslated(0,4.5,-4);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();

                glTranslated(0,4.5,4);
                    glRotated(180,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(-.5,4.5,-4);
                    glScalef(1,.2,8);
                    cube();
                glPopMatrix();

                //wing2
                glPushMatrix();
                    glTranslated(-4,4.7,0);
                    glRotated(90,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();

                glTranslated(4,4.7,0);
                    glRotated(-90,0,1,0);
                    glScalef(1,.2,1);
                    halfCircle();
                glPopMatrix();

                glPushMatrix();
                    glTranslated(-4,4.7,-.5);
                    glScalef(8,.2,1);
                    cube();
                glPopMatrix();

                //wing connector
                glPushMatrix();
                    glTranslated(0,4.3,0);
                    glScalef(.5,.2,.5);
                    cylinder();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

//      glPushMatrix();
//
//        mat_diffuse[0]=0.5;
//        mat_diffuse[1]=0.2;
//        mat_diffuse[2]=0.0;
//
//        mat_specular[0]=0;
//        mat_specular[1]=0;
//        mat_specular[2]=0;
//
////        material();
//
//
//        glTranslated(-12,4,-10);
//
//        cube();
//
//    glPopMatrix();
//
////Second wall
//
//    glPushMatrix();
//
//        mat_diffuse[0]=0.2;
//        mat_diffuse[1]=0.7;
//        mat_diffuse[2]=0.0;
//
//        mat_specular[0]=0;
//        mat_specular[1]=0;
//        mat_specular[2]=0;
//
//      //  material();
//
//        glTranslated(-3.1,4,-55);
//       // ownScale(9.2, 25, 1);
//        cube();
//
//    glPopMatrix();





    //First wall




    glutSwapBuffers();
}





void consoleUpdate()
{

    if (pt==1)
    {
        cout<<"Translated: x: "<<tx<<", y: "<<ty<<", z: "<<tz<<endl;
    }
    else if(pt==2)
    {
        cout<<"Scaled: x: "<<scalex<<", y: "<<scaley<<", z: "<<scalez<<endl;
    }
    else if(pt==3)
    {
        cout<<"CameraCenter: Roll: "<<ROLL<<", YAW: "<<YAW<<", PITCH: "<<PITCH<<endl;
    }
    else if(pt==4)
    {
        cout<<"Rotated: x: "<<degree<<", y: "<<degree1<<", z: "<<degree2<<endl;
    }
    else if(pt==5)
    {
        cout<<"Zoom: "<<scalex<<"x"<<endl;
    }
    else if(pt==6)
    {
        cout<<"CameraEye: x: "<<eX<<", y: "<<eY<<", z: "<<eZ<<endl;
    }
    else if(pt==8)
    {
        cout<<"Light, Point Light: ";
        if(pointLight){
            cout<<"On ";
        }else{
            cout<<"Off ";
        }
        cout<<", Spot Light: ";
        if(spotLight){
            cout<<"On";
        }else{
            cout<<"Off";
        }
        cout<<endl;
    }
        else if(pt==9)
    {
        cout<<"Point Light Color (n=red, m=green, k=blue, l=white): "<<endl;
    }
    else if(pt==10)
    {
        cout<<"Depth: "<<Depth<<endl;
    }
    else if(pt==11)
    {
        cout<<"Spot position X: "<<spx<<" Y: "<<spy<<" Z: "<<spz<<endl;
    }
    else if(pt==12)
    {
        cout<<"Zoom, aperture: "<<ap<<endl;
    }

}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :

    case 'q':
        pt=1;
        cout<<"Mode: Translation"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 'w':
        pt=2;
        cout<<"Mode: Scaling"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 'e':
        pt=3;
        cout<<"Mode: CameraCenter"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 'r':
        pt=4;
        cout<<"Mode: Rotation"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 't':
        pt=5;
        cout<<"Mode: Zoom"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 'y':
        pt=6;
        cout<<"Mode: CameraEye"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 'a':
        cout<<"Mode: Camera Circular Motion"<<endl;
        cout<<"Now ";
        pt=7;
        consoleUpdate();
        break;
    case 's':
        pt=8;
        cout<<"Mode: Light On/Off"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 'd':
        pt=9;
        cout<<"Mode: Light Color"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 'f':
        pt=10;
        cout<<"Mode: Koch Depth"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 'z':
        pt=11;
        cout<<"Mode: SpotLight Pos"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 'x':
        pt=12;
        cout<<"Mode: Zoom using aperture"<<endl;
        cout<<"Now ";
        consoleUpdate();
        break;
    case 'n':
        if (pt==1)
            tx+=.5;
        else if(pt==2)
            scalex+=.2;
        else if(pt==3)
            PITCH+=5;
        else if(pt==4)
            degree+=5.0;
        else if(pt==5)
        {
            scalex+=.2;
            scaley+=.2;
            scalez+=.2;
        }
        else if(pt==6)
        {
            eX+=.2;
        }
        else if(pt==8)
        {
            glEnable(GL_LIGHT0);
            pointLight=true;
        }
        else if(pt==9)
        {
            setLight(1,0,0);
        }
        else if(pt==10)
        {
            if(Depth!=6)
                Depth++;
        }
        else if(pt==11)
        {
            spx+=.5;
        }
        else if(pt==12)
        {
            ap+=2;
        }
        consoleUpdate();
        break;
    case 'm':
        if (pt==1)
            tx-=.5;
        else if(pt==2)
            scalex-=.2;
        else if(pt==3)
            PITCH-=5;
        else if(pt==4)
            degree-=5.0;
        else if(pt==5)
        {
            scalex-=.2;
            scaley-=.2;
            scalez-=.2;
        }
        else if(pt==6)
        {
            eX-=.2;
        }
        else if(pt==8)
        {
            glDisable(GL_LIGHT0);
            pointLight=false;
        }
        else if(pt==9)
        {
            setLight(0,1,0);
        }
        else if(pt==10)
        {
            if(Depth!=0)
                Depth--;
        }
        else if(pt==11)
        {
            spx-=.5;
        }
        else if(pt==12)
        {
            ap-=2;
        }
        consoleUpdate();
        break;
    case 'k':
        if (pt==1)
            ty+=.5;
        else if(pt==2)
            scaley+=.2;
        else if(pt==3)
            YAW+=5;
        else if(pt==4)
            degree1+=5.0;
        else if(pt==5)
        {
            scalex+=.2;
            scaley+=.2;
            scalez+=.2;
        }
        else if(pt==6)
        {
            eY+=.2;
        }
        else if(pt==8)
        {
            glEnable(GL_LIGHT1);
            spotLight=true;
        }
        else if(pt==9)
        {
            setLight(0,0,1);
        }
        else if(pt==11)
        {
            spy+=.5;
        }
        consoleUpdate();
        break;
    case 'l':
        if (pt==1)
            ty-=.5;
        else if(pt==2)
            scaley-=.2;
        else if(pt==3)
            YAW-=5;
        else if(pt==4)
            degree1-=5.0;
        else if(pt==5)
        {
            scalex-=.2;
            scaley-=.2;
            scalez-=.2;
        }
        else if(pt==6)
        {
            eY-=.2;
        }
        else if(pt==8)
        {
            glDisable(GL_LIGHT1);
            spotLight=false;

        }
        else if(pt==9)
        {
            setLight(1,1,1);
        }
        else if(pt==11)
        {
            spy-=.5;
        }
        consoleUpdate();
        break;
    case 'o':
        if (pt==1)
            tz+=.5;
        else if(pt==2)
            scalez+=.2;
        else if(pt==3)
            ROLL+=2;
        else if(pt==4)
            degree2+=5.0;
        else if(pt==5)
        {
            scalex+=.2;
            scaley+=.2;
            scalez+=.2;
        }
        else if(pt==6)
        {
            eZ+=.2;
        }
        else if(pt==11)
        {
            spz+=.5;
        }
        consoleUpdate();
        break;
    case 'p':
        if (pt==1)
            tz-=.5;
        else if(pt==2)
            scalez-=.2;
        else if(pt==3)
            ROLL-=2;
        else if(pt==4)
            degree2-=5.0;
        else if(pt==5)
        {
            scalex-=.2;
            scaley-=.2;
            scalez-=.2;
        }
        else if(pt==6)
        {
            eZ-=.2;
        }
        else if(pt==11)
        {
            spz-=.5;
        }
        consoleUpdate();
        break;
    case '`':
        if (pt==1)
        {
            //tx=0,ty=-5.5,tz=-10
            tx=0;
            ty=-5.5;
            tz=-10;
            cout<<"Reset to: ";
        }
        else if(pt==2)
        {
            scalex=1;
            scaley=1;
            scalez=1;
            cout<<"Reset to: ";
        }
        else if(pt==3)
        {
            YAW=0;
            ROLL=0;
            PITCH=0;
            cout<<"Reset to: ";
        }
        else if(pt==4)
        {
            degree=0;
            degree1=0;
            degree2=0;
            cout<<"Reset to: ";
        }
        else if(pt==5)
        {
            scalex=1;
            scaley=1;
            scalez=1;
            cout<<"Reset to: ";
        }
        else if(pt==6)
        {
            eX=0;
            eY=0;
            eZ=15;
            cout<<"Reset to: ";
        }
        else if(pt==8)
        {
            glEnable(GL_LIGHT0);
            pointLight=true;
            glEnable(GL_LIGHT1);
            spotLight=true;
            cout<<"Reset to: ";
        }
        else if(pt==12)
        {
            ap=90;
            cout<<"Reset to: ";
        }
        consoleUpdate();
    }


    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

void init()
{

    //glEnable(GL_TEXTURE_2D);

    set_texture(1,"G:\\Projects\\Codeblocks\\HL3\\walltex2.bmp");
    set_texture(2,"G:\\Projects\\Codeblocks\\HL3\\floortex1.bmp");
    set_texture(3,"G:\\Projects\\Codeblocks\\HL3\\windowtex1.bmp");
    set_texture(4,"G:\\Projects\\Codeblocks\\HL3\\tabletex1.bmp");
    set_texture(5,"G:\\Projects\\Codeblocks\\HL3\\coptertex2.bmp");
    set_texture(6,"G:\\Projects\\Codeblocks\\HL3\\jacktex1.bmp");


}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1024,720);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("1507096");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    init();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
 //   glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);





    cout<<"Keyboard Operations:\nModes:\n  q = Translation\n  w = Scaling\n  e = CameraCenter\n  r = Rotation\n  t = Zoom\n  y = CameraEye\n  s = Light\n  f = Koch Depth\n  x = Zoom (using aperture)\nOperations:\n  n, m = X axis or PointLight\n  k, l = Y axis or SpotLight\n  o, p = Z axis\n  ` = Reset\n";
    glutMainLoop();

    return EXIT_SUCCESS;
}
