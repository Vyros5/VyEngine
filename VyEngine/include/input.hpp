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
    static float getMouseX();

    // get mouse y position
    static float getMouseY();

    // get mouse change in x
    static float getDX();

    // get mouse change in y
    static float getDY();

    // get scroll value in x
    static float getScrollDX();

    // get scroll value in y
    static float getScrollDY();

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
    static float x;
    // y position
    static float y;


    // previous x position
    static float lastX;
    // previous y position
    static float lastY;


    // change in x position from lastX
    static float dx;

    // change in y position from lastY
    static float dy;


    // change in scroll x
    static float scrollDx;

    // change in scroll y
    static float scrollDy;


    // if this is the first change in the mouse position
    static bool firstMouse;


    // button state array (true for down, false for up)
    static bool buttons[];

    // button changed array (true if changed)
    static bool buttonsChanged[];

};
