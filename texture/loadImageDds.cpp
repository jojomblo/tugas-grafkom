#pragma once
#include <stdio.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <string.h>  

// DDS header flags
#define DDSD_CAPS          0x00000001
#define DDSD_HEIGHT        0x00000002
#define DDSD_WIDTH         0x00000004
#define DDSD_PITCH         0x00000008
#define DDSD_PIXELFORMAT   0x00001000
#define DDSD_MIPMAPCOUNT   0x00020000
#define DDSD_LINEARSIZE    0x00080000
#define DDSD_DEPTH         0x00800000

// Pixel format flags
#define DDPF_ALPHAPIXELS   0x00000001
#define DDPF_FOURCC        0x00000004
#define DDPF_RGB           0x00000040

// FourCC codes for compressed formats
#define FOURCC_DXT1 0x31545844  
#define FOURCC_DXT3 0x33545844  
#define FOURCC_DXT5 0x35545844  

struct DDS_PIXELFORMAT {
    unsigned int dwSize;
    unsigned int dwFlags;
    unsigned int dwFourCC;
    unsigned int dwRGBBitCount;
    unsigned int dwRBitMask;
    unsigned int dwGBitMask;
    unsigned int dwBBitMask;
    unsigned int dwABitMask;
};

struct DDS_HEADER {
    unsigned int dwSize;
    unsigned int dwFlags;
    unsigned int dwHeight;
    unsigned int dwWidth;
    unsigned int dwPitchOrLinearSize;
    unsigned int dwDepth;
    unsigned int dwMipMapCount;
    unsigned int dwReserved1[11];
    DDS_PIXELFORMAT ddspf;
    unsigned int dwCaps;
    unsigned int dwCaps2;
    unsigned int dwCaps3;
    unsigned int dwCaps4;
    unsigned int dwReserved2;
};

GLuint loadDDS_custom(const char* imagepath) {
    FILE* file = fopen(imagepath, "rb");
    if (!file) {
        printf("Could not open DDS file\n");
        return 0;
    }

    // Verify the file is a DDS file
    char filecode[4];
    fread(filecode, 1, 4, file);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(file);
        printf("Not a valid DDS file\n");
        return 0;
    }

    // Read the header
    DDS_HEADER header;
    fread(&header, sizeof(DDS_HEADER), 1, file);

    unsigned int width = header.dwWidth;
    unsigned int height = header.dwHeight;
    unsigned int linearSize = header.dwPitchOrLinearSize;
    unsigned int mipMapCount = header.dwMipMapCount;
    unsigned int fourCC = header.ddspf.dwFourCC;

    // Determine format
    GLenum format;
    unsigned int blockSize = 16; // Default to DXT5 block size
    
    if (fourCC == FOURCC_DXT1) {
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        blockSize = 8;
    }
    else if (fourCC == FOURCC_DXT3) {
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
    }
    else if (fourCC == FOURCC_DXT5) {
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
    }
    else {
        fclose(file);
        printf("Unsupported DDS format\n");
        return 0;
    }

    // Calculate buffer size
    unsigned int bufSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    unsigned char* buffer = (unsigned char*)malloc(bufSize * sizeof(unsigned char));
    fread(buffer, 1, bufSize, file);
    fclose(file);

    // Create OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Load the mipmaps
    unsigned int offset = 0;
    unsigned int w = width;
    unsigned int h = height;
    
    for (unsigned int level = 0; level < mipMapCount && (w || h); ++level) {
        unsigned int size = ((w + 3) / 4) * ((h + 3) / 4) * blockSize;
        
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, w, h, 
                              0, size, buffer + offset);
        
        offset += size;
        w /= 2;
        h /= 2;
    }

    free(buffer);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   mipMapCount > 1 ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return textureID;
}