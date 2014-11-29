//
//  main.cpp
//  Assignment0Gems
//
//  Created by Emma Meersman on 9/16/14.
//  Copyright (c) 2014 Emma Meersman. All rights reserved.
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <list>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

bool grid[4][4];

void fillRandomGrid() {
    for (int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            bool currColor = rand() % 2;
            grid[i][j] = currColor;
        }
    }
}

void fillRedGrid() {
    for (int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            bool currColor = rand() % 1;
            grid[i][j] = currColor;
        }
    }
}

void drawSquare(double x, double y, bool color) {
    if(color == 0) {
        glColor3d(1, 0, 0);
    } else {
        glColor3d(0, 1, 0);
    }
    glBegin(GL_POLYGON);
    glVertex2d(x, y);
    glVertex2d(x, y+0.5);
    glVertex2d(x+0.5, y+0.5);
    glColor3d(0, 0, 0);
    glVertex2d(x+0.5, y);
    glEnd();
}

// Assigns shapes to the cells and displays them on the grid
void drawGrid() {
    double x = -1.0;
    double y;
    for(int i = 0; i < 4; ++i) {
        y = -1.0;
        for(int j = 0; j < 4; ++j) {
            drawSquare(x,y,grid[i][j]);
            y += 0.5;
        }
        x += 0.5;
    }
}

bool change(bool color){
    if(color){
        color = 0;
    } else {
        color = 1;
    }
    return color;
}

// Perform BFS to find all adjacent shapes to clicked shape in the grid
void switchCells(int x, int y) {
    grid[x][y] = change(grid[x][y]);
    if(x == 0) {
        grid[3][y] = change(grid[3][y]);
        grid[x+1][y] = change(grid[x+1][y]);
    } else if(x == 3) {
        grid[0][y] = change(grid[0][y]);
        grid[x-1][y] = change(grid[x-1][y]);
    } else {
        grid[x-1][y] = change(grid[x-1][y]);
        grid[x+1][y] = change(grid[x+1][y]);
    }
    if(y == 0) {
        grid[x][3] = change(grid[x][3]);
        grid[x][y+1] = change(grid[x][y+1]);
    } else if(y == 3) {
        grid[x][0] = change(grid[x][0]);
        grid[x][y-1] = change(grid[x][y-1]);
    } else {
        grid[x][y-1] = change(grid[x][y-1]);
        grid[x][y+1] = change(grid[x][y+1]);
    }
    glutPostRedisplay();
}

//--------------------------------------------------------
// Display callback that is responsible for updating the screen
//--------------------------------------------------------
void onDisplay( ) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);        	// clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen
    
    drawGrid();
    
	glutSwapBuffers();                     		// Swap buffers for double buffering
	
}

void onReshape(int winWidth0, int winHeight0) {
    glViewport(0, 0, winWidth0, winHeight0);
}

void onKeyboard(unsigned char key, int x, int y) {
    if(key == 'r') {
        fillRandomGrid();
    } else if(key == 'c') {
        fillRedGrid();
    }
    glutPostRedisplay();
}

void onClick(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Send the x and y to be handled
        int xi = 4*x/glutGet(GLUT_WINDOW_WIDTH);
        int yi = 4-4*y/glutGet(GLUT_WINDOW_HEIGHT);
        std::cout << xi << " " << yi << std::endl;
        switchCells(xi, yi-1);
    }
}

//--------------------------------------------------------
// The entry point of the application
//--------------------------------------------------------
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);                 		// GLUT initialization
    glutInitWindowSize(640, 480);				// Initial resolution of the MsWindows Window is 600x600 pixels
    glutInitWindowPosition(100, 100);            // Initial location of the MsWindows window
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);    // Image = 8 bit R,G,B + double buffer + depth buffer
    
    glutCreateWindow("Gems");        	// Window is born
    fillRandomGrid();
    glutDisplayFunc(onDisplay);                	// Register event handlers
    glutReshapeFunc(onReshape);                 // Handle window resizing
    glutMouseFunc(onClick);                     // Detect clicks on grid
    glutKeyboardFunc(onKeyboard);
    
    glutMainLoop();                    			// Event loop
    return 0;
}

