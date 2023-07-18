# snake

[![CMake](https://github.com/adrianovaladar/snake/actions/workflows/cmake.yml/badge.svg)](https://github.com/adrianovaladar/snake/actions/workflows/cmake.yml)

The Snake game project is a classic and popular game implemented in C++23 specifically for Linux terminals. It offers a
fun and engaging gaming experience directly within the terminal environment.

To compile the project, navigate to the root directory and execute the following commands:

    $ cmake .
    $ make

After the compilation is complete, a file named "snake" will appear in the directory. To run the game, simply execute
the command "./snake" without any parameters.

Ensure that the logged-in user has the necessary permissions (read, write, and execute) for the project directory. These
permissions are crucial for the game's settings, best scores files, and the ability to load saved games. These files
will be stored in the "files" directory.

Upon launching the game, a menu will be displayed, similar to the example image provided.
![image](https://github.com/adrianovaladar/snake/assets/60299267/a1ccb51c-bf44-4653-b6da-51be6b6514d6)

The game features various elements to enhance gameplay. There are regular food items that the snake can consume to
increase its length and score by 1. Additionally, there are superfood items that provide 3 points when eaten.

It includes a velocity mechanic. As the snake consumes more food, its velocity gradually increases, making the game more
challenging and exciting. Players need to navigate the snake effectively to avoid colliding with walls (if the borders
are on) or its own body.

The game also provides a pause functionality, allowing players to take breaks during gameplay without losing progress.
Additionally, players have the option to save the game at any point, enabling them to continue from where they left off
at a later time. When a saved game is available, an option to continue the game will be presented in the menu.

One unique aspect of the Snake project is the option to change the size of the game map. The game allows players to
adjust the dimensions of the playable area, providing flexibility in gameplay and accommodating different preferences.

By allowing players to change the map size, they can customize the difficulty level and adapt the gameplay experience to
their liking. A larger map size may introduce additional challenges as the snake needs to navigate through a more
extensive area. On the other hand, a smaller map size may create a more intense and fast-paced gameplay environment.

This feature adds an extra layer of versatility to the game, allowing players to tailor their experience based on their
skill level, personal preferences, or desire for different levels of challenge.

Players can modify the map size through the game's settings, providing an intuitive and accessible way to adjust the
gameplay environment to their desired dimensions. Whether they prefer a spacious playing field or a more compact and
intense space, the option to change the map size offers a customizable experience for players to enjoy.

Players also have the option to customize the status of the borders. They can choose to enable or disable the borders
based on their preference.
Enabling the borders restricts the snake's movement within the playable area, while disabling them allows the snake to
wrap around the screen edges.
This customizable feature allows
players to tailor the game's difficulty and mechanics to their preference.

The game includes a "Best Scores" feature that displays the top five players' scores for a given map size, taking into
account the status of the borders (on/off). Players can strive to achieve high scores and compete with others to secure
a place among the top performers in the game.

The following image showcases a preview of the game.

![preview](https://user-images.githubusercontent.com/60299267/196003941-0192f5d9-f290-4d01-bfe5-30344d8beda6.png)

## Creators

This project was created by [**Adriano Valadar**](https://adrianovaladar.github.io) and [**Rogério
Lopes**](https://github.com/ro-g-er).