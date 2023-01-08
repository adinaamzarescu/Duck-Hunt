# Duck Hunt 2D Game
#### Copyright Adina-Maria Amzarescu
__________________________________________________________

![example](https://github.com/adinaamzarescu/EGC/blob/main/example.gif)

__________________________________________________________

### Description

Simplified version of the Duck Hunt game.

Technologies used:
  * C++
  * OpenGL

__________________________________________________________

### Game

Each duck will appear on the screen one after the other.
The trajectory of the duck is determined randomly. 
When it touches the edges of the screen, it will bounce 
at a 90 degrees angle.

The player has 3 lives and 3 bullets.

When the player shoots a duck, it will change its direction 
perpendicularly down, and the player accumulates points. 
At that moment the number of bullets will be reset to 3.

If the player misses, he will lose one bullet for each 
missed shot. 

If he runs out of bullets he will lose a life and the 
duck will escape.

If the player fails to shoot the duck in time, the duck 
will escape and he will lose a life.

When the player shoots 5 ducks in a row, it is considered 
"on killing spree". A diamond will appear in the top left 
of the screen to indicate this, along with the text 
"Killing spree".
The moment he misses a duck, he will no longer 
be on a killing spree.

Once every 5 ducks the player will begin the next round. 
The speed of the ducks will increase with each round. 
The moment of transition to a new round will be marked by 
the rendering of the text "next round" at the top of the screen.

If the player loses all 3 lives the game will end.

When the player reaches the maximum score, he has won, 
and the game will end.
