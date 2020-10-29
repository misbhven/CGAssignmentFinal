//
// Created by cg on 29/10/20.
//

#include "cameraControls.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
//mouse intergration
//TODO - broken constants
float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
int BUTTON_DELAY = 0;
int SHOW_DELAY = 0;

//Toggle Lighting of Scene
//TODO
//The scene is defaulted to a darkish lighting
bool  SCENE_DEFAULT_BRIGHTNESS = true;

//Scale Brightness of Torch
//TODO
//The Brightness of the torch may be given a variety of brightness levels
float torchBrightnessLevels[] = {0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f};
int torchSetting = 3;

//Toggle projection mode
//The scene is defaulted to a perspective projection mode, but can be toggled to an orthographic projection
bool SCENE_DEFAULT_PROJECTION = true;

//Fail Event (Camera collides with enemy)
//TODO
//The Enemy is approaching the camera (player), if the player is hit, game over
bool ENEMY_CLOSE_ENOUGH = false;


bool BUTTON1_PRESSED = false;
bool BUTTON2_PRESSED = false;
bool BUTTON3_PRESSED = false;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void processInput(GLFWwindow *window, float deltaTime) {
    // Exit window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // Camera movement controls <W, A, S, D>
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    // Toggle Brightness controls <K, L>
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && SHOW_DELAY == 0) {
        SHOW_DELAY = 20;
        //TODO
        if (torchSetting > 0)
        {
            torchSetting--;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && SHOW_DELAY == 0) {
        //TODO
        //increase brightness of scene
        SHOW_DELAY = 20;
        if (torchSetting < 6)
        {
            torchSetting++;
        }
    }

    // Toggle projection mode <P>
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && SHOW_DELAY == 0) {
        SHOW_DELAY = 50;
        if (SCENE_DEFAULT_PROJECTION) {
            SCENE_DEFAULT_PROJECTION = false;
        } else {
            SCENE_DEFAULT_PROJECTION = true;
        }
    }

    //Restart Game <R>
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && SHOW_DELAY == 0) {
        SHOW_DELAY = 50;
        // TODO
        // restart game
    }

    //Toggle scene Illumination mode
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && SHOW_DELAY == 0) {
        SHOW_DELAY = 50;
        if (SCENE_DEFAULT_BRIGHTNESS) {
            //set to bright scene
            SCENE_DEFAULT_BRIGHTNESS = false;
        } else {
            SCENE_DEFAULT_BRIGHTNESS = true;
        }
    }
}

void update_delay()
{
    if(BUTTON_DELAY > 0) BUTTON_DELAY -= 1;
    if(SHOW_DELAY > 0) SHOW_DELAY -= 1;
}
