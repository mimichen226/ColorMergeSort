Project: Visual Simulation of Merge Sort Using Colors
======================
Visual simulation of merge sort (sorting colors)

Mimi Chen

Due December 15, 2016


Introduction
------------
This visual simulation uses some of the key CS concepts covered in Fund Comp 
- Recursion 
- GFX animations/ displays
- Data structures 

		Nested vectors
		Classes 
		~ Color (holds the rgb values and the hue calculated from the rgb values)
		~ DispBoard (the board that is displayed to the GFX window is a vector of vector
			 of vector of the class Colors)
- Inheritance



User Perspective
------------------
At the top left of the GFX window, the time complexity of merge sort is displayed. At the top center of the GFX window, the number of colors to be sorted using merge sort is displayed.

By default, the number of colors to be sorted is 5 (n = 5). In the top row, the program displays one list of n unsorted colors in the GFX window. Lists of colors are separated by white bars in a row. In the first step of simulating merge sort, the list of n unsorted colors are divided into two lists (ie. if n = 5, one list has two colors, and the second list has three colors) and displayed in a row right below the top row (depth increased by 1). The two lists are separated by a white bar. The lists of colors are continued to be divided until there is only 1 color in a list (there is a white bar in between each color). When the lists can no longer be divided, the row of lists of singular colors is at the very bottom of the GFX window.

The second step of merge sort is merging back the lists so that the elements are in order. The colors in adjacent lists are compared based upon their hues (0-360). A color with a smaller hue value is placed first in a merged list. The sorted list of colors is displayed in the row above (ie. with the first merge, the merged colors will be above the row with lists of single values) so that it replaces the above row's colors. Then above that row, it is the merged list of colors of lists that were just merged). 

Upon completion of merge sort, the program displays the message "Done!" in the top right corner. The user then can select the number of colors to be sorted using the keyboard inputs. 

		---------------------------------------------
		| Keyboard Input | # of colors to be sorted |
		---------------------------------------------
		| 		2 		 | 		  2					|
		| 		3 		 | 		  3					|
		| 		4 		 | 		  4					|
		| 		5 		 | 		  5					|
		| 		6 		 | 		  6					|
		| 		7 		 |		  7					|
		| 		8 		 |		  8					|
		| 		9   	 | 		  9					|
		---------------------------------------------
		|       q 		 | 		Exits program  		|
		---------------------------------------------

Programmer Perspective
------------------
The program uses two different classes: 
- Color
- DispBoard

Color
---------
The class Color holds the private data r value, g value, b value, and the hue corresponding to the rgb values. The constructor of Color takes three values (r value, g value, b value of a color). The hue is then calculated by calling the method "gethue". The hue is calculated by finding the most intense rgb value (equations found online at http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/). The class Color has the access methods "setrgb" (set the rgb values), "getr" (get the r value), "getg", "getb". The class Color has the utility methods "getmaxrgb" (returns the maximum rgb value), "getminrgb" (returns the minimum rgb value), and "print" (prints the rgb values to the terminal output window). 


DispBoard
-------------
The class DispBoard's private data is a vector of a vector of a vector of Color. The outer most vector corresponds to the row/ depth value. Depth 0 is at the the first row displayed at the top of the screen. The second vector corresponds to the list/ column number. The first row has one list so the second vector has only one element. The second row has two lists, so there are two elements. Each element of the second vector is a vector of Color to represent the list of colors being sorted. 

The constructor of DispBoard takes two values (the depth or number of rows, and the number of elements to be sorted). The outer forloop loops over the number of rows, then the second forloop loops over the number of columns (calculated by taking 2^(row number)) where an empty vector of Color is appended with each iteration. The class has the access methods "setdepthcount", "getsize", and "getdepth". The utility method "print" was used to ensure that the correct colors were in each vecttor. The utility method "gfx_print" displays to the GFX window the formatted vector of vector of vector of Color. 

 final.cpp 
-------------
The program final.cpp has four functions:
- main 
- mergesort
- merge
- randomint

** MAIN **

CREATION OF LIST TO BE SORTED
In the main function, there is a color database (vector of Color) that holds 10 different colors. The unsorted colors that are chosen to be sorted are randomly chosen from the color database. While the input from the user is not 'q', the while loop will continue to execute. Inside the while loop, the color database is shuffled, and based upon the number of colors that are to be in the original unsorted list, that number of colors is pulled from the database and appended to the list of colors to be sorted. 

DETERMINE DEPTH NEEDED TO SORT COLORS
To determine the depth needed to sort colors, the number of colors to be sorted is compared to 2^(depth - 1). Depth is incremented by 1 while the number of colors to be sorted is less than 2^(depth - 1). Now that the depth is determined, an object of the class DispBoard is created. The depth that you are in and the number of times you have been in a depth is kept track of using a vector of integers called "count". The index of "count" corresponds to the depth, and its value is the number of times the depth is called. 

PERFORM MERGE SORT
Main calls the function "mergesort". 

WAITS FOR INPUT FROM USER
With gfx_wait, the program waits for inputs from user before continuing. 


** MERGESORT **
"Mergesort" divides the vector of colors into a two halves then recursively calls "mergesort" on the new half vectors ("mergesort" calls two "mergesort"). After the base case of when the vector of colors to be sorted is 1, it returns and calls the function "merge" to merge the halves together. "Mergesort" takes in the input a vector of colors to be sorted, the depth, and vector of counts (index = depth, value = times in depth). 

** MERGE **
"Merge" returns a sorted vector given two sorted vectors. To determine which element to select first from the sorted vectors, "merge" compares the hue of the first element's in the two vectors passed in.  

** RANDOMINT **
Generates a random integer



Program Validation
------------------
The program was validated by testing the mergesort with different number of colors to be sorted. At first, only a list with even number of colors could be probably displayed because the odd number colors would have a trailing color at the end. After realizing this, I wrote in my display.cpp file to adjust the xposition of the color displayed for the bottom row when only some vectors have the additional row. 
