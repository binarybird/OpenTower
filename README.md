OpenTower
=========
    
Modified July 6, 2014    
    
	
Tower construction and maintenance simulator!    
    
A simple clone of SimTower - a tower construction and simulation game.    
    
There was a project to reboot this game, but it looks like it went nowhere; it seemed too ambitious, with 3d modelling and all.    
This project will be a faithful 2D clone of the original game (with some modern enhancements of course).   
     
The core of the game will be using the Cocos-2DX C++ engine. This will enable the game to be platform agnostic and with some work, mobile device compatible.    
    
If youd like to contribute, just ping me!    
    
---------------------------------------------------------------    
Building:    
    
1) Download cocos2d-x-2.2.4 http://www.cocos2d-x.org/download    
2) Unzip    
3) Checkout OpenTower    
4) Put OpenTower in cocos2d-x-2.2.4/projects folder (you may have to create it)    
5) Open in your favourite IDE and enjoy    
    
---------------------------------------------------------------     
Notes for eclipse and Linux (WIP):     
     
Almost 100% based off of this very helpful article http://borjarefoyo.com/2013/07/02/setup-cocos2dx-environment-in-linux-for-android/    
These are not my exact notes for getting eclipse to play with cocos2dx on Linux, but close, ping me if you have issues! I've left my .project and .cproject in the proj.linux folder for future use.    
    
1) Import -> General-> Existing Projects into Workspace    
2) Select the cocos2d-x-2.2.4 folder and recursivley search for projects.     
3) Include the proj.linux projects for libBox2D, libChipmunk, libcocos2d, libCocosDenshion, libextension, liblua, and ofcourse OpenTower.    
4) Open libextension -> network -> delete the WebSocketWinRT.cpp/h class    
5) Open libextension -> GUI -> CCEditBox -> delete the CCEditBoxImplWinrt.cpp/h and CCEditBoxImplWp8.cpp/h classes    
6) You need to make and install libwebsockets (http://git.warmcat.com/cgi-bin/cgit/libwebsockets/snapshot/libwebsockets-1.22-chrome26-firefox18.tar.gz) (requires libtool and autoconf) See here for detailed instructions http://borjarefoyo.com/2013/07/06/install-libwebsockets-library-in-linux/    
7) You need to delete the includes and libs for libxml2, they are no longer included with cocos2d. Right click on libcocos2d -> Properties -> C/C++ Build -> Settings -> GCC C++ Compiler -> Includes -> Delete  ../../../cocos2dx/platform/third_party/linux/libxml2    
8) Again, delete the linked lib for libxml2  GCC C++ Linker -> Libraries -> Delete  ../../../cocos2dx/platform/third_party/linux/libraries/lib64    
9) For libCocoDension delete linux -> SinpleAudioEngineFMOD    
10) Quit eclipse, navigate to OpenTower/proj.linux/.project add this under ``` <linkedResources>```: 		
```
		<link>    
			<name>ccFPSImages.c</name>    
			<type>1</type>    
			<locationURI>PARENT-3-PROJECT_LOC/cocos2dx/ccFPSImages.c</locationURI>    
		</link>    
		<link>    
			<name>ccFPSImages.h</name>    
			<type>1</type>    
			<locationURI>PARENT-3-PROJECT_LOC/cocos2dx/ccFPSImages.h</locationURI>    
		</link>    
```
11) My PARENT-3-PROJECT_LOC from the above points to the cocos2d-x-2.2.4 folder, yours may not, so just open up eclipse, look in OpenTower -> ccFPSImages.c and ccFPSImages.h should exist, if not, just right click -> Properties and edit the resource location    
12) In my case, im on a Ubuntu 14 64 bit, so I needed to adjust the includes and libs (from x86 to 64) for every project in eclipse. Right click on each lib -> Properties -> C/C++ Build -> Settings. Under GCC C++ Compiler, GCC C Compiler make sure your includes are good. Under GCC C++ Linker, make sure the libs your linking against are for your architecture.    
    
---------------------------------------------------------------     
    
Notes for casual users: You can run and build what I have here, but a stable "normal" program for release is still in the works!    

