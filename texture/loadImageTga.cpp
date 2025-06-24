#pragma once
#include <stdio.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <string.h> 

#pragma pack(push, 1)
struct TGAHeader {
    unsigned char idLength;
    unsigned char colorMapType;
    unsigned char imageType;
    unsigned short colorMapOrigin;
    unsigned short colorMapLength;
    unsigned char colorMapDepth;
    unsigned short xOrigin;
    unsigned short yOrigin;
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char descriptor;
};
#pragma pack(pop)

GLuint loadTGA_custom(const char* imagepath) {
    FILE* file = fopen(imagepath, "rb");
    if (!file) {
        printf("Image could not be opened\n");
        return 0;
    }

    TGAHeader header;
    if (fread(&header, sizeof(TGAHeader), 1, file) != 1) {
        printf("Could not read TGA header\n");
        fclose(file);
        return 0;
    }

    // Skip image ID if present
    if (header.idLength > 0) {
        fseek(file, header.idLength, SEEK_CUR);
    }

    // We only support uncompressed true-color images
    if (header.imageType != 2) {  // 2 = uncompressed true-color
        printf("Unsupported TGA image type (only uncompressed true-color supported)\n");
        fclose(file);
        return 0;
    }

    // We only support 24 or 32 bpp images
    if (header.bpp != 24 && header.bpp != 32) {
        printf("Unsupported TGA bit depth (only 24 and 32 bpp supported)\n");
        fclose(file);
        return 0;
    }

    const int width = header.width;
    const int height = header.height;
    const int channels = header.bpp / 8;
    const int imageSize = width * height * channels;

    unsigned char* data = new unsigned char[imageSize];
    if (fread(data, 1, imageSize, file) != imageSize) {
        printf("Could not read image data\n");
        delete[] data;
        fclose(file);
        return 0;
    }
    fclose(file);

    // TGA stores pixels as BGR(A), so we need to swap to RGB(A)
    for (int i = 0; i < imageSize; i += channels) {
        // Instead of std::swap, use manual swapping:
        unsigned char temp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = temp;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // Set default texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    delete[] data;
    return textureID;
}