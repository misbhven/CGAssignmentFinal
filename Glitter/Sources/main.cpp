// Local Headers
#include "main.h"
#include <cstdio>
// Screen dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//time logic
float deltaTime = 0.0f;
float lastFrame = 0.0f;

extern float box[288];
extern bool SCENE_DEFAULT_BRIGHTNESS;
extern bool SCENE_DEFAULT_PROJECTION;
extern float torchBrightnessLevels[];
extern int torchSetting;
extern Camera camera;
extern glm::vec3 light_pos;




int main(int argc, char * argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SpookyForest_1.0", NULL, NULL);

    // Check for Valid Context
    if (window == NULL) {
        std::cout << "Failed to Create OpenGL Context" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //check glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);


    //TODO - set up shaders
    Shader light_shader("./shader.vs", "./shader.fs");
    Shader lamp_shader("./lamp.vs" , "./lamp.fs");


    //TODO - set up buffers and array objects
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //binds
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // color attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //vertex array object for the lighting
    unsigned int VAO_light;
    glGenVertexArrays(1, &VAO_light);
    glBindVertexArray(VAO_light);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //update the lamp position attribute's stride
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //TODO - load all textures
    initTextures();

    //TODO - config shaders
    light_shader.use();
    light_shader.setInt("material.diffuse", 0);
    light_shader.setInt("material.specular", 1);

    glm::mat4 projection;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        //SETUP
        //-------------------------------------------------------------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //update keystroke "cooldowns"
        update_delay();

        //input from user
        processInput(window, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //TODO - light properties

        if (SCENE_DEFAULT_BRIGHTNESS)
        {
            light_shader.use();
            light_shader.setVec3("light.ambient", torchBrightnessLevels[torchSetting], torchBrightnessLevels[torchSetting], torchBrightnessLevels[torchSetting]);

            light_shader.setVec3("light.position", camera.Position);
            light_shader.setVec3("light.direction", camera.Front);
            light_shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
            light_shader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
            light_shader.setVec3("viewPos", camera.Position);
        }
        else
        {
            light_shader.use();
            light_shader.setVec3("light.ambient", 50.0f, 50.0f, 50.0f);

            light_shader.setVec3("light.position", light_pos);
            light_shader.setVec3("viewPos", camera.Position);

        }
        light_shader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
        light_shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        light_shader.setFloat("light.constant", 1.0f);
        light_shader.setFloat("light.linear", 0.09f);
        light_shader.setFloat("light.quadratic", 0.032f);
        light_shader.setFloat("material.shininess", 32.0f);
        //TODO - projection
        if(SCENE_DEFAULT_PROJECTION)
        {
            projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        }
        else
        {
            projection = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, 1.0f, 100.0f);
        }

        // camera transformation
        glm::mat4 view = camera.GetViewMatrix();
        light_shader.setMat4("projection", projection);
        light_shader.setMat4("view", view);

        //draw
        render_grass(VAO, &light_shader);
        render_sky(VAO, &light_shader);
        render_trees(VAO, &light_shader);
        render_light(VAO_light);



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VAO_light);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void init()
{

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------

