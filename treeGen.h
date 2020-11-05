/*
DEM_Generation/treeGen.h
Author: Daniel Bowden BWDDAN001

Header file for the treeGen class declaring all class variables and functions

*/

#ifndef TREEGEN_H_
#define TREEGEN_H_
#include <list>
#include <vector>

#include "opencv2/core.hpp"

namespace treeGen{
   struct Pos{
      int x;
      int y;
   };
   class Tree{
      private:
         float minHeight,maxHeight;
         int width;         

      public:
         int** heightGrid;
         Tree();
         Tree(float min,float max, int w, int treeType);
         void drawTree();
         void drawNeatTree();
         bool insideCircle(Pos center, Pos tile, float radius);
         void drawCircularTree(int choice);
         void drawRadialTree();
         int getWidth();
   };

   class TreeGroup{
      
      public:
         TreeGroup();
         void createTreesGrid(int treeWidth, int gapX,int gapY,int gridWidthY,int gridWidthX);  //sets treePositions based on available space, tree width and gap between trees        
         void createTreesLinear(int treeWidth,int gap,int gridWidthY,int gridWidthX); 
         void createTreesContour(int treeWidth,int gap,int gridWidthY,int gridWidthX , std::vector<std::vector<cv::Point>> contours); //sets treePositions on contour lines based on available space, tree width and gap between trees        
         void setAvailable(int** grid, int gridWidthY, int gridWidthX); //sets spawnGrids available spawns

         Pos* treePositions; 
         int treeCnt;
      private:
         int** spawnGrid;

   };
}
#endif