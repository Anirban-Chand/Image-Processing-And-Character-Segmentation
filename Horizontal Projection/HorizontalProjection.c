#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define uli unsigned long long int
#define MAF printf("Sorry, Memory Allocation Failed. Cannot Process Further.\n");
#define FAF printf("Cannot process The File.\n");
#define FUP printf("Files Are Under Processing...\n");

int background = 0;
int foreground = 1;


typedef struct Input_Binary_Image{
    /* NOTE -->  Height, Width, Maximum Pixel Value and Magic No. of the Image  */
    int height;
    int width;
    char magicNo[2];
    int **pixelData;
}binImg;

typedef struct Structuring_Element{
    /* NOTE -->  Height, Width of the Kernel  */
    int kernel_height;
    int kernel_width;
    int **kernel_data;
}kernel;

int* get_projection(binImg* img, int* pixelRow){
    // uli horizontal[img->height];
    for (int i = 0; i < img->height; i++)
    {
        pixelRow[i] = 0;
        // horizontal[i]=0;
        for (int j = 0; j < img->width; j++)
        {
            pixelRow[i]+=img->pixelData[i][j];  
        }
    }
    printf("Projection Catched...\n");
    return pixelRow;

    // int lineThreshold=30;
    // for(int i=0; i<img->height; i++){
    //     if(pixelRow[i]>=lineThreshold)
    //         horizontal[i]=1;
    //     else
    //         horizontal[i]=0;
    // }

    // uli lineStart[img->height], lineEnd[img->height];
    // for(int i=0, j=0; i<img->height-1, j<100; i++, j++){
    //     lineStart[i]=0;
    //     lineEnd[i]=0;
    //     if(horizontal[i] == 0 && horizontal[i+1] == 1)
    //         lineStart[i] = i;
    //     else if(horizontal[i] == 1 && horizontal[i+1] == 0)
    //         lineEnd[j] = i;
    // }

    // for(int i=0; i<img->height; i++){
    //     printf("%d\n", horizontal[i]);
    // }
}

void export_image(binImg* img, FILE *out)
{
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            fprintf(out, "%d ", img->pixelData[i][j]);
        }
        fprintf(out, "\n");
    }

    printf("\nOutput file is ready...\n");
}

int main(int argc, char *argv[])
{
    /* NOTE ---------- [in = input file/import from   ||   out = output file/export to] ----------*/
    FILE *in = NULL, *out = NULL;

    
    /* NOTE ---------- Opening Input File in Read Mode ---------- */
    in = fopen(argv[1], "rb");

    /* NOTE ---------- Opening file in write-binary('wb') mode for binarization ---------- */
    out = fopen(argv[2], "wb");

    /* NOTE ---------- Check whether the file pointers have been opened required files or not ---------- */
    if ((in != NULL) && (out != NULL))
    {
        FUP; // FUP has been defined
    }
    else
    {
        FAF; // FAF has been defined
    }


    /* Creating an image structure from the input image to access data more conviniently */ 
    binImg *img1 = (binImg*)malloc(sizeof(binImg));

    /* NOTE ---------- Reads and Writes the Magic No of the Image ---------- */
    fgets(img1->magicNo, 3, in); // reads from input file
    fscanf(in, "\n");      // reads the newline character
    fputs(img1->magicNo, out);      // 'P1' is the Magic No for a outary Image
    fputs("\n", out);      // writes the newline character

    /* NOTE ---------- Reads and Writes the Width and Height of the Image ---------- */
    fscanf(in, "%d %d", &img1->width, &img1->height); // reads
    fscanf(in, "\n");                     // reads the newline character
    printf("Image Resolution(W x H): %d x %d\n", img1->width, img1->height);
    fprintf(out, "%d %d", img1->width, img1->height); // writes
    fprintf(out, "\n");                   // writes the newline character


    /* NOTE ---------- 2-D Image Array to store Pixel Values ---------- */
    /* NOTE ---------- 
                        'image' is the array of pointers,
                        each of its part stores the base address 
                        of the nested arrays that's why we should
                        use double star(int **image) ---------- */
    img1->pixelData = NULL;

    img1->pixelData = (int **)malloc(img1->height * sizeof(int *));
    if (img1->pixelData == NULL)
        MAF;

    /* NOTE ---------- Reads and Writes Every Pixel's Value ---------- */
    for (int i = 0; i < img1->height; i++)
    {
        img1->pixelData[i] = (int *)malloc(img1->width * sizeof(int));

        for (int j = 0; j < img1->width; j++)
        {
            int x;
            fscanf(in, "%d", &x);
            fscanf(in, "\n");
            img1->pixelData[i][j] = x;
            if (feof(in))
                break;
        }
    }

    binImg* img2 = (binImg*)malloc(sizeof(binImg));
    memcpy(img2->magicNo, img1->magicNo, 3);
    img2->height = img1->height;
    img2->width = img1->width;
    img2->pixelData = (int**)malloc(img1->height * sizeof(int*));
    if (img2->pixelData == NULL)
        MAF;
    
    for (int i = 0; i < img2->height; i++)
    {
        img2->pixelData[i] = (int*)malloc(img1->width * sizeof(int));
        for(int j=0; j<img1->width; j++)
            img2->pixelData[i][j] = background;
    }


    int* pixelRow = (int*)malloc(img1->height * sizeof(int));
    pixelRow = get_projection(img1, pixelRow);

    for (int i = 0; i < img2->height; i++)
    {
        for(int j=0; j<pixelRow[i]; j++){
            img2->pixelData[i][j] = foreground;
        }
    }

    export_image(img2, out);

    fclose(in);
    fclose(out);
    free(img1->pixelData);
    free(img2->pixelData);

    return 0;
}
