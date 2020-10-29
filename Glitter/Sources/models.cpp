//
// Created by cg on 29/10/20.
//

#include "models.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

glm::vec3 light_pos(0.0f, 40.0f, 0.1f);

//texture IDs
unsigned int tex_wood_diffuse, tex_street_diffuse, tex_grass_diffuse, tex_marble_diffuse, tex_curtin_diffuse, tex_sky_diffuse;
unsigned int tex_wood_specular, tex_street_specular, tex_grass_specular, tex_marble_specular, tex_curtin_specular, tex_sky_specular;

unsigned int tex_red_dark_diffuse, tex_red_bright_diffuse, tex_red_diffuse, tex_green_diffuse, tex_blue_diffuse;
unsigned int tex_red_dark_specular, tex_red_bright_specular, tex_red_specular, tex_green_specular, tex_blue_specular;

float box[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

void render_grass(unsigned int VAO, Shader* light_shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    light_shader->setMat4("model", model);
    //need VAO
    //need glm::mat4 model
    //relevant shaders
    //do textures in this class

    //DRAW OBJECTS

    //---------------------------------------------------------------------
    // GRASS (the ground plane)
    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_grass_diffuse);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex_grass_specular);

    model = glm::mat4(1.0f);
    //move grass plane slightly below origin
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    //scale the grass plane model so that it is very flat and covers a large area
    model = glm::scale(model, glm::vec3(50.0f , 0.001f, 50.0f));

    light_shader->setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);

}

void render_sky(unsigned int VAO, Shader* light_shader)
{
    //SKYBOX (the box that envelops the scene)

    glm::mat4 model = glm::mat4(1.0f);
    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_sky_diffuse);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex_sky_specular);

    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));

    light_shader->setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void render_trees(unsigned int VAO, Shader* light_shader)
{
    glm::mat4 model = glm::mat4(1.0f);

    glm::vec3 tree_scales[] = {
            glm::vec3(0.3f, 4.0f, 0.3f),  //trunk
            glm::vec3(3.0f, 0.25f, 3.0f), //bottom leaves
            glm::vec3(2.0f, 0.25f, 2.0f), //lower leaves
            glm::vec3(1.5f, 0.25f, 1.5f), //upper leaves
            glm::vec3(0.5f, 0.5f, 0.5f) //top leaves

    };

    glm::vec3 tree_pos[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),  //trunk
            glm::vec3(0.0f, 0.5f, 0.0f), //bottom leaves
            glm::vec3(0.0f, 1.0f, 0.0f), //lower leaves
            glm::vec3(0.0f, 1.5f, 0.0f), //upper leaves
            glm::vec3(0.0f, 2.0f, 0.0f) //top leaves
    };

    glm::vec3 tree_locations[] = {
            glm::vec3(7.0f, 0.0f, 6.0f), //tree 1
            glm::vec3(-5.0f, 0.0f, -10.0f), //tree 2
            glm::vec3(2.0f, 0.0f, -3.0f), //tree 1
            glm::vec3(4.0f, 0.0f, 5.0f), //tree 2
            glm::vec3(7.0f, 0.0f, 10.0f), //tree 1
            glm::vec3(-12.0f, 0.0f, -2.0f), //tree 2
            glm::vec3(11.0f, 0.0f, 8.0f), //tree 1
            glm::vec3(-1.0f, 0.0f, -10.0f), //tree 2
    };


    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_grass_diffuse);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
    //glActiveTexture(GL_TEXTURE2);
    //glBindTexture(GL_TEXTURE_2D, tex_wood_diffuse);
    //glActiveTexture(GL_TEXTURE3);
    //glBindTexture(GL_TEXTURE_2D, tex_wood_diffuse);

    for(int tree = 0; tree < 8; tree++)
    {
        for(int tab = 0; tab < 5; tab++)
        {
            if (tab == 0) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, tex_wood_diffuse);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, tex_wood_specular);
            } else {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, tex_grass_diffuse);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, tex_grass_diffuse);
            }
            model = glm::mat4(1.0f);
            model = glm::translate(model, tree_locations[tree]);
            model = glm::translate(model, tree_pos[tab]);
            model = glm::scale(model, tree_scales[tab]);

            light_shader->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}

void render_light(unsigned int VAO_light)
{
    glBindVertexArray(VAO_light);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void initTextures()
{
    tex_wood_diffuse = loadTexture("../../Glitter/resources/textures/wood2.jpg");
    tex_wood_specular = loadTexture("../../Glitter/resources/textures/wood2_specular.jpg");
    tex_street_diffuse = loadTexture("../../Glitter//textures/street.png");
    tex_street_specular = loadTexture("../../Glitter/resources/textures/street_specular.png");
    tex_grass_diffuse = loadTexture("../../Glitter/resources/textures/grass.jpg");
    tex_grass_specular = loadTexture("../../Glitter/resources/textures/grass_specular.jpg");
    tex_marble_diffuse = loadTexture("../../Glitter/resources/textures/marble.jpg");
    tex_marble_specular = loadTexture("../../Glitter/resources/textures/marble_specular.jpg");
    tex_curtin_diffuse = loadTexture("../../Glitter/resources/textures/curtin.jpg");
    tex_curtin_specular = loadTexture("../../Glitter/resources/textures/curtin_specular.jpg");
    tex_sky_diffuse = loadTexture("../../Glitter/resources/textures/night_sky.jpg");
    tex_sky_specular = loadTexture("../../Glitter/resources/textures/night_sky_specular.jpg");


    tex_red_dark_diffuse = loadTexture("../../Glitter/resources/textures/red_dark.jpg");
    tex_red_dark_specular = loadTexture("../../Glitter/resources/textures/red_dark_specular.jpg");
    tex_red_bright_diffuse = loadTexture("../../Glitter/resources/textures/red_bright.jpg");
    tex_red_bright_specular = loadTexture("../../Glitter/resources/textures/red_bright_specular.jpg");
    tex_red_diffuse = loadTexture("../../Glitter/resources/textures/red.jpg");
    tex_red_specular = loadTexture("../../Glitter/resources/textures/red_specular.jpg");
    tex_green_diffuse = loadTexture("../../Glitter/resources/textures/green.jpg");
    tex_green_specular = loadTexture("../../Glitter/resources/textures/green_specular.jpg");
    tex_blue_diffuse = loadTexture("../../Glitter/resources/textures/blue.jpg");
    tex_blue_specular = loadTexture("../../Glitter/resources/textures/blue_specular.jpg");


}

unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    //flip image
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    return textureID;

}