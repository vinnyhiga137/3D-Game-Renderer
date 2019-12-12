# 3D Game Renderer
My simple OpenGL Renderer for games made with OpenGL 3

# Project Status

Windows 10 (x64):

![alt text](https://ci.appveyor.com/api/projects/status/32r7s2skrgm9ubva?svg=true)

Mac OS Catalina (x64):

![alt text](https://ci.appveyor.com/api/projects/status/32r7s2skrgm9ubva?svg=true)

# About the Project

This project has the idea to try to build a simple OpenGL Game with following features:

* Support common images formats (like JPEG and PNG with Alpha).
* Render 2D / 3D Graphics with shaders.
* Support to Phong Material type.
* Support to simple FPS style input.

# How to build

On Windows 10 (x64):

* You must have visual studio 2019 (or equivalent) installed with C++.

* You must have installed the Windows SDK at least from the Major 16 Version (The Major is the Prefix).

On Mac OS Catalina (x64):

* You must have the lastest XCode installed for the supported Mac OS and be careful for the deprecation WARNING from Apple due the substitute API that is there (Metal API).

* You must change the development team to yours and if there's some import errors you must put on the linker the libraries that are on the "3rd_party" folder.
