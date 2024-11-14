# vOS-Flipper-0
# vOS GUI Codebase

This codebase provides a simple graphical user interface (GUI) for the Flipper Zero using Furi's GUI and input handling APIs. The interface features a mouse cursor that can be moved using button inputs, a status bar displaying a battery percentage, and the ability to switch between multiple scenes. Additionally, the app can be exited by pressing the back button three times within a specified time window.

## Overview

### Structure
The codebase is organized into the following main components:
- **main.c**: The entry point for the application, which sets up the GUI and handles the main loop.
- **bin/button_handler.c**: Handles button input, manages cursor movement, and controls scene switching.
- **lib/button_handler.h**: Defines the `ButtonHandlerContext` structure and declares the input handling function.
- **bin/draw_canvas.c**: Manages the drawing of different scenes on the canvas, including the status bar and cursor.
- **lib/draw_canvas.h**: Declares the drawing function and defines the window types and cursor position variables.

## Features

### 1. Button Input Handling
The `button_input_callback` function in `button_handler.c` manages input from the Flipper Zero's buttons:
- **Back Button**: Pressing the back button three times within 2 seconds exits the app.
- **Directional Buttons**: Moves the cursor on the screen. The cursor can be moved continuously with long presses or one step at a time with short presses.
- **Scene Switching**: When the cursor reaches the left or right edge of the screen, the scene switches, and the cursor is repositioned at the center.

### 2. Scene Management
Scenes are represented by an enumeration `WindowType`:
- **WindowStatus**: Displays the status bar with the battery percentage and the mouse cursor.
- **WindowEmpty**: An empty screen with a centered label "Empty Window."
- **WindowAbout**: Displays information about the app, such as the version and author.
- **WindowCount**: Used to track the total number of scenes.

### 3. Drawing Functionality
The `draw_callback` function in `draw_canvas.c` handles the rendering of the different scenes:
- **Status Bar**: A white bar at the top of the screen with the app name and battery percentage.
- **Mouse Cursor**: A `^` symbol representing the cursor, which can be moved around the screen.
- **Scene-Specific Content**: Each scene displays different content, depending on the `current_window`.

### 4. Application Lifecycle
The main application logic in `main.c` includes:
- **Initialization**: Allocates and sets up the `ViewPort`, and attaches it to the GUI.
- **Main Loop**: Keeps the app running until the `running` flag in the `ButtonHandlerContext` is set to `false`.
- **Cleanup**: Frees resources and closes the GUI record before exiting.

## How to Use

1. **Navigation**: Use the directional buttons to move the cursor. The cursor can be moved in all scenes.
2. **Scene Switching**: Move the cursor to the left or right edge to switch scenes. The cursor will be reset to the center after switching.
3. **Exiting**: Press the back button three times within 2 seconds to exit the application.

## Dependencies
- **Furi API**: Provides access to the Flipper Zero's hardware and GUI functionality.
- **Input Handling**: For detecting button presses and managing user interaction.
- **Power Service**: For retrieving and displaying battery status.

## Files and Their Roles

### main.c
- Initializes the GUI and sets up the input and drawing callbacks.
- Runs the main loop until the app is exited.

### bin/button_handler.c
- Handles all button input, including cursor movement and scene switching.
- Manages the logic for exiting the app with multiple back button presses.

### lib/button_handler.h
- Defines the structure for the button handler context.
- Declares the input callback function.

### bin/draw_canvas.c
- Manages drawing the content for each scene.
- Renders the status bar, mouse cursor, and scene-specific elements.

### lib/draw_canvas.h
- Declares the drawing function and defines global variables for cursor position and current window.

## Future Improvements
- **Additional Scenes**: Add more scenes with different functionalities.
- **Enhanced Input Handling**: Support for additional button events or gestures.
- **Dynamic Content**: Display more dynamic information, such as the current time or system status.

## Author
- **blmvxer**: Creator of the initial version of the vOS GUI.
