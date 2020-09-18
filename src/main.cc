#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "game/game.h"
#include "core/resource_manager.h"

using namespace std;

void KeyCallback(GLFWwindow* window, int key, int scan_code, int action, int mode);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

// 屏幕的宽高，引入缩放的概念后，相当于设计分辨率
const unsigned int kWidth = 800;
const unsigned int kHeight = 600;

// 全局的缩放，可用于适配retina屏幕
glm::vec2 screen_scale;

Game breakout(kWidth, kHeight);
 
int main()
{
	// 初始化glfw
    glfwInit();
	// 使用OpenGL3.3版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 使用OpenGL核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, false);

	// 创建建一个窗口对象，这个对象存放了所有和窗口相关的数据
	GLFWwindow* window = glfwCreateWindow(kWidth, kHeight, "Breakout", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
        return 0;
	}
	// 设置当前线程的主上下文
	glfwMakeContextCurrent(window);

	// 给glad传入用来加载系统相关的OpenGL函数指针地址的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return 0;
	}

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	screen_scale = glm::vec2(screen_width / kWidth, screen_height / kHeight);

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	// OpenGL配置
	glViewport(0, 0, kWidth, kHeight);
	// 开启面剔除
	glEnable(GL_CULL_FACE);
	// 开启混合
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 初始化游戏
	breakout.Init(screen_scale);

	float delta_time = 0.0f;
	float last_time = 0.0f;

	breakout.state_ = kGameMenu;

    while (!glfwWindowShouldClose(window)) {
        float current_time = (float)glfwGetTime();
		delta_time = current_time - last_time;
		last_time = current_time;
        
        glfwPollEvents();

		// 处理用户输入
		breakout.ProcessInput(delta_time);
		
		breakout.Update(delta_time);

		// 渲染
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// 清理颜色缓冲
		glClear(GL_COLOR_BUFFER_BIT);
		breakout.Render();

		glfwSwapBuffers(window);
	}

	ResourceManager::Clear();
	glfwTerminate();

    return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scan_code, int action, int mode){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if(key >= 0 && key < 1024){
		if(action == GLFW_PRESS)
			breakout.keys_[key] = GL_TRUE;
		else if(action == GLFW_RELEASE){
			breakout.keys_[key] = GL_FALSE; 
			breakout.keys_processed_[key] = GL_FALSE; 
		}
	}
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height){
	// 保证视口与窗口大小一致
	glViewport(0, 0, width, height);
}