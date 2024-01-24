//-----------------------------------------------------------------------------
// Copyright:      RAD Electronic Co. LTD,
// Author:         Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        1.5.0
// Description:    GLCD's graphic founctions
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include "Graphic.h"


// Description	: Draw a line on a graphic LCD
// Input        : x1,y1 - starting coordinates
//              : x2,y2 - ending coordinates
//********************************************************************
void Line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color)
{
	signed int  	x, y, addx, addy, dx, dy;
	signed long 	P;
	int 					i;

	dx = abs((signed int)(x2 - x1));
	dy = abs((signed int)(y2 - y1));
	x  = x1;
	y  = y1;

	addx = addy = 1;
	if(x1 > x2)		addx = -1;
	if(y1 > y2)		addy = -1;

	if (dx >= dy)
	{
		P = 2L*dy - dx;
		for (i=0; i<=dx; ++i)
		{
	  	PutPixel((unsigned char)x, (unsigned char)y, color);
			if(P < 0)
	  	{
	    	P += 2*dy;
	    	x += addx;
	  	}
			else
			{
	    	P += 2*dy - 2*dx;
	    	x += addx;
	    	y += addy;
	  	}
		}
	}
	else
	{
		P = 2L*dx - dy;
		for(i=0; i<=dy; ++i)
		{
	  	PutPixel((unsigned char)x, (unsigned char)y, color);
	  	if(P < 0)
	  	{
	    	P += 2*dx;
	    	y += addy;
	  	}
	  	else
	  	{
	    	P += 2*dx - 2*dy;
	    	x += addx;
	    	y += addy;
	  	}
		}
	}
}	//*Line

// Description  : Draw a rectangle on a graphic LCD
// Input        : x1,y1 - starting coordinates
//              : x2,y2 - ending coordinates
//********************************************************************
void Rectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color)
{
		RectangleFill(x1, y1, x2, y1, color);    // top
    RectangleFill(x1, y2, x2, y2, color);    // bottom
    RectangleFill(x1, y1, x1, y2, color);    // left
    RectangleFill(x2, y1, x2, y2, color);    // right
}	//*Rectangle

// Description	: Draws a beveled figure on the screen. 
// Input       	: x1, y1 - coordinate position of the upper left center
//		      		: x2, y2 - coordinate position of the lower right center
//             	: rad    - defines the redius of the circle,
//             	: fill   - fill yes or no
//********************************************************************
void RoundRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char radius, unsigned char fill, unsigned char color)
{
	signed int 		a, b, P;

	a  = 0;       				// increment by 1
	b  = radius;  				// decrement by 1 using P
	P  = 1 - (signed int)(radius);

	if (fill)
	{		
		RectangleFill((unsigned char)(x1), (unsigned char)(y1+radius), (unsigned char)(x2), (unsigned char)(y2-radius), color);
		
		do
		{
      RectangleFill((unsigned char)(x1-a+radius), (unsigned char)(y1-b+radius), (unsigned char)(a+x2-radius), (unsigned char)(y1-b+radius), color);	// 8 --> 1
      RectangleFill((unsigned char)(x1-b+radius), (unsigned char)(y1-a+radius), (unsigned char)(b+x2-radius), (unsigned char)(y1-a+radius), color);	// 7 --> 2
      RectangleFill((unsigned char)(x1-b+radius), (unsigned char)(a+y2-radius), (unsigned char)(b+x2-radius), (unsigned char)(a+y2-radius), color);	// 6 --> 3
			RectangleFill((unsigned char)(x1-a+radius), (unsigned char)(b+y2-radius), (unsigned char)(a+x2-radius), (unsigned char)(b+y2-radius), color);	// 5 --> 4

			if(P < 0)		P+= 3 + 2*a++;
			else				P+= 5 + 2*(a++ - b--);
		} while(a <= b);
	} //fill
	else
	{
		RectangleFill((unsigned char)(x1+radius), (unsigned char)(y1)       , (unsigned char)(x2-radius), (unsigned char)(y1)       , color);	// top
		RectangleFill((unsigned char)(x1+radius), (unsigned char)(y2)       , (unsigned char)(x2-radius), (unsigned char)(y2)       , color);	// bottom
		RectangleFill((unsigned char)(x1)       , (unsigned char)(y1+radius), (unsigned char)(x1)       , (unsigned char)(y2-radius), color);	// left
		RectangleFill((unsigned char)(x2)       , (unsigned char)(y1+radius), (unsigned char)(x2)       , (unsigned char)(y2-radius), color);	// right

		do
		{
			PutPixel((unsigned char)(a+x2-radius), (unsigned char)(y1-b+radius), color);	// `````` Segment 1
			PutPixel((unsigned char)(b+x2-radius), (unsigned char)(y1-a+radius), color);	// `````` Segment 2
			
			PutPixel((unsigned char)(b+x2-radius), (unsigned char)(a+y2-radius), color);	// `````` Segment 3
			PutPixel((unsigned char)(a+x2-radius), (unsigned char)(b+y2-radius), color);	// `````` Segment 4
			
			PutPixel((unsigned char)(x1-a+radius), (unsigned char)(b+y2-radius), color);	// `````` Segment 5
			PutPixel((unsigned char)(x1-b+radius), (unsigned char)(a+y2-radius), color);	// `````` Segment 6
			
			PutPixel((unsigned char)(x1-b+radius), (unsigned char)(y1-a+radius), color);	// `````` Segment 7
			PutPixel((unsigned char)(x1-a+radius), (unsigned char)(y1-b+radius), color);	// `````` Segment 8
			
			if(P < 0)		P+= 3 + 2*a++;
			else				P+= 5 + 2*(a++ - b--);
		} while(a <= b);
	} //no fill
}	//RoundRectangle

