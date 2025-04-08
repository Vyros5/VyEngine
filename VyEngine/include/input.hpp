#pragma once

#include <GLFW/glfw3.h>

/*
    Keyboard class to handle keyboard callbacks
*/

class Keyboard
{
public:
    /*
        Static Callback
    */

    // key state changed
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


    /*
        Static Accessors
    */

    // get key state
    static bool key(int key);

    // get if key recently changed
    static bool keyChanged(int key);

    // get if key recently changed and is up
    static bool keyWentUp(int key);

    // get if key recently changed and is down
    static bool keyWentDown(int key);


private:
    /*
        Static Keyboard Values
    */

    // key state array (true for down, false for up)
    static bool keys[];

    // key changed array (true if changed)
    static bool keysChanged[];
};


/*
    mouse class to handle mouse callbacks
*/

class Mouse {
public:
    /*
        callbacks
    */

    // cursor position changed
    static void cursorPosCallback(GLFWwindow* window, double _x, double _y);

    // mouse button state changed
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    // scroll wheel moved
    static void mouseWheelCallback(GLFWwindow* window, double dx, double dy);

    /*
        accessors
    */

    // get mouse x position
    static double getMouseX();

    // get mouse y position
    static double getMouseY();

    // get mouse change in x
    static double getDX();

    // get mouse change in y
    static double getDY();

    // get scroll value in x
    static double getScrollDX();

    // get scroll value in y
    static double getScrollDY();

    // get button state
    static bool button(int button);

    // return if button changed then reset it in the changed array
    static bool buttonChanged(int button);

    // return if button changed and is now up
    static bool buttonWentUp(int button);

    // return if button changed and is now down
    static bool buttonWentDown(int button);

private:
    /*
        static mouse values
    */

    // x posiiton
    static double x;
    // y position
    static double y;


    // previous x position
    static double lastX;
    // previous y position
    static double lastY;


    // change in x position from lastX
    static double dx;

    // change in y position from lastY
    static double dy;


    // change in scroll x
    static double scrollDx;

    // change in scroll y
    static double scrollDy;


    // if this is the first change in the mouse position
    static bool firstMouse;


    // button state array (true for down, false for up)
    static bool buttons[];

    // button changed array (true if changed)
    static bool buttonsChanged[];

};
