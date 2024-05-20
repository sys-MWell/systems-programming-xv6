#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "rect.h"
#include "hdc.h"

struct hdc hdcList[100];
int counter = 0;

#define PHYSICAL_ADDRESS 0xA0000
#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 200
#define	COLOUR_WHITE 0x0F // Value 15
#define COLOUR_BLACK 0x00

void clear320x200x256() {
	// This function is called from videosetmode.
	// You need to put code to clear the video buffer here.  Initially, 
	// you might just set each pixel to black in a nested loop, but think
	// about faster ways to do it. 
	uchar *VGA = (uchar*)P2V(PHYSICAL_ADDRESS);
	// The total screen resolution pixels
	// Width x height
	int pixels = WINDOW_WIDTH * WINDOW_HEIGHT;
	
	// Nested loop
	for (int i = 0; i < pixels; i++){
		VGA[i] = COLOUR_BLACK;
	}
}

int sys_setpixel(void)
{
	int hdc;
    int x;
    int y;
	
    // Handle parameters
    if (argint(0, &hdc) < 0 || argint(1, &x) < 0 || argint(2, &y) < 0)
        return -1;

    if(hdcList[hdc].index != -1)
    {
        uchar *VGA=(uchar*)P2V(PHYSICAL_ADDRESS);
	    VGA[y*320+x] = hdcList[hdc].penIndex;
        
        return 0;
    }
    else
    {
        return -1;
    }

	return 0;
		
}

int sys_moveto(void)
{
    // Set local variables
    int hdc;
    int x;
    int y;

    // Handle parameters
    if (argint(0, &hdc) < 0 || argint(1, &x) < 0 || argint(2, &y) < 0)
        return -1;

    // Clip x value to ensure it is within the screen limits
    if (x < 0)
    {
        x = 0;
    }
    else if (x >= WINDOW_WIDTH)
    {
        x = WINDOW_WIDTH - 1;
    }

    // Clip y value to ensure it is within the screen limits
    if (y < 0)
    {
        y = 0;
    }
    else if (y >= WINDOW_HEIGHT)
    {
        y = WINDOW_HEIGHT - 1;
    }

    // Set initial moveto coordinates, startin place for line_to
    if(hdcList[hdc].index != -1)
    {
        hdcList[hdc].xPos = x;
        hdcList[hdc].yPos = y;
        return 0;
    }
    else
    {
        return -1;
    }
}

int sys_lineto(void)
{
    int hdc, x1, y1, x0, y0;

    if (argint(0, &hdc) < 0 || argint(1, &x1) < 0 || argint(2, &y1) < 0)
        return -1;

    // Clipping coordinates - within window bounds
    if (x1 >= WINDOW_WIDTH)
        x1 = WINDOW_WIDTH - 1;
    else if (x1 < 0)
        x1 = 0;

    if (y1 >= WINDOW_HEIGHT)
        y1 = WINDOW_HEIGHT - 1;
    else if (y1 < 0)
        y1 = 0;

    uchar *VGA=(uchar*)P2V(PHYSICAL_ADDRESS);

    // Check HDC has a valid index
    if (hdcList[hdc].index != -1)
    {
        // Store the current position (x0, y0) of the HDC
        x0 = hdcList[hdc].xPos;
        y0 = hdcList[hdc].yPos;

        // Update the position of the HDC to the new coordinates (x1, y1)
        hdcList[hdc].xPos = x1;
        hdcList[hdc].yPos = y1;

        // Calculate the differences in x and y coordinates
        int dx = x1 - x0, dy = y1 - y0;

        // Determine the direction of movement in x and y
        int xi = (dx >= 0) ? 1 : -1;
        int yi = (dy >= 0) ? 1 : -1;

        // Ensure dx and dy are positive
        dx = (dx >= 0) ? dx : -dx;
        dy = (dy >= 0) ? dy : -dy;

        // Initialise decision variable and starting position
        int decision, x = x0, y = y0;

        // Check if the line is steeper in the x-direction
        if (dy < dx)
        {
            // Initialise decision variable for Bresenham's algorithm
            decision = (2 * dy) - dx;

            // Iterate over x coordinates and draw pixels along the line
            while (x != x1)
            {
                // Draw pixel
                VGA[y * 320 + x] = hdcList[hdc].penIndex;  
                x += xi;

                // Update decision variable and y coordinate as needed
                if ((decision += 2 * dy) > 0)
                {
                    y += yi;
                    decision -= 2 * dx;
                }
            }
        }
        else // Line is steeper in the y-direction
        {
            // Decision variable
            decision = (2 * dx) - dy;

            // Iterate over y coordinates and draw pixels along the line
            while (y != y1)
            {
                // Draw pixel
                VGA[y * 320 + x] = hdcList[hdc].penIndex;
                y += yi;

                // Update decision variable and x coordinate as needed
                if ((decision += 2 * dx) > 0)
                {
                    x += xi;
                    decision -= 2 * dy;
                }
            }
        }
    }
    else // Invalid HDC index
    {
        return -1;
    }
    // Success
    return 0;

}

