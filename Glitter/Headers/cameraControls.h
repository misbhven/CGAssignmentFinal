//
// Created by cg on 29/10/20.
//

#ifndef ASSIGNMENT_CAMERACONTROLS_H
#define ASSIGNMENT_CAMERACONTROLS_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "shader_m.h"

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION


void processInput(GLFWwindow *window, float deltaTime);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void update_delay();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);




#endif //ASSIGNMENT_CAMERACONTROLS_H
