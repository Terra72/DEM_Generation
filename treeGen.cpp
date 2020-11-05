/*
DEM_Generation/treeGen.cpp
Author: Daniel Bowden BWDDAN001

treeGen contains the functionality to generate tree positions for groups of trees based on given contour lines
or based on rows in a grid structure

Additionally contains the functionality to generate heights for a group of pixels to represent a tree canopy

*/

#include <iostream>
#include <stdlib.h>
#include <list>
#include <time.h>  
#include <vector>
#include <cmath>

#include "treeGen.h"

using namespace std;
namespace treeGen{
    /*
    tree default constructor
    */
    Tree::Tree(){
        minHeight = 5;
        maxHeight = 10;        
        width = 4;
        drawTree();   
    }

    /*
    tree overloaded constructor
    */
    Tree::Tree(float min,float max, int w, int treeType){
        minHeight = min;
        maxHeight = max;
        width = w;
        drawCircularTree(treeType);
    }

    /*
    drawTree void function, Experimental and not used in final! draws a bumpy flat square canopy tree
    */
    void Tree::drawTree(){ //allocates on the heap, beware!
        int heightMulti =   rand() % 3 + 1;
        float randHeight;
        heightGrid = new int*[width];
        for (int i = 0; i < width ; i++){
            heightGrid[i] = new int[width];
            for (int j = 0; j < width ; j++){
                float randHeight = minHeight + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxHeight-minHeight)));
                heightGrid[i][j] = randHeight * heightMulti;
            }
        }
    }
    
    /*
    drawNeatTree void function, Experimental and not used in final! draws a square canopy tree with a gradient of heights
    */
     void Tree::drawNeatTree(){ 
        int heightMulti = 1;
        float randHeight;
        heightGrid = new int*[width];
        for (int i = 0; i < width ; i++){
            heightGrid[i] = new int[width];
            for (int j = 0; j < width ; j++){
                float treeHeight = ((width/2 - abs(width/2 - i)) +(width/2 - abs(width/2 - j)))/2;
                heightGrid[i][j] = treeHeight * heightMulti + minHeight;
            }
        }
    }

    /*
    insideCircle return function returning true for a point inside a circle of a given radius
    */
    bool Tree::insideCircle(Pos center, Pos tile, float radius) {
        float dx = center.x - tile.x;
        float dy = center.y - tile.y;
        float distance_squared = dx*dx + dy*dy;
        return distance_squared <= radius*radius;
    }

    /*
    drawCircularTree void function, writing the values for a tree to the heightgrid for all trees
    heightgrid contains the heights for every pixel in every trees canopy
    */
    void Tree::drawCircularTree(int choice){
        int radius = width/2;
        Pos center = {width/2,width/2};
        //create a new 2D array for a tree canopy grid
        heightGrid = new int*[width];
        for (int i = 0; i < width ; i++){
            heightGrid[i] = new int[width];
            for (int j = 0; j < width ; j++){
                Pos tempPos = {i,j};    
                heightGrid[i][j] = 0;   
                //check if the pixel (i,j) is inside the radius of the tree         
                if(insideCircle(center, tempPos, radius)){
                    float treeHeight;
                    switch(choice){
                        //various different tree types can be drawn based on choice
                        case 1: // pyrimid like canopy
                            treeHeight = ((radius - abs(radius - i)) +(radius - abs(radius - j)))/2;
                            heightGrid[i][j] =  treeHeight + minHeight ; 
                            break;
                        case 2: //Simple tree canopy for width of 30
                            {
                                int diffY = abs(width/2 - j);
                                int diffX = abs(width/2 - i);
                                int dist = sqrt(diffY * diffY + diffX * diffX);
                                int tempDist = max(1,dist);
                                treeHeight = pow(abs((width/2)-tempDist), (float)width/100)*width/4;
                                heightGrid[i][j] =  treeHeight + minHeight ; 
                            }
                            break;

                        case 3: //Simple tree canopy for width of 15
                            {
                                int diffY = abs(width/2 - j);
                                int diffX = abs(width/2 - i);
                                int dist = sqrt(diffY * diffY + diffX * diffX);
                                int tempDist = max(1,dist);
                                treeHeight = abs((width/2)-tempDist);
                                heightGrid[i][j] =  treeHeight + minHeight ; 
                            }
                            break;

                        case 4: //Complex tree canopy for width of 30, random variations on the height and edges
                            {
                                int canopyVariance = rand() % 2 - 2;                                
                                int diffY = abs(width/2 - j);
                                int diffX = abs(width/2 - i);
                                int dist = sqrt(diffY * diffY + diffX * diffX);
                                int tempDist = max(1,dist);
                                treeHeight = pow(abs((width/2)-tempDist), (float)width/100)*width/4;
                                int canopyHoleChance = rand() % tempDist;        
                                if(canopyHoleChance > width/4){
                                    heightGrid[i][j] =  0; 
                                } 
                                else{
                                    heightGrid[i][j] =  treeHeight + minHeight + canopyVariance ; 
                                }
                            }
                            break;
                        case 5: //Complex tree canopy for width of 15, random variations on the height and edges
                            {
                                int canopyVariance = rand() % 2 - 2; 
                                int diffY = abs(width/2 - j);
                                int diffX = abs(width/2 - i);
                                int dist = sqrt(diffY * diffY + diffX * diffX);
                                int tempDist = max(1,dist);
                                treeHeight = abs((width/2)-tempDist);
                                int canopyHoleChance = rand() % tempDist;      
                                if(canopyHoleChance > width/4){
                                    heightGrid[i][j] =  0; 
                                } 
                                else{
                                    heightGrid[i][j] =  treeHeight + minHeight + canopyVariance ; 
                                }
                            }
                            break;
                    }                    
                }
            }
        }
    }

    /*
    drawRadialTree void function, Experimental and not used in final! attempt at drawing a tree radially instead of from min to max of grid
    */
    void Tree::drawRadialTree(){
        int radius = width/2;
        Pos center = {width/2,width/2};
        heightGrid = new int*[width];
        for (int i = 0; i < width ; i++){
            heightGrid[i] = new int[width];
            for (int j = 0; j < width ; j++){  
                heightGrid[i][j] = 0;  
            }
        }         
        for (int i = -radius; i < radius ; i++){
            for (int j = -radius; j < radius ; j++){
                if(i*i + j*j <= radius*radius){
                    int diffY = abs(width/2 - (j + center.y));
                    int diffX = abs(width/2 - (i + center.x));
                    int dist = sqrt(diffY * diffY + diffX * diffX);
                    int tempDist = max(1,dist);
                    float treeHeight = pow(abs((radius)-tempDist), (float)width/100)*width/4;
                    heightGrid[center.x + i][center.y + j] =  treeHeight + minHeight ; 
                }                
            }
        }              
    }
    
    /*
    getWidth return function returning integer width
    */
    int Tree::getWidth(){
        return width;
    }
    /*
    TreeGroup constructor function
    */
    TreeGroup::TreeGroup(){
        cout << "New group of trees!" << endl;
        treeCnt = 0;
    }

    /*
    setAvailable void function
    initializes the available raster grid area that can spawn trees, 
    0 for can't spawn, 1 for can
    */
    void TreeGroup::setAvailable(int** inputGrid, int gridWidthY, int gridWidthX){
        spawnGrid = new int*[gridWidthX]; 
        for (int i = 0; i < gridWidthX ; i++){
             spawnGrid[i] = new int[gridWidthY];
            for (int j = 0; j < gridWidthY ; j++){
                spawnGrid[i][j] = inputGrid[i][j];
            }
        }
    }
    //sets treePositions based on available space and tree width and gap between trees
    void TreeGroup::createTreesGrid(int treeWidth, int gapX,int gapY,int gridWidthY ,int gridWidthX){     
        int yDist = gapY; 
        int xDist = gapX;
        list<Pos> tempPosList;
        //start at first spawnable tree pos, spawn a tree if possible then reset Dist values loop to next space
        for (int i = gapX + treeWidth; i < gridWidthX ; i++){
            int randDistX = rand() % treeWidth/4 - treeWidth/4;
            xDist++;
            for (int j = gapY + treeWidth; j < gridWidthY ; j++){
                int randDistY = rand()  % treeWidth/4 - treeWidth/4;
                yDist++;
                //if the Dist is too small :can't spawn tree
                if(yDist >= gapY && xDist>= gapX){
                    //reset yDist once a tree has spawned
                    yDist = 0;
                    Pos tempPoint;
                    tempPoint.x = i+ randDistX; 
                    tempPoint.y = j+ randDistY ; 
                    if (tempPoint.x < gridWidthX && tempPoint.y <gridWidthY){
                        //if the position is available then set the position of the tree with a slight jitter
                        if(spawnGrid[tempPoint.x][tempPoint.y] == 1){
                            int randDropVal = rand()  % 10;
                            //chance to not spawn a tree
                            if(randDropVal != 1){
                                tempPosList.push_back(tempPoint);
                            }                            
                        }                        
                    }                  
                }
            } 
            //reset xDist once a row has spawned           
            if(xDist>= gapX){
                xDist = 0;
            } 
        }
        //add the temporary list to the treePositions global data structure
        treePositions = new Pos[tempPosList.size()];
        int k = 0;
        for (Pos const &i: tempPosList ){
            treePositions[k++] = i;
            treeCnt++;
        }
    }

    /*
    createTreesLinear void function, Experimental and not used in final! Sets treePositions for a single row based on linear function
    */
    void TreeGroup::createTreesLinear(int treeWidth,int gap,int gridWidthY ,int gridWidthX){  
        //y = mx + c   
        int gradient = rand() % 5 + 1;
        cout << "gradient " << gradient << endl;
        //int gradient = 2;
        list<Pos> tempPosList;

        int xGap = gap/gradient;
        //for each (x + treewidth) create a point using y=mx+c
        for (int c = -gridWidthY; c < gridWidthY; c+= 100){
            int  i = 0;     
            while (i + treeWidth/4 < gridWidthX  && (i*gradient + c + treeWidth/4) < gridWidthY){
                int randDistX = rand() % treeWidth/4 - treeWidth/4;
                int randDistY = rand() % treeWidth/4 - treeWidth/4;
                if (i - treeWidth/4 >= 0 && (i*gradient + c - treeWidth/4) > 0){
                    Pos tempPoint;
                    tempPoint.x = i + randDistX;
                    tempPoint.y = i*gradient + c+ randDistY;
                    if(spawnGrid[tempPoint.x][tempPoint.y] == 1){
                        tempPosList.push_back(tempPoint);                                      
                    } 
                } 
                i+= xGap;                                          
            }
        }
        //add the temporary list to the treePositions global data structure
        treePositions = new Pos[tempPosList.size()];
        int k = 0;
        for (Pos const &i: tempPosList ){
            treePositions[k++] = i;
            treeCnt++;
        }
    }

    /*
    createTreesContour void function creating tree positions and adding them to the treePositions data structure
    sets treePositions on contour lines based on available space, tree width and gap between trees
    */
    void TreeGroup::createTreesContour(int treeWidth,int gap,int gridWidthY ,int gridWidthX,std::vector<std::vector<cv::Point>> contours){  
        //create the available area grid 
        int** farmArea;
        farmArea = new int *[gridWidthX];
        for(int i = 0; i< gridWidthX; i++){
            farmArea[i] = new int [gridWidthY];
            for(int j = 0; j< gridWidthY; j++){
                farmArea[i][j] = 1;
            }
        }
        setAvailable(farmArea, gridWidthY,gridWidthX);
        int spawnX = 125;
        int spawnY = 125;
        list<Pos> tempPosList;
        //foreach contour line vector grouping try to set a tree position
        for(int i = 0; i< contours.size(); i++){
            for(int j = 0; j< contours[i].size(); j++){               
                Pos tempPoint;
                tempPoint.x = contours[i][j].x;
                tempPoint.y = contours[i][j].y;
                //check if the pos is available, if it is make the surrounding pixels unavailable and add it as a tree pos
                if(tempPoint.x > 125 && tempPoint.y > 125 && tempPoint.x < 375 && tempPoint.y < 375){ // constrain to our test region area 
                    if(spawnGrid[tempPoint.x][tempPoint.y] == 1){
                        tempPosList.push_back(tempPoint);   
                        for (int i = tempPoint.x - gap; i < tempPoint.x + gap; i++){
                            for (int j = tempPoint.y - gap; j < tempPoint.y + gap; j++){
                                if(i < gridWidthX && j < gridWidthY && i > 0 && j > 0){
                                    spawnGrid[i][j] = 0;
                                }
                            }
                        }                
                    }    
                }                         
            }
	    }
        //add the temporary list to the treePositions global data structure
        treePositions = new Pos[tempPosList.size()];
        int k = 0;
        for (Pos const &i: tempPosList ){
            treePositions[k++] = i;
            treeCnt++;
        }
    }
}