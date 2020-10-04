# cub3D
"This project’s objectives are similar to all this first year’s objectives: Rigor, use of C, use of basic algorithms, information research etc. As a graphic design project, cub3D will enable you to improve your skills in these areas: windows, colors, events, fill shapes, etc. To conclude cub3D is a remarkable playground to explore the playful practical applications of mathematics without having to understand the specifics. With the help of the numerous documents available on the internet, you will use mathematics as a tool to create elegant and efficient algorithms."

# Resources
- General
    https://github.com/dichotommy49/cub3d/blob/master/cub3d%20resources.txt
- BMP File
    https://engineering.purdue.edu/ece264/16au/hw/HW13#:~:text=In%20short%2C%20a%20BMP%20file,red%2C%20green%2C%20and%20blue.


# TODOs
- NORM

# DONE
- Display different wall textures (the choice is yours) that vary depending on which side the wall is facing (North, South, East, West).
- Your program must be able to display an item (sprite) instead of a wall.
- Your program must be able to set the floor and ceilling colors to two different ones
- The left and right arrow keys of the keyboard must allow you to look left and right in the maze.
- The W, A, S and D keys must allow you to move the point of view through the maze.
- Pressing ESC must close the window.
- Clicking on the red cross on the window’s frame must close the window and quit the program.
- The management of your window must remain smooth: changing to another window, minimizing, etc.
- If the declared screen size in the map is greater than the display resolution, the window size will be set depending to the current display resolution.
- The management of your window must remain smooth: changing to another window, minimizing, etc. (NO WORK TO DO ON THIS ONE?)
- In case the Deepthought has eyes one day to evaluate your project, your program must save the first rendered image in bmp format when its second argument is "––save".
    - Weird that the save image size is slightly different from the window I see when I run the cub. CHECKED DONE
- Ray: posX, posY, dirX, dirY seems to be off. spawn place is swaped between X axis and Y axis. DONE
- Player position stored correctly, but in cub the posX and posY are inversed. (DONE: reversed argument x and y in set_player_position)
- SHOW SPRITE ON MAP (after parsing from cub file, can'y makke tem appear.) (DONE: also had to reverse x and y in ft_cub_map)
- Sprite Sorting: Zbuffer checks if the osition of the sprite is further away from the closest wall on the Zbuffer[x_axis].
- PARSING MAP
    - Player position (DONE)
    - Map's validity (DONE)
    - Sprite position (DONE)
- Colision: walking towards wall sometime leads to go over them and to see the outside. (SEEMS TO BE RESOLVED)
- Quit the program CLEANLY through ESC KEY, RED CROSS
- COVER ALL ERROR: If any misconfiguration of any kind is encountered in the file, the program must exit properly and return "Error\n" followed by an explicit error message of your choice.