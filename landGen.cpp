/*
DEM_Generation/landGen.cpp
Author: Daniel Bowden BWDDAN001

landGen contains the functionality to draw the underlying landscapes that we will be spawning tree on later
landscapes are drawn by creating a Mat Image and adjusting every pixel value in a different way to create a landscape DEM
*/

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "landGen.h"

using namespace cv;
using namespace std;

namespace landGen{
	/*
	Pos struct for x y positions
	*/
	struct Pos{
		int x;
		int y;
	}; 
	/*
	landscape default constructor
	*/
	landscape::landscape(){
		widthX = 500;
		widthY = 500;
	}
	/*
	drawLand void function, drawing a landscape based on landType chosen
	*/
	void landscape::drawLand(int landType){
		//temporary variables to store height change values
		float increase;
		float increase2;
		float decrease;
		float temp;
		float temp2;
		bool upwards;
		Mat image(widthX, widthY, CV_32F);
		switch(landType){
			case 1: //steep linear gradient map
				increase = 0.2f;
				temp = 50;
				for(int i = 0 ; i < 500 ; i++){
					temp += increase;
					for(int j = 0 ; j < 500 ; j++){
						// randStep used for most maps to create bumpy ground texture of slightly varying height values even when flat
						int randStep = rand() % 3 - 3; 
						image.at<float>(i,j) = temp + randStep;
					}
				}
				break;

			case 2: //gentle linear gradient map
				increase = 0.03f;
				temp = 50;
				for(int i = 0 ; i < 500 ; i++){
					temp += increase;
					for(int j = 0 ; j < 500 ; j++){
						int randStep = rand() % 3 - 3;
						image.at<float>(i,j) = temp + randStep;
					}
				}
				break;

			case 3: //jaggedHills (not used, too artifical)
				increase = 0.5f;
				decrease = 0.5f;
				upwards = true;
				temp = 50;
				for(int i = 0 ; i < 500 ; i++){
					if(upwards){
						temp += increase;
						if(temp > 55){
							upwards = false;
						}
					}
					else{
						temp -= decrease;
						if(temp< 45){
							upwards = true;
						}
					}					
					for(int j = 0 ; j < 500 ; j++){
						int randStep = rand() % 3 - 3;
						image.at<float>(i,j) = temp + randStep;
					}
				}
				break;

			case 4: //wavy map, landscape similar to sin wave when viewed from side
				increase = 0.05;
				temp = 0;
				for(int i = 0 ; i < 500 ; i++){
					temp = 0;
					for(int j = 0 ; j < 500 ; j++){
						temp += increase;
						int randStep = rand() % 3 - 3;
						image.at<float>(i,j) = sin(temp)*10 + randStep;
					}
				}
				break;

			case 5: //hills map, creates pattern of ditches and hills
				increase = 0.05;
				temp = 0;
				temp2 = 0;

				for(int i = 0 ; i < 500 ; i++){
					temp = 0;
					temp2 += increase;
					for(int j = 0 ; j < 500 ; j++){
						temp += increase;
						int randStep = rand() % 3 - 3;
						image.at<float>(i,j) = sin(temp) * sin(temp2)*5 + randStep;
					}
				}
				break;

			case 6: //Hill contours, creates simple sloping hill with more realistic curved shape than linear gradient maps
					//to be used for contour tree growing
				increase = 0.005;
				increase2 = 0.01f;
				temp = 0;
				temp2 = 0;

				for(int i = 0 ; i < 500 ; i++){
					temp = 0;
					temp2 += increase2;
					for(int j = 0 ; j < 500 ; j++){
						temp += increase;
						int randStep = rand() % 3 - 3;
						image.at<float>(i,j) = sin(temp) *20 * temp2 + randStep; 
					}
				}
				break;

			case 7: //flat zero ground
				for(int i = 0 ; i < 500 ; i++){
					for(int j = 0 ; j < 500 ; j++){
						image.at<float>(i,j) = 0;
					}
				}
				break;

			case 8: //flat bumpy ground, default flat ground map
				for(int i = 0 ; i < 500 ; i++){
					for(int j = 0 ; j < 500 ; j++){
						int randStep = rand() % 3 - 3;
						image.at<float>(i,j) = 0 + randStep;
					}
				}
				break;
			case 9: //contouHillJoin map, creates two overlapping hills similar to case 6
					// to be used for contour tree growing
				increase = 0.005;
				increase2 = 0.01f;
				temp = 0;
				temp2 = 0;

				for(int i = 0 ; i < 500 ; i++){
					temp = 0;
					temp2 += increase2;
					for(int j = 0 ; j < 500 ; j++){
						temp += increase;
						int randStep = rand() % 3 - 3;
						image.at<float>(i,j) = max(sin(temp+50) *20 * temp2 + randStep, cos(temp+50) *20 * temp2 + randStep); 
					}
				}
				break;

			case 10: // hills map, creates pattern of ditches and hills but without bumpy ground texture
				increase = 0.05;
				temp = 0;
				temp2 = 0;

				for(int i = 0 ; i < 500 ; i++){
					temp = 0;
					temp2 += increase;
					for(int j = 0 ; j < 500 ; j++){
						temp += increase;
						image.at<float>(i,j) = sin(temp) * sin(temp2)*5; 
					}
				}
				break;
		}		
		//write the resultant landscape DEM to file
		imwrite("output/landscape.tif",image);
	}
}
