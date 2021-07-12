# CPPND: Capstone Hello World Repo

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application starting with this repo, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./HelloWorld`.


1- download abd install QT for open source users. Note: project developed using Qt5.15.2. When selecting componets, include msvc compiler since it will be used by visual studio 2019. 
https://www.qt.io/download
watch video https://youtu.be/sEXOkBm_fuo
Require to sign up with valid email 

2- install Vs 2019 Community 
https://visualstudio.microsoft.com/vs/
have conguigrtion properties C++17 or above. 


3 - Configure Visual Studio 2019 to use QT 5.
Follow the instruction using the video below. 
Note: the part where Qt 5 is added to go to VS->Options->Versions...for the path not stop in msvc2019_64...
go to bin and qmake
https://youtu.be/6bXrfVrYyxk

4- add QT to System enviroment. Also add  C:\Qt\5.15.2\msvc2019_64\bin to the Path to avoid error such as The code execution can not proceed because qt5core.dll was not found. 


5 - install cmake 
cmake.org 


