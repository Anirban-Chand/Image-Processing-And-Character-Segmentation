  #include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Insertion Sort Method has been used
void sort(int n, int arr[]) 
{
    int i, key, j; 
    for (i = 1; i < n; i++) 
    { 
        key = arr[i]; 
        j = i - 1; 
        while (j >= 0 && arr[j] > key) 
        { 
            arr[j + 1] = arr[j]; 
            j--; 
        } 
        arr[j + 1] = key; 
    } 
}


/* Driver Code */
int main(int argc, char* argv[]){
    
    /* in = input file
       out = output file */
    FILE *in=NULL, *out=NULL, *med=NULL;

    /* Height, Width and Maximum Pixel Value of the Image */
    int height,width,maxpix;

    /* Magic No of the Image and Str is for storing the strings read */
    char c,magicno[2],str[500];

    /* Total 3 files are gonna open for 3 operations */
    /* Opening Input File in Read Mode */
    in=fopen(argv[1],"r");

    /* Opening Output File in Write Mode */
    out=fopen(argv[2],"w");
    
    /* Opening file for filtration */
    med=fopen(argv[3],"w+");
    if((in!=NULL)&&(out!=NULL)&&(med!=NULL)){
        printf("Files Are Opened And Processing...\n");
    }
    else{
        printf("Files Opening Failed!!!\n");
    }

    /* Reads and Writes the Magic No of the Image */
    fgets(magicno, 3, in); // reads from input file
    fscanf(in,"\n"); // reads the newline character
    printf("Magic No - %s\n",magicno);
    fputs(magicno,out); // writes in output file
    fputs("\n",out); // writes the newline character
    fputs(magicno,med); // writes in output file
    fputs("\n",med); // writes the newline character
    

    fgets(str, 50, in); // reads the comment out line
    // printf("%s\n",str);
    

    /* Reads and Writes the Width and Height of the Image */
    fscanf(in, "%d %d", &width, &height); // reads
    fscanf(in,"\n"); // reads the newline character
    // printf("Width = %d\tHeight = %d\n", width,height);
    fprintf(out, "%d %d", width,height); // writes
    fprintf(out,"\n"); // writes the newline character
    fprintf(med, "%d %d", width,height); // writes
    fprintf(med,"\n"); // writes the newline character
    

    /* Reads and Writes the Maximum Pixel Value */
    fscanf(in, "%d", &maxpix);
    fprintf(out, "%d", maxpix);
    fprintf(med, "%d", maxpix);
    fscanf(in,"\n"); // reads the newline character
    fprintf(out,"\n"); // writes the newline character
    fprintf(med,"\n"); // writes the newline character


    printf("Image Details Read Successfully. :)\n");
    printf("Image Details Written Successfully. :)\n");


    /* 2-D Image Array to store Pixel Values */
    /* 'image' is the array of pointers,
        each of its part stores the base address 
        of the nested arrays that's why we should use double star(int **image) */
    int **image;
    int **cpyimg;
    
    image = (int**)malloc(height * sizeof(int*));
    cpyimg = (int**)malloc(width * sizeof(int*));
    if(image == NULL) printf("SORRY! Memory Allocation Failure!\n");
    if(cpyimg == NULL) printf("Memory Allocation Failed for Filtering!\n");
    else printf("Memory for the Image File Allocated.\n");

    
    /* Reads and Writes Every Pixel's Value */
    for(int i=0; i<height; i++){
        
        image[i] = (int*)malloc(width * sizeof(int));
        cpyimg[i] = (int*)malloc(height * sizeof(int));

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
    
    
    for(int i=1; i<height+1; i++){
        for(int j=1; j<width+1; j++){
            
            int window[]={image[i-1][j-1],image[i-1][j],image[i-1][j+1],image[i][j-1],image[i][j],image[i][j+1],image[i+1][j-1],image[i+1][j],image[i+1][j+1]};

            sort(9, window);    
            
            cpyimg[i][j]=window[4];
            fprintf(med, "%d ", cpyimg[i][j]);
        }
        fprintf(med, "\n");
    }

    printf("*Image denoised Successfully. :)\n");
    fclose(in);
    fclose(out);
    fclose(med);
    printf("Files have been closed\n");
}
