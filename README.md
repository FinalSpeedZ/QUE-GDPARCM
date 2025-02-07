# QUE-GDPARCM

The solution would contain multiple projects of my GDPARCM journey

## Problem Set 1
### How to run:
1. Launch QUE-GDPARCM.sln
2. Navigate to the project **QUE-RaytracingInOneWeekend**
   -> Double check that the solution's startup project is either the Raytracing project or Current Selection
3. Entry file is main.cpp
4. Run the solution either in *Debug* or *Release* but Release has relatively faster render time by clicking the **Green Play Button** or **F5**
### Dependencies:
1. C/C++ -> General -> Additional Include Directories: Place the path to the include folder of OPENCV
2. Linker -> General -> Additional Library Directories: Place the path to the lib folder of OPENCV
3. Linker -> Input -> Additional Dependencies: opencv_world455d.lib | opencv_world455.lib
4. Place the .dll files of opencv under the x64/Debug and x64/Release folders

