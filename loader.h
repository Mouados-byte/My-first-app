
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h> 

class loader
{
	
	
public:
	int my_image_width;
	int my_image_height;
	GLuint my_image_texture;
	bool ret;
	loader();
	bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);
	void printtexture(const char* filename , int out_width, int out_height);
};

