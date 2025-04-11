# snake

[![CMake](https://github.com/adrianovaladar/snake/actions/workflows/cmake.yml/badge.svg)](https://github.com/adrianovaladar/snake/actions/workflows/cmake.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=adrianovaladar_snake&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=adrianovaladar_snake)
![GitHub contributors](https://img.shields.io/github/contributors/adrianovaladar/snake)
![GitHub release](https://img.shields.io/github/v/release/adrianovaladar/snake)
![GitHub license](https://img.shields.io/github/license/adrianovaladar/snake)

The Snake game project is a classic and popular game implemented in C++23 specifically for Linux terminals. It offers a
fun and engaging gaming experience directly within the terminal environment.

## Installation

To compile the project, navigate to the root directory and execute the following commands:

    $ cmake .
    $ make

After the compilation is complete, a file named snake will appear in the directory. To run the game, simply execute
the following command:

    $ ./snake

Ensure that the logged-in user has the necessary permissions (read, write, and execute) for the project directory. These
permissions are crucial for the game's settings, best scores files, and the ability to save and load games. These files
will be stored in the files' directory.

### Another Approach: Dockerfile

#### Build the docker image

First, build the Docker image using the provided Dockerfile:

    $ docker build -t snake .

This command will create a Docker image tagged as snake.

#### Run the game

Once the image is built, run the game inside a Docker container:

    $ docker run -it -v ~/snake_files:/usr/src/app/files -v ~/snake_files/logs:/usr/src/app/logs snake

This command does the following:

- -it: Runs the container interactively with a terminal;
- -v ~/snake_files:/usr/src/app/files: Mounts the snake_files directory from your local machine (in your home directory)
  to /usr/src/app/files inside the container.
  This allows the game to save data like high scores and saved games to your local machine, ensuring persistence across
  runs;
- -v ~/snake_files/logs:/usr/src/app/logs snake: This allows the game to save logs that can be useful for debugging and
  issue tracking;
- snake: Specifies the Docker image to use.

## Gameplay Features

Upon launching the game, a menu will be displayed, similar to the example image provided.

![image](https://github.com/adrianovaladar/snake/assets/60299267/1622bc1a-3fd7-4a9c-938b-ab42a0b6f1c3)

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

The game includes the best scores feature that displays the top five players' scores for a given map size, taking into
account the status of the borders (on/off). Players can strive to achieve high scores and compete with others to secure
a place among the top performers in the game.

## Preview of the game

A preview of the game can be watched in the following
video: [Snake game preview](https://www.youtube.com/watch?v=1JRSfNTa7Eg).

## Download and Support on itch.io

The game is available for download and support on itch.io. Access the following link to download the game and show
support for the project: [Snake game](https://adrianovaladar.itch.io/snake-game).

## Important note

The code includes a command to clear the terminal for a better gaming experience. If you have any important data or
output in the current terminal session, it is recommended to open a new terminal window or to save your work before
running the game to avoid unintended data loss.

## Creators

This project was created by [**Adriano Valadar**](https://github.com/adrianovaladar) and [**Rogério
Lopes**](https://github.com/ro-g-er).
