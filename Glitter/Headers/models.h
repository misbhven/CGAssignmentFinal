//
// Created by cg on 29/10/20.
//

#ifndef ASSIGNMENT_MODELS_H
#define ASSIGNMENT_MODELS_H

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
#include "cameraControls.h"

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION

void render_grass(unsigned int VAO, Shader* light_shader);
void render_sky(unsigned int VAO, Shader* light_shader);
void render_(unsigned int VAO, Shader* light_shader);
void render_trees(unsigned int VAO, Shader* light_shader);
void render_light(unsigned int VAO_light);

void initTextures();
unsigned int loadTexture(char const * path);

//lighting for world

#endif //ASSIGNMENT_MODELS_H
