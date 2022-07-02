#include <bits/stdc++.h>
using namespace std;

#define uli unsigned long long int
#define MAF printf("Sorry, Memory Allocation Failed. Cannot Process Further.\n");
#define FAF printf("Cannot Process The File.\n");
#define FUP printf("Files Are Under Processing...\n");

int BACKGROUND = 0;
int FOREGROUND = 1;

// Structure for an input binary image
typedef struct Input_Binary_Image
{
    /* NOTE -->  Height, Width, Maximum Pixel Value and Magic No. of the Image  */
    int height;
    int width;
    char magicNo[2];
    int **pixelData;
} binImg;

// Dilation morphological operation
binImg *dilation(binImg *img)
{
    int seh, sew;
    printf("Height and Width of SE for dilation: ");
    scanf("%d %d", &seh, &sew);

    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            int kernel[seh][sew];
            for (int k = 0; k < seh; k++)
            {
                for (int l = 0; l < sew; l++)
                {
                    kernel[k][l] = 1;
                }
            }
            if (((i + seh) < img->height) && ((j + sew) < img->width))
            {
                for (int k = 0; k < seh; k++)
                {
                    for (int l = 0; l < sew; l++)
                    {
                        if (img->pixelData[i + k][j + l] == kernel[k][l])
                        {
                            img->pixelData[i + (seh / 2)][j + (sew / 2)] = FOREGROUND;
                            break;
                        }
                        else
                            img->pixelData[i + (seh / 2)][j + (sew / 2)] = BACKGROUND;
                    }
                }
            }
        }
    }
    // printf("Dilation Done...\n");
    return img;
}

// Erosion morphological operation
binImg *erosion(binImg *img)
{
    int seh, sew;
    printf("Height and Width of SE for erosion: ");
    scanf("%d %d", &seh, &sew);

    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            int kernel[seh][sew];
            for (int k = 0; k < seh; k++)
            {
                for (int l = 0; l < sew; l++)
                {
                    kernel[k][l] = 1;
                }
            }
            if (((i + seh) < img->height) && ((j + sew) < img->width))
            {
                for (int k = 0; k < seh; k++)
                {
                    for (int l = 0; l < sew; l++)
                    {
                        if (img->pixelData[i + k][j + l] != kernel[k][l])
                        {
                            img->pixelData[i + seh / 2][j + sew / 2] = BACKGROUND;
                            break;
                        }
                        else
                            img->pixelData[i + seh / 2][j + sew / 2] = FOREGROUND;
                    }
                }
            }
        }
    }
    // printf("Erosion Done...\n");
    return img;
}

// Opening Operation = erosion -> dilation
binImg *opening(binImg *img)
{
    img = erosion(img);
    img = dilation(img);
    // printf("\nOpening Done!\n");
    return img;
}

// Closing Operation = dilation -> erosion
binImg *closing(binImg *img)
{
    img = dilation(img);
    img = erosion(img);
    // printf("\nClosing Done!\n");
    return img;
}

// Returns an array of the positions of the headlines in the text image
int *get_headlines(binImg *img, int *headlines)
{
    int pixelRow[img->height];
    for (int i = 0; i < img->height; i++)
    {
        pixelRow[i] = 0;
        for (int j = 0; j < img->width; j++)
        {
            pixelRow[i] += img->pixelData[i][j];
        }
    }

    headlines = (int *)malloc(img->height * sizeof(int));

    for (int i = 0; i < img->height; i++)
    {
        if (pixelRow[i] > 50)
            headlines[i] = 1;
        else
            headlines[i] = 0;
    }

    return headlines;
}

// Utility function to remove headlines from the actual text image
binImg *remove_headlines(binImg *image1, int *headlines)
{
    for (int i = 0; i < image1->height - 2; i++)
    {
        if (headlines[i] == 1)
        {
            for (int j = 0; j < image1->width; j++)
            {
                image1->pixelData[i][j] = BACKGROUND;
                image1->pixelData[i + 1][j] = BACKGROUND;
                image1->pixelData[i + 2][j] = BACKGROUND;
            }
        }
    }

    return image1;
}

// Utility function to export image file
void export_image(binImg *img, FILE *out)
{
    if (!img)
    {
        printf("No Image File...\n");
        exit(0);
    }
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            fprintf(out, "%d ", img->pixelData[i][j]);
        }
        fprintf(out, "\n");
    }

    printf("Output file is ready...");
}

// Utility function to free image file
void free(binImg *img)
{
    free(img->pixelData);
    img->pixelData = NULL;
    free(img);
}


