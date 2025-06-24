#pragma once
#include <stdio.h>
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <string.h> 

struct my_error_mgr {
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};

METHODDEF(void) my_error_exit(j_common_ptr cinfo) {
    my_error_mgr* myerr = (my_error_mgr*)cinfo->err;
    (*cinfo->err->output_message)(cinfo);
    longjmp(myerr->setjmp_buffer, 1);
}

GLuint loadJPG_custom(const char* imagepath) {
    struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;
    FILE* file;
    JSAMPARRAY buffer;
    unsigned char* data = NULL;
    GLuint textureID = 0;

    if ((file = fopen(imagepath, "rb")) == NULL) {
        printf("Image could not be opened\n");
        return 0;
    }

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        fclose(file);
        if (data) free(data);
        return 0;
    }

    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int channels = cinfo.output_components;

    data = (unsigned char*)malloc(width * height * channels);
    if (!data) {
        printf("Memory allocation failed\n");
        jpeg_destroy_decompress(&cinfo);
        fclose(file);
        return 0;
    }

    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width * channels, 1);

    while (cinfo.output_scanline < cinfo.output_height) {
        unsigned char* rowptr = data + (cinfo.output_scanline) * width * channels;
        jpeg_read_scanlines(&cinfo, buffer, 1);
        memcpy(rowptr, buffer[0], width * channels);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    free(data);
    return textureID;
}