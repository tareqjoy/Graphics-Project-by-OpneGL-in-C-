
#include <fstream>
#include <iostream>
#include <GL/glut.h>


#define checkImageWidth 512
#define checkImageHeight 512



using namespace std;


GLuint texture[20]={0};
int texture_index=2;

struct Image {

    unsigned long sizeX;

    unsigned long sizeY;

    char *data;

};

Image save_image[20];
typedef struct Image Image;

GLubyte checkImage[checkImageWidth][checkImageHeight][3];

void makeCheckImage(void){

    int i, j, c;

    for (i = 0; i < checkImageWidth; i++) {

        for (j = 0; j < checkImageHeight; j++) {

            c = ((((i&0x8)==0)^((j&0x8)==0)))*255;

            checkImage[i][j][0] = (GLubyte) c;

            checkImage[i][j][1] = (GLubyte) c;

            checkImage[i][j][2] = (GLubyte) c;

        }

    }

}




int ImageLoad(char *filename, Image *image) {

    FILE *file;

    unsigned long size; // size of the image in bytes.

    unsigned long i; // standard counter.

    unsigned short int planes; // number of planes in image (must be 1)

    unsigned short int bpp; // number of bits per pixel (must be 24)

    char temp; // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.

    if ((file = fopen(filename, "rb"))==NULL){

        printf("File Not Found : %s\n",filename);

        return 0;

    }

    // seek through the bmp header, up to the width/height:

    fseek(file, 18, SEEK_CUR);

    // read the width

    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {

        printf("Error reading width from %s.\n", filename);

        return 0;

    }

    //printf("Width of %s: %lu\n", filename, image->sizeX);

    // read the height

    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {

        printf("Error reading height from %s.\n", filename);

        return 0;

    }

    //printf("Height of %s: %lu\n", filename, image->sizeY);

    // calculate the size (assuming 24 bits or 3 bytes per pixel).

    size = image->sizeX * image->sizeY * 3;

    // read the planes

    if ((fread(&planes, 2, 1, file)) != 1) {

        printf("Error reading planes from %s.\n", filename);

        return 0;

    }

    if (planes != 1) {

        printf("Planes from %s is not 1: %u\n", filename, planes);

        return 0;

    }

    // read the bitsperpixel

    if ((i = fread(&bpp, 2, 1, file)) != 1) {

        printf("Error reading bpp from %s.\n", filename);

        return 0;

    }

    if (bpp != 24) {

        printf("Bpp from %s is not 24: %u\n", filename, bpp);

        return 0;

    }

    // seek past the rest of the bitmap header.

    fseek(file, 24, SEEK_CUR);

    // read the data.

    image->data = (char *) malloc(size);

    if (image->data == NULL) {

        printf("Error allocating memory for color-corrected image data");

        return 0;

    }

    if ((i = fread(image->data, size, 1, file)) != 1) {

        printf("Error reading image data from %s.\n", filename);

        return 0;

    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)

        temp = image->data[i];

        image->data[i] = image->data[i+2];

        image->data[i+2] = temp;

    }

    // we're done.

    return 1;

}


Image loadTexture(char *path){

    Image *image1;

    // allocate space for texture

    image1 = (Image *) malloc(sizeof(Image));

    if (image1 == NULL) {

        printf("Error allocating space for image");

        exit(0);

    }

    if (!ImageLoad(path, image1)) {

        exit(1);

    }

    Image image_1;
    image_1.sizeX=image1->sizeX;
    image_1.sizeY=image1->sizeY;
    image_1.data=image1->data;
    return image_1;

}


void set_texture(int texture_index,char *path)
{
    save_image[texture_index] = loadTexture(path);
    /*

    if(save_image[texture_index] == NULL){

        printf("Image was not returned from loadTexture\n");

        exit(0);

    }*/

    makeCheckImage();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Create Texture

    //glGenTextures(5, texture);

    glBindTexture(GL_TEXTURE_2D, texture_index);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); //scale linearly when image bigger than texture

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //scale linearly when image smalled than texture

    glTexImage2D(GL_TEXTURE_2D, 0, 3, save_image[texture_index].sizeX, save_image[texture_index].sizeY, 0,

    GL_RGB, GL_UNSIGNED_BYTE, save_image[texture_index].data);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);



    //glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_FLAT);

}

