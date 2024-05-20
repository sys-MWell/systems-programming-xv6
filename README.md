# Systems Programming Assignment 2

## Overview

This project is part of an assessment for a Systems Programming course, focused on implementing graphics routines for a VGA display as part of an operating system kernel. 
The project requires adding system calls that allow user-level programs to perform graphics operations, such as setting a pixel, drawing lines, and filling rectangles, on a VGA display.

## Assessment Content

The assessment is specified in stages, each building on the previous one to add more functionality and achieve higher grades. The following are the stages and their requirements:

### Stage 1: Basic Graphics Function
- **System Calls**:
  - `int setpixel(int hdc, int x, int y)`: Sets the specified pixel to the current default pen colour (white).
  - `int moveto(int hdc, int x, int y)`: Updates the current graphics position to the specified coordinates.
  - `int lineto(int hdc, int x, int y)`: Draws a line from the current graphics position to the specified coordinates using integer arithmetic (Bresenham's algorithm).
  - `void clear320x200x256()`: Clears the screen to black.
- **User-Level Programs**: Demonstrate switching to video mode 0x13, setting pixels, and drawing lines.

### Stage 2: Colour and Filled Shapes
- **System Calls**:
  - `int setpencolour(int index, int r, int g, int b)`: Sets a colour in the palette.
  - `int selectpen(int hdc, int index)`: Selects a pen colour for subsequent drawing operations.
  - `int fillrect(int hdc, struct rect * rect)`: Fills a rectangle with the current pen colour.
- **User-Level Programs**: Demonstrate drawing with different colours and filling rectangles.

### Stage 3: Device Contexts and Multiple Processes
- **System Calls**:
  - `int beginpaint(int hwnd)`: Acquires a device context for drawing.
  - `int endpaint(int hdc)`: Releases the device context.
- **User-Level Programs**: Demonstrate starting another process that makes graphics calls, ensuring graphics operations do not interfere with each other.

## Project Structure

The project includes the following files:

### Source Files
- **graphics.c**: Contains the implementation of graphics functions and system calls.
- **vga.c**: Contains functions for setting video modes.
- **types.h**: Contains type definitions.
- **user.h**: Contains user-level function prototypes.
- **rect.h**: Defines the rectangle structure used in graphics functions.

### User-Level Programs
- **stage1.c**: Draws a white square using basic graphics functions.
- **stage1multiple.c**: Draws multiple blue squares, demonstrating clipping.
- **stage2.c**: Draws a square with different colours for each side.
- **stage2rectfill.c**: Draws and fills rectangles with different colours.
- **stage3.c**: Draws two rectangles with multiple processes.
- **stage3sqr.c**: Draws multiple squares with multiple processes.
- **stage3sqr2.c**: Draws multiple squares in an interesting pattern.

### Build and Run
- **Makefile**: Contains instructions to build the project.
- **sign.pl**: A script to sign the bootable disk image.
- **implementation_log.pdf**: Documents the implementation process, problems encountered, and how they were resolved.

## How to Build and Run

### Prerequisites
- A terminal or command prompt on your system.
- A cross-compiler for building the kernel.
- QEMU or another emulator to test the kernel.

## User-Level Program Description and Testing

### Stage 1
- **stage1.c**:
  - Draws a white square.
  - Uses `setvideomode` to set the screen to graphics mode and back to text mode.
  - Utilises `moveto` and `lineto` to draw the square.
  - ![image](https://github.com/sys-MWell/systems-programming-xv6/assets/74254544/f92f9fb1-a546-4aba-b220-d8de0507689a)

### Stage 1 (Multiple)
- **stage1multiple.c**:
  - Draws multiple blue squares.
  - Demonstrates clipping when squares go out of bounds.
  - ![image](https://github.com/sys-MWell/systems-programming-xv6/assets/74254544/eb9681a9-6860-4f14-a6ab-d0e3c0e5f322)

### Stage 2
- **stage2.c**:
  - Draws a square with different colours for each side.
  - Utilises `setpencolour` to set custom palette colours and `selectpen` to change pen colours.
  - ![image](https://github.com/sys-MWell/systems-programming-xv6/assets/74254544/84c7b579-5544-4198-8f80-ba42070b84fa)

### Stage 2 (Rectangle Fill)
- **stage2rectfill.c**:
  - Draws and fills rectangles with different colours.
  - Utilises `fillrect` to fill rectangles.
  - ![image](https://github.com/sys-MWell/systems-programming-xv6/assets/74254544/f14c3c98-6281-4afe-8033-9ffb26812b1f)

### Stage 3
- **stage3.c**:
  - Draws two rectangles with multiple processes.
  - Demonstrates the use of `beginpaint` and `endpaint`.
  - ![image](https://github.com/sys-MWell/systems-programming-xv6/assets/74254544/c332d6a7-c82b-410a-b5f0-5f8ff072d8dd)

### Stage 3 (Multiple Squares)
- **stage3sqr.c**:
  - Draws multiple squares with multiple processes.
  - Demonstrates clipping and proper use of `fork`.
  - ![image](https://github.com/sys-MWell/systems-programming-xv6/assets/74254544/123ee012-e7a4-4453-921b-bb0982a461c5)

### Stage 3 (Pattern)
- **stage3sqr2.c**:
  - Draws multiple squares in an interesting pattern, incrementing colours to create a shooting star effect.
  - ![image](https://github.com/sys-MWell/systems-programming-xv6/assets/74254544/41424033-a479-49af-9bf5-048f6864c6e6)


