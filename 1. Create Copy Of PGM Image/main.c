#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Driver Code */
int main(int argc, char* argv[]){
    
    /* in = input file
       out = output file */
    FILE *in, *out;


    /* Height, Width and Maximum Pixel Value of the Image */
    int height,width,maxpix;


    /* Magic No of the Image and Str is for storing the strings read */
    char c,magicno[2],str[500];


    /* Opening Input File in Read Mode */
    in=fopen(argv[1],"r");
    if(in==NULL){
        /* Checks if the file opened successfully */
        printf("SORRY! Input File Opening Failed.\n");
    }
    else printf("Input File Opened.\n");


    /* Opening Output File in Write Mode */
    out=fopen(argv[2],"w");
    if(out==NULL){
        /* Checks if the file opened successfully */
        printf("SORRY! Output File Opening Failed.\n");
    }
    else printf("Output File Opened.\n");
    

    /* Reads and Writes the Magic No of the Image */
    fgets(magicno, 3, in); // reads from input file
    fscanf(in,"\n"); // reads the newline character
    printf("Magic No - %s\n",magicno);
    fputs(magicno,out); // writes in output file
    fputs("\n",out); // writes the newline character
    // printf("Magic No Written Successfully. :)\n");
    

    // fgets(str, 50, in); // reads the comment out line
    // printf("%s\n",str);
    

    /* Reads and Writes the Width and Height of the Image */
    fscanf(in, "%d %d", &width, &height); // reads
    fscanf(in,"\n"); // reads the newline character
    printf("Width = %d\tHeight = %d\n", width,height);
    fprintf(out, "%d %d", width,height); // writes
    fprintf(out,"\n"); // writes the newline character
    printf("Width and Height Written Successfully. :)\n");
    

    /* Reads and Writes the Maximum Pixel Value */
    fscanf(in, "%d", &maxpix);
    fprintf(out, "%d", maxpix);
    fscanf(in,"\n"); // reads the newline character
    fprintf(out,"\n"); // writes the newline character
    printf("Maximum Pixel Value = %d\n", maxpix);
    printf("Max Pixel Value Written Successfully. :)\n");


    printf("Image Details Has Been Written Successfully. :)\n");


    /* 2-D Image Array to store Pixel Values */
    /* 'image' is the array of pointers,
        each of its part stores the base address 
        of the nested arrays that's why we should use double pointer(int **image) */
    int **image; 
    image = (int**)malloc(height * sizeof(int*));
    if(image == NULL) printf("SORRY! Memory Allocation Failure.\n");
    else printf("Memory for the Image File Allocated.\n");


    /* Reads and Writes Every Pixel's Value */
    for(int i=0; i<height; i++){
        
        image[i] = (int*)malloc(width * sizeof(int));

        for(int j=0; j<width; j++){ 
            int x;
            fscanf(in, "%d", &x);
            fscanf(in, "\n");
            image[i][j]=x;
            fprintf(out, "%d ", image[i][j]);
            if(feof(in)) break;
        }
        fprintf(out, "\n");
    }

    printf("*Image Data Copied From The File Successfully. :)\n");

    fclose(in);
    fclose(out);
    printf("*Image Files Are Closed...\n");

    return 0;
}
