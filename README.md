# Image-Processing-And-Character-Segmentation

## Notes To Remember:
* **PGM** - Portable Graymap

* **PBM** - Portable Bitmap

* **Magic Number** - Magic numbers are the first few bytes of a file that are unique to a particular file type. These unique bits are referred to as magic numbers,  also sometimes referred to as a  file signature.
These bytes can be used by the system to “differentiate between and recognize different files” without a file extension.

* **Different Magic Numbers**:

| Magic Number   | File Type        | Extension | Type   |
|:--------------:|------------------|-----------|--------|
|    P1          | Portable Bitmap  | PBM       | ASCII  |
|    P2          | Portable Graymap | PGM       | ASCII  |
|    P3          | Portable Pixmap  | PPM       | ASCII  |
|    P4          | Portable Bitmap  | PBM       | Binary |
|    P5          | Portable Graymap | PGM       | Binary |
|    P6          | Portable Pixmap  | PPM       | Binary |

* Only P1, P2 magic numbers are used

* **Noise Reduction**::	(For noise reduction we use structuring element/kernel/window of different sizes.)
	- 1. Average/Mean Filter
	- 2. Median Filter
		
* **Mean Filter** -	Superimpose the kernel on the image. Value at the center of the kernel is avg of the kernel.
	- Example: for 3x3 kernel - image[i][j] =(kernel[i-1][j-1]+kernel[i-1][j]+kernel[i-1][j+1]+kernel[i][j-1]+kernel[i][j]+kernel[i][j+1]+kernel[i+1][j-1]+kernel[i+1][j]+kernel[i+1][j+1])/9
				
* **Median Filter** -	Superimpose the kernel on the image. Value at center of kernel is median of the kernel. We sort kernel elements & take median of them.
	- Example: image[i][j] = median(kernel[i-1][j-1], kernel[i-1][j], kernel[i-1][j+1], kernel[i][j-1], kernel[i][j], kernel[i][j+1], kernel[i+1][j-1], kernel[i+1][j], kernel[i+1][j+1])
				
				
* **Binarization** - Process of converting a multi-tone image into a two-tone image. Compute the threshold value of the multi-tone image using Otsu's Thresholding Algorithm. If value of a particular pixel is less than the threshold then we make it background(value = 1) and otherwise make that pixel foreground(value = 0).

* **Otsu's Algorithm::**
	- step-1: Histogram of the image
	- step-2: Compute Between-Class Variance
	- step-3: Find the Threshold value

* **Threshold Value**  -	Pixel value for which b/w class variance is maximum.

* **Connected Components** - 2 pixels are said to be connected if their pixel values are same and they are N4 or N8 neighbor of each other.

* **Morphological Operations** - Morphological operations are mathematical operations applied on binary images for analysis and processing. 
	- Basic Types - 
		- Dilation
		- Erosion
	- Composed Types - 
		- Opening = erosion -> dilation
		- Closing = dilation -> erosion

* **Line Detection** - Detect where each line starts and ends.

* **Horizontal Projection Profile** - Sum of all pixels within a row.
