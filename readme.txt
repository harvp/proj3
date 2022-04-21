Harvey Petersen hrp3@uakron.edu
Algorithms Spring 2022
Project 3

Welcome to carver. Carver uses seam carving to remove seams of pixels from pgm image files. Multiple seams can be removed at once, and vertical and horizontal seams can both be removed.

INPUT

The files used must be pgm image files. As such, the must begin with a literal value of P2, and should specify several values. First, one one line, include the number of columns and the number of rows in the starting file. Then, on the next line, specify the maximum value of pixel intensity in the file. Comments in the file should have a # at the beginning of the line.

SYNTAX

When running carver, the command must be in this format: 

carver.exe FILENAME.pgm VERTICAL HORIZONTAL 

where FILENAME is the name of your file, VERTICAL is a numeric value for the number of vertical seams that will be removed, and HORIZONTAL is a numeric value for the number of horizontal seams that will be removed. The filename is CASE SENSITIVE- if you input an incorrect name, carver will not run. 

If your file is stars.pgm and you want to remove 20 vertical seams and 10 horizontal seams, the correct syntax is:

carver.exe stars.pgm 20 10


OUTPUT

After all seams are removed, the program will output a pgm file in the format FILENAME_processed.pgm

