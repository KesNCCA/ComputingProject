# Report

## Abstract

My project is inspired by asteroids, a 1979 game that has the player avoiding asteroids while simultaneously destroying them with projectiles. My aim is to create my own version of this game in three dimensions with tweaked gameplay elements, with the classic teapot model being attacked in virtual 'space'.

## Implementation

All objects within the scene follow a similar rule to the original asteroids game. They switch sides once they reach the end of the plane by multiplying their current coordinates by -1. The game features an accelerate button which increases the speed, and a decelerate button, with 'rotational' movement where the left and right keys rotate the teapot and essentially change its trajectory. I created several vector arrays for both the bullets and the asteroids, as their quantities are unknown, allowing me to dynamically increase the object count whenever needed.

collision detection was one of the most difficult aspects of the game. I used a Jon Macey's sphere-to-sphere collision detection algorithm as my objects were mostly spheres, making collisions quite accurate. For bullet-to-asteroid and asteroid-to-teapot collision, destroying the specific objects in the game once their health reached zero also proved to be difficult, iterate through the vector array of the asteroid or bullet once collision had been detected and remove it from the vector array once its object health reached zero. 

I created a Game 'state' manager which handles drawing both the game and menu screens, allowing the game to start when the user requests (and not simply as soon as the game runs), with the 'enter' key. This state manager also allows the user to pause the game with the 'p' key, having the game freeze in place until it is unpaused. The manager works using enum's that represent different game states, and therefore gives the game the ability to go back to the menu screen when the player has either won or lost.

I used a standard c++ library to generate random numbers. This was used for the asteroid class to have the asteroids set position, move speed and direction be random, for a more dynamic gameplay element where the game is essentially different to play each time. I used SDL2 for my game's window creation - this proved to be an appropriate API as it includes event handling for both keyboard and mouse (specific to game creation). SDL's timer i.e. 'SDL_GetTicks' and other features allowed me to multiply the game objects speed by time; this allowed for frame rate independent gameplay. The speed of objects were initially tied to the varied frame rate of the game which when running on different machines could make the game unplayable, as the frame rate was too high and so the objects moved too fast on different hardware to my own. 

I decided to utilise class inheritance as my game features several objects; the bullets, asteroids and teapot within the game all inherit elements from an object class which contains all the necessary elements that every object in the game needs. The spaceship and asteroid classes are therefore altered from the object class wherever necessary.

## Problems

My asteroids spawn in random positions and directions, and I struggled to find a way to create many of them, and keep track of which newly spawned asteroid was shot. For this I used a dynamic vector array as their quantity can be undefined and increased when needed. 

I also had a problem with moving all my .h and .cpp files into their respective 'include' and 'src' folders, with linker errors that I could not solve, making it difficult to follow the NCCA coding standard as well as I would have liked to.

My main unsolved problem with the game, however, is the camera. With the inclusion of a menu screen, the camera is zoomed far too much once the game has started. This has to be adjusted by the user slightly, until it 'snaps' back into place, and I spent a lengthy amount of time trying to solve this, though I was regretfully unable to.

My initial ambition for the game was to create multiple levels and 'power up' elements that the teapot would collect,  which would alter the gameplay by doing a number of things, such as slowing time or increasing bullet size to make the game easier, etc. However, the initial gameplay elements such as basic collision detection and having the teapot move in whichever angle/direction it is facing, proved to take more time than i had initially anticipated. I needed to forgo these features to insure i had a fully working game with a win and lose state, and ways to keep track of health and score; ensuring the game worked was my primary goal. 

## Result

Overall with the amount of time given, I believe I achieved a decent working game. The game features collision detection and has a win and lose state. it is abstracted out into many classes which i believe makes the code easier to read and edit. 

## References

- Lazyfoo.net. (2014). _Lazy Foo' Productions - Advanced Timers_. [online] Available at: https://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php [Accessed 20 May 2019].

- Macey, j. (2014). _NCCA/Collisions_. [online] GitHub. Available at: https://github.com/NCCA/Collisions/blob/master/SphereSphere/src/NGLScene.cpp [Accessed 16 May 2019].
