/*
DEM_Generation/landGen.h
Author: Daniel Bowden BWDDAN001

Header file for the landGen class declaring all class variables and functions

*/

#ifndef LANDGEN_H_
#define LANDGEN_H_

namespace landGen{
   struct Point{
      int x;
      int y;
   };
   class landscape{
      private:
         int widthX;
         int widthY; 
      public:
         landscape();
         void drawLand(int landType);
   };
}
#endif