#pragma once
#include <stdio.h>
#include <GL/freeglut.h>
#include <webp/decode.h>
#include <stdlib.h>

GLuint loadWebP_custom(const char* imagepath) {
    FILE* file = fopen(imagepath, "rb");
    if (!file) {
        printf("Image could not be opened\n");
        return 0;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Read file data
    uint8_t* file_data = (uint8_t*)malloc(file_size);
    if (!file_data) {
        printf("Memory allocation failed\n");
        fclose(file);
        return 0;
    }
    
    if (fread(file_data, 1, file_size, file) != file_size) {
        printf("Could not read file\n");
        free(file_data);
        fclose(file);
        return 0;
    }
    fclose(file);

    // Decode WebP
    int width, height;
    uint8_t* pixel_data = WebPDecodeRGBA(file_data, file_size, &width, &height);
    free(file_data);
    
    if (!pixel_data) {
        printf("WebP decoding failed\n");
        return 0;
    }

    // Create OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data);
    
    // Set texture parameters (optional)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Free WebP decoded data
    WebPFree(pixel_data);

    return textureID;
}