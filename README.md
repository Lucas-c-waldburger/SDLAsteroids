# SDL Asteroids

![SDL_Asteroids footage](sdl_asteroids_gameplay_1.gif?raw=true "SDL_Asteroids_footage")
![SDL_Asteroids footage2](sdl_asteroids_gameplay_2.gif?raw=true "SDL_Asteroids_footage2")

My take on the classic game. Each game object is a vector of points representing a circle. Creating different n-sided shapes and rotating them is accomplished through subdividing the base circle's perimeter points into n-equal parts and rendering a line between them. Movement is handled by populating another vector of path points through a line-approximation algorithm and iterating through them. These path points are calculated all at once and are not recalculated for the player's ship unless rotated. This eliminates the need for expensive recalculation each frame and is easily copied when the user fires a bullet.

