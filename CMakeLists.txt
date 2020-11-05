cmake_minimum_required(VERSION 3.0)
project( quickTest )
find_package( OpenCV REQUIRED )

# Create a list with all .cpp source files
set( project_sources
   main.cpp
   treeGen.cpp
   landGen.cpp
)

add_executable( quickTest ${project_sources}) #main.cpp ${project_sources
target_link_libraries( quickTest ${OpenCV_LIBS} ) 
