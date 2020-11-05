author: Daniel Bowden BWDDAN001

DEM_Generation Layer

Requires openCV 4 to run: 
https://opencv.org/
https://www.learnopencv.com/install-opencv-4-on-ubuntu-18-04/

-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
To Build: 
while in DEM_Generation/build directory:
	make
	
To run:
while in DEM_Generation directory:
	./build/quickTest

-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Description of input choices:

Specify landscape [1...10]: 
	Pick any landscape 1 to 10
Specify tree type number [2...5]: 
	specify a desired tree type
	2: Simple case medium sized tree with diamter of 30 pixels
	3: Simple case small sized tree with diameter of 15 pixels
	4: Complex case medium sized tree with diameter of 30 pixels
	5: Complex case small sized tree with diameter of 15 pixels
Overlap trees? [y/n]: 
	specify whether trees should overlap or be spread
Normalize image? [y/n] 
	choose n when using a generated landscape
Convert to 8bit? [y/n] 
	choose y when using a generated landscape
Draw trees based on contour lines? [y/n] 
	specify whether to based tree growth on contour lines or not

-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
EXAMPLE INPUT:

Specify landscape [1...10]: 
6
Specify tree type number [2...5]: 
4
Overlap trees? [y/n]: 
y
Normalize image? [y/n] 
n
Convert to 8bit? [y/n] 
y
Draw trees based on contour lines? [y/n] 
y

-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
