# Changelog

## [Unreleased]
### Added
- Implemented `button_input_callback` to handle button inputs and manage the cursor movement across different screens.
- Added `ButtonHandlerContext` to keep track of the running state, back press count, and timing information for exit functionality.
- Introduced `draw_callback` in `draw_canvas.c` to handle drawing on the canvas, including the status bar, cursor, and scene-specific content.
- Created `movement_timer` to manage continuous cursor movement when a button is held down.
- Added logic to wrap the cursor position to the opposite side of the screen when it reaches the edges.
- Set up `movement_timer_callback` for handling continuous cursor movement during long button presses.
- Included an external `init_button_handler` and `free_button_handler` to allocate and free the movement timer.
- Enhanced the status bar to display "vOS" and the current battery percentage.
- Made the mouse cursor display consistently on all screens (WindowStatus, WindowEmpty, WindowAbout).
- Implemented scene-switching logic: moving the cursor to the left or right edges of the screen switches scenes and repositions the cursor to the center.

### Changed
- Updated `handle_cursor_movement` to ensure the cursor wraps around the screen edges and appears on the opposite side.
- Modified the back button logic to require three consecutive short presses within a specified time window to exit the app.
- Refined the cursor movement logic to support both short and long presses for continuous movement.
- Fixed issues where the cursor would stop responding to inputs after holding down a button.

### Fixed
- Addressed issues with undefined or incorrect key references, including `InputKeyUnknown`.
- Fixed compilation errors related to `InputKey` types and added necessary references from the Flipper Zero SDK.
- Corrected the continuous cursor movement logic to ensure it works as expected and doesn’t cause input freezes.

## [Initial Version]
- Set up the basic GUI framework using Flipper Zero SDK.
- Added initial scene management and status bar drawing functionality.
