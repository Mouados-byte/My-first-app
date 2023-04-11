#include "loader.h"
#include <iostream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

loader::loader() {
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
}

// Simple helper function to load an image into a OpenGL texture with common settings
bool loader::LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{

    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL) {
        return false;
    }
        
    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

void loader::printtexture(const char* filename, int out_width, int out_height) {
    ret = LoadTextureFromFile("Resources/pop_cat.png", &my_image_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(out_width,out_height));
}

