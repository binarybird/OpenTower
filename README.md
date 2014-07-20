OpenTower
=========
    
Modified July 20, 2014    
    
	
Tower construction and maintenance simulator!    
    
A simple clone of SimTower - a tower construction and simulation game.    
    
---------------------------------------------------------------        
What makes this project special?    
    
The OpenTower structure/sim logic is abstracted and COMPLETELY separate from the GUI and rendering logic. You can implement a SimTower clone using any gaming engine you want (this also makes the OpenTower runnable on pretty much anything). You could even make an ascii version for a command line SimTower clone!    
    
Multiplayer support! Thats right, build towers with your friends!
    
For my purposes, I used the cocos2d-x C++ engine for rendering junk.   
         
The platforms I am currently putting my efforts in to are Mac and Windows (linux should be easy though).
    
If youd like to contribute, just ping me!  
    
---------------------------------------------------------------    
Shoutouts:

Thanks to AzemOcram https://github.com/AzemOcram/OcramTower for ALL the sprite/image assets - its a huge help    
Thanks to Celsius http://www.celsiusgs.com/blog/2012/12/a-simple-data-serialization-system-for-c/ for the serialization code    
Thanks to Boost http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio.html for the asio networking libs!    
     
---------------------------------------------------------------     
Building:    
    
1) Checkout OpenTower     
2) Open proj.* in your favourite IDE and enjoy    
    
NOTE for VisualStudio:    
If, when you run the game, and all text is crammed in the middle, with no buttons:    
Open the .sln file Right click on the OpenTower project. Under Configuration Properties -> Debugging -> Make sure the "Working Directory" is $(ProjectDir)..\Resources    
    
If you have 3rd party lib issues, look in the cocos2d/external folder, make sure your platform and arch have the proper libs. If youre on linux, be sure to install the required dependencies - run the python script in cocos2d/download-deps,py    
    
---------------------------------------------------------------     
Progress:    

Theres a menu, you can open a new tower, you can save the tower (opening old towers almost implemented)    
In game - you can build an office, but thats it for now :p

---------------------------------------------------------------
    
Notes for casual users: You can run and build what I have here, but a stable "normal" program for release is still in the works!    

Basic Class Diagram (Im not one much for documentation, sorry :p )    
    
I dont have my Cocos2D-X implementation documented yet - its late, ill do it later.
        
![](Resources/ClassDiagram.png?raw=true)

---------------------------------------------------------------



