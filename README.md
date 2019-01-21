# -MVD-Engine-Programming-Delivery

Things done in this project:

In short: there is a flying cat that keeps going and avoiding random-positioned boxes.

1. The map is generated reading the json and by code. The otuer limits need to be allways there, so these are defined in the json.
All the boxes arround the level are randomly positioned via code.
2. I've made a custom control system, to have an orbiting camera arround the cat. It reads the mouse movement constantly and rotates arround according to the mouse's movement.
3. The flying cat is the main thing here. It's an entity with a mesh, two ray colliders and a script. The script checks the collider's state every frame, and decides the movement of the cat. The cat will keep going foward until it sees a wall. Once it sees a wall, it makes a decision, based on the ray's info. The cat can turn left or right, and if the wall is too close, it will go slower and rotate faster. Sometimes the cat can get stuck, but it manages to get out of trouble because he is aware of this situation. If it finds itself in this situation, will keep rotating until it sees an exit.