int sys_setpencolour(void)
{
    // Declare variables colour index, red (r), green (g), and blue (b) values
    int index, r, g, b;

    // Check (index, r, g, b) can be retrieved from the user space
    if (argint(0, &index) < 0 || argint(1, &r) < 0 || argint(2, &g) < 0 || argint(3, &b) < 0)
        return -1;

    // Ensure that the colour index and RGB values are within valid ranges
    index = (index > 255) ? 255 : (index < 16) ? 16 : index;
    r = (r > 63) ? 63 : (r < 0) ? 0 : r;
    g = (g > 63) ? 63 : (g < 0) ? 0 : g;
    b = (b > 63) ? 63 : (b < 0) ? 0 : b;

    // Set the colour index using the outb function
    outb(0x3C8, index);

    // Set the red, green, and blue values using the outb function
    outb(0x3C9, r);
    outb(0x3C9, g);
    outb(0x3C9, b);

    // Return 0 success
    return 0;
}

int sys_selectpen(void)
{
    // HDC and colour index
    int hdc;
    int index;

    // Check user space arguments
    if (argint(0, &hdc) < 0 || argint(1, &index) < 0)
        return -1;

    // Colour index is within valid range (0 to 255)
    if (index > 255)
    {
        return -1;
    }

    // HDC has valid index in the hdcList arrays
    if (hdcList[hdc].index != -1)
    {
        // Colour index within the valid range (0 to 255)
        if (index > 255)
        {
            return -1;  // Outside the valid range
        }

        // Set the penIndex of the specified HDC to the provided index
        hdcList[hdc].penIndex = index;
        return 0;   // Success
    }
    else
    {
        // Invalid Index
        return -1;
    }

}

int sys_fillrect(void)
{
    // Declare and initialise variables for HDC and a pointer to the rectangle
    int hdc = 0;
    struct rect *rect;

    // Check if the HDC and rectangle pointer arguments can be retrieved from the user space
    if (argint(0, &hdc) < 0 )
    {
        return -1;  // Return -1 if HDC retrieval fails
    }
    if (argptr(1, (void*)&rect, sizeof(&rect)) < 0) 
    {
        return -1;  // Return -1 if rectangle pointer retrieval fails
    }

    // Check if the specified HDC has a valid index in the hdcList array
    if (hdcList[hdc].index != -1)
    {
        // Access the VGA memory using the PHYSICAL_ADDRESS, converting it to a virtual address
        uchar *VGA = (uchar*)P2V(PHYSICAL_ADDRESS);

        // Iterate over the x and y coordinates of the specified rectangle
        for(int x = rect->left; x <= rect->right; x++)
        {
            for(int y = rect->top; y <= rect->bottom; y++)
            {
                // Set the pixel at the current coordinates to the penIndex of the specified HDC
                VGA[y * 320 + x] = hdcList[hdc].penIndex;
            }
        }
        // Success
        return 0;
    }
    else
    {
        // Invalid index
        return -1;
    }
}

int sys_beginpaint(void)
{
    int hwnd;

    // Check argument
    if (argint(0, &hwnd) < 0 )
    {
        return -1;  // Return -1 if HDC retrieval fails
    }

    // Declare a struct hdc
    struct hdc hdc;

    // Iterate over HDC array
    for(int i = 0; i <= 99; i++)
    {
        // Check if the current index is -1, if array element becomes invalid
        if(hdcList[i].index == -1)
        {
            // Update the hdcList array if -1, fix erroneous hdc
            hdc.index = i;
            hdcList[i] = hdc;

            // Return the assigned index and exit the loop
            return hdc.index;
            break;
        }
    }

    // If no available slot is found and the array is full, return -1
    if (counter >= 100)
    {
        return -1;
    }

    hdc.index = counter;
    hdcList[counter] = hdc;
    // Increment counter
    counter++;
    // Return the assigned index
    return hdc.index;
}

int sys_endpaint(void)
{
    int hdc;
    if(argint(0, &hdc) < 0 )
    {
        return -1;
    }
    // When finished -1 from index due to complition
    hdcList[hdc].index = -1;

    return 0;
}