// Description	: Draw a circle on the screen. 
// Input       	: x,y  - the center of the circle
//             	: rad  - defines the redius of the circle,
//             	: fill - fill yes or no
//********************************************************************
void Circle_Fill(unsigned char x, unsigned char y, unsigned char radius, unsigned char fill, unsigned char color)
{
   signed int 	a, b, P;
   
   a = 0;
   b = radius;
   P = 1 - (signed int)(radius);

   do
   {
   		if(fill)
     	{
      	RectangleFill((unsigned char)(x-a), (unsigned char)(y+b), (unsigned char)(x+a), (unsigned char)(y+b), color);	// 5 --> 4
        RectangleFill((unsigned char)(x-a), (unsigned char)(y-b), (unsigned char)(x+a), (unsigned char)(y-b), color);	// 8 --> 1
        RectangleFill((unsigned char)(x-b), (unsigned char)(y+a), (unsigned char)(x+b), (unsigned char)(y+a), color);	// 6 --> 3
        RectangleFill((unsigned char)(x-b), (unsigned char)(y-a), (unsigned char)(x+b), (unsigned char)(y-a), color);	// 7 --> 2
     	}
     	else
     	{
																																			//       		8	1
																																			//       	7			2
																																			//       	6			3
																																			//       		5	4
																																			//
       	PutPixel((unsigned char)(a+x), (unsigned char)(b+y), color);	// `````` Segment 4
        PutPixel((unsigned char)(b+x), (unsigned char)(a+y), color);	// `````` Segment 3
        PutPixel((unsigned char)(x-a), (unsigned char)(b+y), color);	// `````` Segment 5
        PutPixel((unsigned char)(x-b), (unsigned char)(a+y), color);	// `````` Segment 6
        PutPixel((unsigned char)(b+x), (unsigned char)(y-a), color);	// `````` Segment 2
        PutPixel((unsigned char)(a+x), (unsigned char)(y-b), color);	// `````` Segment 1
        PutPixel((unsigned char)(x-a), (unsigned char)(y-b), color);	// `````` Segment 8
        PutPixel((unsigned char)(x-b), (unsigned char)(y-a), color);	// `````` Segment 7
      }

      if(P < 0)    P+= 3 + 2*a++;
      else         P+= 5 + 2*(a++ - b--);
    } while(a <= b);
}	//Circle_Fill
