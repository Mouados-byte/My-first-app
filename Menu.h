//Includes
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "fileio.h"
#include "settings.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <fstream>
#include <string>
#include <GLFW/glfw3.h>



class Menu
{
	
public:
	
	void Render(ImGuiStyle* style , std::vector<LOGIN>& resources , std::vector<LOGIN>& new_content);
	void Theme(ImGuiStyle* style);

};

