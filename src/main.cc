#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <iostream>

#include "ft2build.h"
#include FT_FREETYPE_H

using namespace std;
 
int main()
{
    cout << "hello" << endl;
    
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
        return 0;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return 0;
	}

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 0.3f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glm::vec3 t;

	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
	}else{
		cout << "gggggg" << endl;
	}

	FT_Face face;
	if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face)) {
		cout << "ERROR::FREETYPE: Failed to load font" << endl;
	}else{
		cout << "ttttttttt";
	}

	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return 0;
}