int isolate_char(binImg *img)
{
    /* ----------------- Horizontal Projection ----------------- */
    int pixelRow[img->height] = {0};
    for (int i = 0; i < img->height; i++)
    {
        int s = 0;
        for (int j = 0; j < img->width; j++)
        {
            s += img->pixelData[i][j];
        }
        pixelRow[i] = s;
    }


    /* ----------------- Textline detection and counting ----------------- */
    int line_start_count = 0;
    int line_end_count = 0;

    for (int i = 0; i < img->height; i++)
    {
        if (pixelRow[i] == 0 && pixelRow[i + 1] != 0)
        {
            line_start_count++;
        }
        else if (pixelRow[i] != 0 && pixelRow[i + 1] == 0)
        {
            line_end_count++;
        }
    }


    int line_start[line_start_count] = {0};
    int line_end[line_end_count] = {0};

    int s = 0, e = 0;
    for (int i = 0; i < img->height; i++)
    {
        if (pixelRow[i] == 0 && pixelRow[i + 1] > 0 && s <= line_start_count)
        {
            line_start[s] = i + 1;
            s++;
        }
        else if (pixelRow[i] > 0 && pixelRow[i + 1] == 0 && e <= line_end_count)
        {
            line_end[e] = i;
            e++;
        }
    }


    /* ----------------- Average Line Height Calculation ----------------- */
    int avg_line_height = 0;
    int line_heights[line_start_count];

    for (int i = 0; i < line_start_count; i++)
    {
        line_heights[i] = line_end[i] - line_start[i];
        avg_line_height += line_heights[i];
    }
    avg_line_height /= line_start_count;


    /* ----------------- Zone Identification ----------------- */
    // Baseline: Separates middle & bottom zone
    for (int l = 0; l < line_start_count; l++)
    {

        for (int j = 0; j < img->width; j++)
        {
            img->pixelData[line_start[l] + avg_line_height - 3][j] = BACKGROUND;
        }
    }

    int baseline[line_start_count] = {0};
    for (int i = 0; i < line_start_count; i++)
    {
        baseline[i] = line_start[i] + avg_line_height - 3;
    }

    // Topline: separates upper & middle zone
    // for (int l = 0; l < line_start_count; l++)
    // {

    //     for (int j = 0; j < img->width; j++)
    //     {
    //         img->pixelData[baseline[l] - avg_line_height + 18][j] = BACKGROUND;
    //     }
    // }

    int topline[line_start_count] = {0};
    for (int i = 0; i < line_start_count; i++)
    {
        topline[i] = baseline[i] - avg_line_height + 18;
    }


    /* ----------------- Characters Isolation ----------------- */
    int flag;
    for (int i = 0; i < line_start_count; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            flag = 0;
            if(img->pixelData[topline[i]-3][j] == FOREGROUND){
                for(int k=5; k<avg_line_height-10; k++){
                    if(img->pixelData[topline[i]+k][j] == FOREGROUND)
                        flag=1;
                }
            }
            else if(img->pixelData[topline[i]-2][j] == FOREGROUND){
                for(int k=5; k<avg_line_height-10; k++){
                    if(img->pixelData[topline[i]+k][j] == FOREGROUND)
                        flag=1;
                }
            }
            else if(img->pixelData[topline[i]-1][j] == FOREGROUND){
                for(int k=5; k<avg_line_height-10; k++){
                    if(img->pixelData[topline[i]+k][j] == FOREGROUND)
                        flag=1;
                }
            }
            else if(img->pixelData[topline[i]+1][j] == FOREGROUND){
                for(int k=5; k<avg_line_height-10; k++){
                    if(img->pixelData[topline[i]+k][j] == FOREGROUND)
                        flag=1;
                }
            }
            else if(img->pixelData[topline[i]+2][j] == FOREGROUND){
                for(int k=5; k<avg_line_height-10; k++){
                    if(img->pixelData[topline[i]+k][j] == FOREGROUND)
                        flag=1;
                }
            }
            else if(img->pixelData[topline[i]+3][j] == FOREGROUND){
                for(int k=5; k<avg_line_height-10; k++){
                    if(img->pixelData[topline[i]+k][j] == FOREGROUND)
                        flag=1;
                }
            }

            if(flag == 0){
                    for (int c = -5; c <= 3; c++){
                        img->pixelData[topline[i] + c][j] = BACKGROUND;
                    }
                }
        }
    }

    return avg_line_height;
}


// DRIVER CODE
int main(int argc, char *argv[])
{
    FILE *in = NULL, *out = NULL;
    in = fopen(argv[1], "rb");
    out = fopen(argv[2], "w");

    if ((in != NULL) && (out != NULL)) { FUP; }
    else { FAF; }

    /* Creating an image structure from the input image to access data more conviniently */
    binImg *img1 = (binImg *)malloc(sizeof(binImg));
    binImg *copy = (binImg *)malloc(sizeof(binImg));

    fgets(img1->magicNo, 3, in); // reads from input file
    fscanf(in, "\n");            // reads the newline character
    fputs(img1->magicNo, out);   // 'P1' is the Magic No for a outary Image
    fputs("\n", out);            // writes the newline character

    fscanf(in, "%d %d", &img1->width, &img1->height); // reads
    fscanf(in, "\n");                                 // reads the newline character
    printf("Image Resolution(W x H): %d x %d\n", img1->width, img1->height);
    fprintf(out, "%d %d", img1->width, img1->height); // writes
    fprintf(out, "\n");                               // writes the newline character

    img1->pixelData = NULL;
    copy->pixelData = NULL;

    copy->height = img1->height;
    copy->width = img1->width;

    img1->pixelData = (int **)malloc(img1->height * sizeof(int *));
    copy->pixelData = (int **)malloc(copy->height * sizeof(int *));

    if (img1->pixelData == NULL || copy->pixelData == NULL)
        MAF;

    /* NOTE ---------- Reads and Writes Every Pixel's Value ---------- */
    for (int i = 0; i < img1->height; i++)
    {
        img1->pixelData[i] = (int *)malloc(img1->width * sizeof(int));
        copy->pixelData[i] = (int *)malloc(copy->width * sizeof(int));
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

    for (int i = 0; i < img1->height; i++)
    {
        for (int j = 0; j < img1->width; j++)
        {
            copy->pixelData[i][j] = img1->pixelData[i][j];
        }
    }

    int avg_line_height = isolate_char(img1);
    copy = opening(copy); // 3x25
    // int *headlines = get_headlines(copy, headlines);
    // img1 = remove_headlines(img1, headlines);

    export_image(img1, out); // Exports image to the o/p file

    fclose(in);
    fclose(out);
    free(img1);
    free(copy);

    return 0;
}
