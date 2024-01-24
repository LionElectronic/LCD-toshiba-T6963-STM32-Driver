
#ifndef _FONT_H_
	#define _FONT_H_

	#include <string.h>
	#include "Graphic.h"

 	#define FONT_HEADER_SIZE  				7 					// header size of fonts
    #define PutPixel(x, y, clr)											T6963_SetPixel(x, y, clr)
	// Letter type (English - Persian)
	typedef enum {
		E_LETTER,
	  P_LETTER
	} Lt_Mode;

	/////////////////////////////////////////////////////////
	#define STYLE_NONE								0
	#define STYLE_NO_ZERO   					1
	#define STYLE_NO_SPACE  					2
	
	#define ALINE_LEFT								0
	#define ALINE_CENTER							1
	#define ALINE_RIGHT								2
	#define ALINE_MARK								(ALINE_LEFT | ALINE_CENTER | ALINE_RIGHT)
	
	#define BORDER_NONE								0x00
	#define BORDER_RECT								0x04
	#define BORDER_FILL								0x08
	#define BORDER_BEVEL							0xF0	// bevel radius 0x00(rectangle), 0x10-0xF0(radius size)
	#define BORDER_MASK								(BORDER_FILL | BORDER_RECT)
	#define bvl(x)										(x<<4)


	/////////////////////////
	extern unsigned char 							rot;
	extern unsigned char 							Reverse;
	extern unsigned char							Horizontal;

	extern unsigned short							FgColor;
	extern unsigned short							BkColor;
	extern unsigned char							FontFixed;
	extern unsigned char							NonTransparence;
	
	extern unsigned char 							FontWidth;
	extern unsigned char 							FontHeight;
	extern unsigned char 							FontXScale;
	extern unsigned char 							FontYScale;
	extern unsigned char 							FontSpace;
	
	extern unsigned int 							cursorX;
	extern unsigned int 							cursorY;

	extern Lt_Mode										peLETTER;

	/////////////////////////////////////////////////////////	
	#define GetLetter() 							peLETTER

	#define GetCursorX() 							cursorX
	#define GetCursorY() 							cursorY
	#define SetCursorX(x) 						cursorX = x
	#define SetCursorY(y) 						cursorY = y
	#define SetCursor(x,y) 						{cursorX = x; cursorY = y;}
	
	#define LcdRot(n)									rot = n
	#define LcdReverse(n)							Reverse = n
	#define LcdHorizontal(n)					Horizontal = n
	
	#define LcdFontFixed(n)						FontFixed = n
	#define LcdNonTransparence(n)			NonTransparence = n
	
	#define SetFgColor(c)							FgColor = c
	#define SetBkColor(c)							BkColor = c
	#define GetFgColor()							FgColor
	#define GetBkColor()							BkColor
	
	#define LcdFontXScale(n)					FontXScale = n
	#define LcdFontYScale(n)					FontYScale = n
	
	#define LcdFontSpaceX(n)					FontSpaceX  = n
	#define LcdFontSpaceY(n)					FontSpaceY  = n


	#define LcdFontWidth() 	 					FontWidth
	#define LcdFontHeight()						FontHeight
	
	// complex function
	#define DrawStringAt(l,c,s,fk,bk)			{SetLine(l,c); SetFgColor(fk); SetBkColor(bk); Puts(s);}
	//#define DrawStringAtP(l,c,s,fk,bk)		{SetLine(l,c); SetFgColor(fk); SetBkColor(bk); PutsP(s);}

	
	//******************* Function Prototypes
	void LcdFont(const unsigned char *pointer);

	void SetLetter(Lt_Mode L);
	void SetLine(unsigned char line,unsigned char column);

	void PutChar(unsigned char c);
	void Puts(char *Text);
	//void PutsP(char *Text);

	void PutLong(unsigned long src, unsigned char digit, unsigned char decimal, unsigned char Parameter);
	void PutInt(unsigned short src, unsigned char digit, unsigned char decimal, unsigned char Parameter);
	void PutByte(unsigned char src, unsigned char digit, unsigned char decimal, unsigned char Parameter);
	
	void PutText(unsigned short left, unsigned short top, unsigned short right, unsigned short bottom, char *str, unsigned char style);
	
	//void PutTextP(unsigned short left, unsigned short top, unsigned short right, unsigned short bottom, _const char *str, unsigned char style);
	
	void TextBox(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, char *str, unsigned char style);
	/*
	meghdare X avval marbot be shoro va meghdare X dovvom marbot be payan an reshte dar mehvare  X ha mibashad
	in maghadir baraye Y ha ham be hamin shekl mibashad
	baraye chap chin , rast chin va vasat chin bayad motaghayyer "style" ra tanzim nemod. 
	*/
	
	void TextBoxP(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, const char *str, unsigned char style);
	unsigned char Bit_Is_Set(unsigned char ,unsigned char);
#endif	//_FONT_H_
