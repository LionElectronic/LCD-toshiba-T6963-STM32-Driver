//-----------------------------------------------------------------------------
// Copyright:      RAD Electronic Co. LTD,
// Author:         jaruwit supa, Base on FontEditor written by H. Reddmann
//								 Modified by Sh. Nourbakhsh Rad for Persian and Arabic font
//								 and fixed some errors
// Remarks:        
// known Problems: none
// Version:        2.0.0  15.10.2011
// Description:    Font Library
//-----------------------------------------------------------------------------
#include "T6963.h"
#include "Font.h"
#include "PE_Map.h"


const unsigned char 	   *FontPointer; 									// Font	Pointer
unsigned char 						rot 						= 0;					// Rot 0=0°, 1=90°
unsigned char 						Reverse					= 0;					// Reverse text direction on the display
unsigned char							Horizontal			=	1;					// 1: Portrait - 240x320 ,   2: Landscape - 320x240

unsigned  char 							c1=0;  // Last character buffer

unsigned short 						FgColor 				= BLACK;			// Text fg color, 5-6-5 RGB
unsigned short 						BkColor 				= WHITE;			// Text bk color, 5-6-5 RGB
unsigned char 						FontFixed				= 0;					// Text type 0=Proportional , 1=Fixed
unsigned char							NonTransparence = 1;					// Transparent 0=No, 1=Yes

unsigned short 						fontSize;											// size of current font
unsigned char 						firstchar;										// first character noumber of current font
unsigned char 						lastchar;											// last character noumber of current font
unsigned char 						charwidth;										// current character width register

unsigned char							FontWidth;										// max width of font
unsigned char							FontHeight;										// max height of font
unsigned char 						FontXScale 			= 1;					// X size of font
unsigned char 						FontYScale 			= 1;					// Y size of font

unsigned char 						FontSpaceX 			= 0;					// space between char
unsigned char 						FontSpaceY			= 0;					// space between lines

unsigned int 							cursorX 				= 0;					// x position
unsigned int 							cursorY 				= 0;					// y position


Lt_Mode									peLETTER				= E_LETTER;		// English or Persian letter

unsigned char 						prevLet 				= 0xFF;				// previous persian character register
unsigned char	 						nextLet 				= 0xFF; 			// next persian character register

//*************************************************
//******************* Functions *******************
//*************************************************
#if KeilARM
	size_t StrNlen (_const char* s, size_t maxlen)
	{
		size_t len = 0;
	
	  while ((len <= maxlen) && (*s))
	  {
	  	s++;
	    len++;
	  }
	
	  return(len);
	} //*StrNlen
#endif

void PutCharEN(unsigned char c)
{
	unsigned char 			byte 					= 0;
	unsigned char 			bitoffset 				= 0;
	unsigned char 			maske 					= 0;
	unsigned short 			bcounter 				= 0;
	unsigned short 			bitsbischar 			= 0;
	unsigned short 			bytesbischar			= 0;
	unsigned short 			xPos,yPos;
	
	unsigned char 			Ccounter 				= 0;
	unsigned char 			xc						= 0;
	unsigned char 			yc						= 0;
	unsigned char 			sx 						= 0;
	unsigned char 			sy 						= 0;

   // get current character width
	charwidth	= (FontPointer[(unsigned int)(c)+FONT_HEADER_SIZE-firstchar]);
	
	
	if(c == '\n')
	{
		cursorX = 0;
		cursorY = cursorY + (unsigned int)FontHeight * FontYScale; 
		
		return;
	}

	// character out of range.
  if( (c < firstchar) || (c > lastchar) || (fontSize == 0)) 
  {
	  return;
  };
	// character is not in list.
	if (charwidth == 0)
	{
		return;
	};
	// sara thai font. line remain at last position
	if(FontFixed)
	{
		charwidth = FontWidth;
	}
	else
	{
		//english special fonts!
		if (((c >= 0xd4) && (c <= 0xda)) || 
	  	  ((c >= 0xe7) && (c <= 0xec)) ||
				 (c == 0xd1))
		{
			cursorX = cursorX - (unsigned int)charwidth * FontXScale;
		}
	}

	// fixed width for digit
 	if((c >= '0') && (c <= '9'))		// english : 0 to 9
		charwidth = (FontPointer[(unsigned int)(FONT_HEADER_SIZE)+'0'-firstchar]);		//width reference = ZERO
	
	// line adjust
	if(((int)cursorX + charwidth * FontXScale) > GetMaxX())
	{
		cursorY = cursorY + (unsigned int)FontHeight * FontYScale; 
		cursorX = 0;
	}

	// calculate current character position on the table
	for(Ccounter = 0; Ccounter < c-firstchar; Ccounter++)
		bitsbischar += ((FontPointer[(unsigned int)(Ccounter)+FONT_HEADER_SIZE]));	//c0_width +...+ cn_width
    
    
	bitsbischar 		*= FontHeight;																										//c_widths * FH
	bitsbischar 		+= (((unsigned short)(lastchar)-firstchar)+FONT_HEADER_SIZE)*8;		//plus font headers
	bytesbischar 		 = bitsbischar/8;																//
	bitoffset 			 = bitsbischar % 8;															//
	maske						 = bitoffset % 8;																//

	// draw character
	for(xc = 0; xc < charwidth; xc++)
	{
		for(yc = 0; yc < FontHeight; yc++)
		{
			if(maske > 7)
			{
				maske = 0;
				bcounter += 1;
			}
			byte = (FontPointer[bytesbischar + bcounter + 1]);

			xPos = (unsigned short)xc*FontXScale + cursorX;
			
			if(Horizontal)	//128x64
			{
				if(Reverse)
					yPos = (((unsigned short)FontHeight-yc)*FontYScale + cursorY);
				else
					yPos = (((unsigned short)yc)*FontYScale + cursorY);     
			}
			else						//64x128
			{
				if(Reverse)
					yPos = (((unsigned short)FontHeight-yc)*FontYScale + cursorY);
				else
					yPos = (((unsigned short)yc)*FontYScale + cursorY);
				
			}	//Horizontal

			for(sx = 0; sx < FontXScale; sx++)
			{
				for(sy = 0; sy < FontYScale; sy++)
				{
					if(Bit_Is_Set(byte, maske))
					{
						if(rot)		PutPixel(yPos+sy, xPos+sx, FgColor);
						else			PutPixel(xPos+sx, yPos+sy, FgColor);
					}
					else
					{
						if(NonTransparence)
						{
							if(rot)		PutPixel(yPos+sy, xPos+sx, BkColor);
							else			PutPixel(xPos+sx, yPos+sy, BkColor);
						}
					}
				};//for sy
			};//for sx
			
			maske++;
		};//for yc
	};//for xc
	
	// adjust cursor to next position - english
	//cursorX	+= (unsigned int)charwidth * FontXScale + FontSpace;
	cursorX	+= (unsigned int)charwidth * FontXScale + FontSpaceX;
}	//*PutCharEN

void PutCharPE(unsigned char c)
{
	unsigned char 			byte 					= 0;
	unsigned char 			bitoffset 		= 0;
	unsigned char 			maske 				= 0;
	unsigned short 			bcounter 			= 0;
	unsigned short 			bitsbischar 	= 0;
	unsigned short 			bytesbischar	= 0;
	unsigned short 			xPos,yPos;

	unsigned char 			Ccounter 			= 0;
	unsigned char 			xc 						= 0;
	unsigned char 			yc 						= 0;
	unsigned char 			sx 						= 0;
	unsigned char 			sy 						= 0;
	
	// get current character width
	charwidth	= (FontPointer[(unsigned int)(c)+FONT_HEADER_SIZE-firstchar]);
	

	// line feed, goto next line
	if(c == '\n')
	{
		cursorX = GetMaxX();
		cursorY += (unsigned int)(FontHeight +FontSpaceY)* FontYScale;
		
		return;
	}

	// character out of range.
  if( (c < firstchar) || (c > lastchar) || (fontSize == 0)) 
  {
  	return;
  };
	// character is not in list.
	if (charwidth == 0)
	{
		return;
	};
	// sara thai font. line remain at last position
	if(FontFixed)
	{
		charwidth = FontWidth;
	};
	// line adjust
	if(((int)cursorX - charwidth * FontXScale) < 0)
  {
		cursorY = cursorY   + (unsigned int)FontHeight * FontYScale; 
		cursorX = GetMaxX() - (unsigned int)charwidth * FontXScale;
	}

	// adjust cursor to current position - persian
	cursorX	-= (unsigned int)charwidth * FontXScale + FontSpaceX;

	// calculate current character position on the table
	for(Ccounter = 0; Ccounter < c-firstchar; Ccounter++)
		bitsbischar += ((FontPointer[(unsigned int)(Ccounter)+FONT_HEADER_SIZE]));	//c0_width +...+ cn_width


	bitsbischar 		*= FontHeight;																										//c_widths * FH
	bitsbischar 		+= (((unsigned short)(lastchar)-firstchar)+FONT_HEADER_SIZE)*8;		//plus font headers
	bytesbischar 		 = bitsbischar/8;									//
	bitoffset 			 = bitsbischar % 8;								//
	maske						 = bitoffset % 8;									//

	// draw character
	for(xc = 0; xc < charwidth; xc++)
	{
		for(yc = 0; yc < FontHeight; yc++)
		{
			if(maske > 7)
			{
				maske = 0;
				bcounter+=1;
			}
			byte = (FontPointer[bytesbischar + bcounter + 1]);

			xPos = (unsigned short)xc*FontXScale + cursorX;
			
			if(Horizontal)	//128x64
			{
				if(Reverse)
					yPos = (((unsigned short)FontHeight-yc)*FontYScale + cursorY);
				else
					yPos = (((unsigned short)yc)*FontYScale + cursorY);     
			}
			else						//64x128
			{
				if(Reverse)
					yPos = (((unsigned short)FontHeight-yc)*FontYScale + cursorY);
				else
					yPos = (((unsigned short)yc)*FontYScale + cursorY);
				
			}	//Horizontal

			for(sx = 0; sx < FontXScale; sx++)
			{
				for(sy = 0; sy < FontYScale; sy++)
				{
					if(Bit_Is_Set(byte, maske))
					{
						if(rot)		PutPixel(yPos+sy, xPos+sx, FgColor);
						else			PutPixel(xPos+sx, yPos+sy, FgColor);
					}
					else
					{
						if(NonTransparence)
						{
							if(rot)		PutPixel(yPos+sy, xPos+sx, BkColor);
							else			PutPixel(xPos+sx, yPos+sy, BkColor);
						}
					}
				};//for sy
			};//for sx
			
			maske++;
		}//for yc
	}//for xc	
}	//*PutCharPE

unsigned int CalcTextWidthEN(char *str)
{
	unsigned int 		strSize = 0;
	unsigned char 	c;
	unsigned int 		i = 0;	

	while(str[i])
	{
		c = str[i++];
		
		if(c == '\n')			continue;
		
		if(FontFixed)
			strSize += (unsigned int)(FontWidth) * FontXScale;
		else
		{
		  if((c < firstchar) || (c > lastchar)) 
				charwidth = FontWidth;
			else
			{
				charwidth = (FontPointer[(unsigned int)(c)+FONT_HEADER_SIZE-firstchar]);

				//english spesial fonts!
				if (((c >= 0xd4) && (c <= 0xda)) || 
		    		((c >= 0xe7) && (c <= 0xec)) ||
				  	 (c == 0xd1))

					charwidth = 0;
			}
			
			strSize += (unsigned int)(charwidth) * FontXScale;
		}
		
		strSize += FontSpaceX;
	}//while
	
	return(strSize);
}	//*CalcTextWidthEN

unsigned int CalcTextWidthPE(char *str)
{
	unsigned char 	curnLet, dumyLet;
	unsigned char 	Pstat, stat, Nstat;
	
	unsigned char		backFontSpace =FontSpaceX;
	unsigned int 		strSize = 0;
	unsigned int		i = 0;
	
 	while(str[i])
	{ 		
		curnLet = str[i++];
		if(curnLet == '\n')			continue;
	
		if(FontFixed)
			strSize += (unsigned int)(FontWidth) * FontXScale;
		else
		{
		 	if((curnLet < firstchar) || (curnLet > lastchar)) 
				charwidth = FontWidth;
			else
			{
		 		switch(curnLet)
		 		{	
		 			case 0x81:				//peh
		    		curnLet = 0xEA;
		 				break;
		 			case 0x8D:				//cheh
		    		curnLet = 0xEB;
		 				break;
		 			case 0x8E:				//zheh
		    		curnLet = 0xEE;
		 				break;
		 			case 0x90:				//geh
		    		curnLet = 0xEF;
		 				break;
					case 0x98:				//Ke
		    		curnLet = 0xDF;
		 				break;
		 			case 0xE1:				//laa
		    		nextLet = str[i++];
		    		
		    		if(nextLet == 0xC7)
		    			curnLet = 0xFB;
		    		else
		    		{
		    			i--;
		    			curnLet = 0xE1;
		    		}
		 				break;
		 			case 0x30:				//persian digits 0...9
					case 0x31:
					case 0x32:
					case 0x33:
					case 0x34:
					case 0x35:
					case 0x36:
					case 0x37:
					case 0x38:
					case 0x39:
						curnLet -= 0x20;
		 				break;
		 			case 0x3F:				//persian question mark
		    		curnLet = 0xBF;
		 				break;
		 			case 0x3B:				//persian semicolon
		    		curnLet = 0x1F;
		 				break;
		 			case 0x2C:				//persian comma
		    		curnLet = 0x1D;
		 				break;
		 			case 0x2E:				//persian point
		    		curnLet = 0x1C;
		 				break; 				
				}//switch curnLet
		
				//--------------------------------
		  	nextLet = str[i++];
		  	i--;
		  	
		 		switch(nextLet)
		 		{	
		 			case 0x81:				//peh
		    		nextLet = 0xEA;
		 				break;
		 			case 0x8D:				//cheh
		    		nextLet = 0xEB;
		 				break;
		 			case 0x8E:				//zheh
		    		nextLet = 0xEE;
		 				break;
		 			case 0x90:				//geh
		    		nextLet = 0xEF;
		 				break;
					case 0x98:				//Ke
		    		nextLet = 0xDF;
		 				break;
		 			case 0x30:				//0...9
					case 0x31:
					case 0x32:
					case 0x33:
					case 0x34:
					case 0x35:
					case 0x36:
					case 0x37:
					case 0x38:
					case 0x39:
						nextLet -= 0x20;
		 				break; 			
		 			case 0x3F:				//persian question mark
		    		nextLet = 0xBF;
		 				break;
		 			case 0x3B:				//persian semicolon
		    		nextLet = 0x1F;
		 				break;
		 			case 0x2C:				//persian comma
		    		nextLet = 0x1D;
		 				break;
		 			case 0x2E:				//persian point
		    		nextLet = 0x1C;
		 				break; 				
				}//switch nextLet

				if(curnLet > 0xC0)
				{		
					if(prevLet > 0xC0)
						Pstat = (((PEmap[prevLet-0xC1][5])));
					else
						Pstat = 0;
						
					if(nextLet > 0xC0)
						Nstat = (((PEmap[nextLet-0xC1][4])));
					else
						Nstat = 0;
					
					stat = (Pstat<<1) | Nstat;		
					
					if(stat>1)	FontSpaceX = 0;
					else 				FontSpaceX = backFontSpace;
					////////////////
					dumyLet = ((PEmap[curnLet-0xC1][stat]));
					
					charwidth = (FontPointer[(unsigned int)(dumyLet)+FONT_HEADER_SIZE-firstchar]);
					strSize += (unsigned int)(charwidth) * FontXScale;
					strSize += FontSpaceX;
					////////////////
					FontSpaceX = backFontSpace;
				}
				else
				{
					charwidth = (FontPointer[(unsigned int)(curnLet)+FONT_HEADER_SIZE-firstchar]);
					strSize += (unsigned int)(charwidth) * FontXScale;
					strSize += FontSpaceX;
				}
				
				prevLet = curnLet;
			}
		}
	}//while

 	prevLet = 0xFF;
 	
	return(strSize);
}	//*CalcTextWidthPE

unsigned int CalcTextWidth(char *Text)
{
	if(peLETTER == E_LETTER)
		return(CalcTextWidthEN(Text));
	else
		return(CalcTextWidthPE(Text));
}	//*CalcTextWidth

unsigned int CalcTextHeight(void)
{
	return((unsigned int)(FontHeight) * FontYScale);
}	//*CalcTextHeight


// Convert a single Character from UTF8 to Extended ASCII
// Return "0" if a byte has to be ignored
char  utf8ascii(char ascii) {

    if ( ascii<128 )   // Standard ASCII-set 0..0x7F handling
    {   c1=0;
        return( ascii );
    }

    // get previous input
    char last = c1;   // get last char
    c1=ascii;         // remember actual character

switch (last)     // conversion depending on first UTF8-character
    {
case 0xd8:
        if(ascii>=0xa0 && ascii<=0xb6)
        {
        return (ascii + 0x20);
        }

        if(ascii>=0xb7 && ascii<=0xba)
        {
        	return (ascii + 0x21);
        }
        break;
case 0xd9:
        if(ascii>=0x80 && ascii<=0x83)
        {
        	return (ascii + 0x5c);
        }

        if(ascii==0x84)
        {
        	return (ascii + 0x5d);
        }

        if(ascii>=0x85 && ascii<=0x88)
        {
        	return (ascii + 0x5e);
        }

        if(ascii==0x89 || ascii==0x8a)
        {
        	return (ascii + 0x63);
        }

        if(ascii==0xbe)
        {
        	return 0x81;
        }
        break;
case 0xda:
        if(ascii==0x86)
        {
        	return 0x8d;
        }
        if(ascii==0x98)//zhe
        {
        	return 0x8e;
        }

        if(ascii==0xaf)
        {
        	return 0x90;
        }
        if(ascii==0xa9)//ke
          {
          	return 0xdf;
          }
        break;
case 0xdb:
        if(ascii==0x8c)
        {
        	return 0xed;
        }
        break;
    }

    return  (0);                                     // otherwise: return zero, if character has to be ignored
}


void PutsPE(char *str0)
{	
	unsigned char 	curnLet;
	unsigned char 	Pstat, stat, Nstat;
	
	unsigned char		backFontSpace = FontSpaceX;
	char 						strTemp[50];
	char 						str[50];
	unsigned char 	i = 0, j = 0,c=0;
	unsigned int		k = 0;

	// ****** UTF8-Decoder: convert UTF8-string to extended ASCII *******
	        for (i=0; i<strlen(str0); i++)
	        {
	                c = utf8ascii(str0[i]);
	                if (c!=0) str[k++]=c;

	        }
	        str[k]=0;
	        i = 0;
	        k=0;

 	while(str[k])
	{ 		
 		curnLet = str[k++];
 		
 		switch(curnLet)
 		{	
 			case 0x81:				//peh
    		curnLet = 0xEA;
 				break;
 			case 0x8D:				//cheh
    		curnLet = 0xEB;
 				break;
 			case 0x8E:				//zheh
    		curnLet = 0xEE;
 				break;
 			case 0x90:				//geh
    		curnLet = 0xEF;
 				break;
			case 0x98:				//Ke
		    curnLet = 0xDF;
		 		break;
 			case 0xE1:				//laa
    		nextLet = str[k++];
    		
    		if(nextLet == 0xC7)
    			curnLet = 0xFB;
    		else
    		{
    			k--;
    			curnLet = 0xE1;
    		}
 				break;
 			case 0x3F:				//persian question mark
    		curnLet = 0xBF;
 				break;
 			case 0x3B:				//persian semicolon
    		curnLet = 0x1F;
 				break;
 			case 0x2C:				//persian comma
    		curnLet = 0x1D;
 				break;
 			case 0x2E:				//persian point
    		curnLet = 0x1C;
 				break; 				
		}//switch curnLet
		
		//--------------------------------
  	nextLet = str[k++];
  	k--;
 	
 		switch(nextLet)
 		{	
 			case 0x81:				//peh
    		nextLet = 0xEA;
 				break;
 			case 0x8D:				//cheh
    		nextLet = 0xEB;
 				break;
 			case 0x8E:				//zheh
    		nextLet = 0xEE;
 				break;
 			case 0x90:				//geh
    		nextLet = 0xEF;
 				break;
			case 0x98:				//Ke
		    nextLet = 0xDF;
		 		break;
 			case 0x3F:				//persian question mark
    		nextLet = 0xBF;
 				break;
 			case 0x3B:				//persian semicolon
    		nextLet = 0x1F;
 				break;
 			case 0x2C:				//persian comma
    		nextLet = 0x1D;
 				break;
 			case 0x2E:				//persian point
    		nextLet = 0x1C;
 				break; 			
		}//switch nextLet

		if(curnLet > 0xC0)
		{		
			if(prevLet > 0xC0)
				Pstat = (((PEmap[prevLet-0xC1][5])));		// 1: prevLet attach to curnLet -- 0: prevLet don't attach to curnLet
			else
				Pstat = 0;
				
			if(nextLet > 0xC0)
				Nstat = (((PEmap[nextLet-0xC1][4])));		// 1: nextLet attach to curnLet -- 0: nextLet don't attach to curnLet
			else
				Nstat = 0;
			
			//			Pstat	|	Nstat	|	stat
			//		 -------+-------+------
			//				0		|		0		|		0				curnLet, don't attach to prevLet and nextLet
			//				0		|		1		|		1				curnLet, don't attach to prevLet and attach to nextLet
			//				1		|		0		|		2				curnLet, attach to prevLet and don't attach to nextLet
			//				1		|		1		|		3				curnLet, attach to prevLet and nextLet
			
			stat = (Pstat<<1) | Nstat;		
			
			if(stat>1)	FontSpaceX = 0;
			else 				FontSpaceX = backFontSpace;
			
			PutCharPE(((PEmap[curnLet-0xC1][stat])));
			FontSpaceX = backFontSpace;
		}
		else	//Original 'curnLet' below 193 without ( � � � � )  -- for digits and symbols!
		{
  		if((curnLet >= '0') && (curnLet <= '9'))		// 0 to 9
  		{
  			i++;
  			strTemp[i] 	 = curnLet;

  			if(!((nextLet >= '0') && (nextLet <= '9')))
				{
					for(j=i; j>0; j--)
						PutCharPE(strTemp[j]-0x20);

					i = 0;
				}
			}		
			else
				PutCharPE(curnLet);
		}
		
		prevLet = curnLet;
	}//while

 	prevLet = 0xFF;
}	//*PutsPE

//-------------------------------------------------
//**** select font
void LcdFont(const unsigned char *pointer)
{
	FontPointer 			= pointer;

	FontWidth 				= (FontPointer[2]);
	FontHeight				= (FontPointer[3]);

	//fontSize				=	_pgm_read_word(FontPointer[0]);
	fontSize					=	(unsigned short)((FontPointer[1])) << 8;
	fontSize				 += (FontPointer[0]);
	firstchar 				=	(FontPointer[5]);
	lastchar 					=	(FontPointer[6]);
}	//*LcdFont

void SetLetter(Lt_Mode L)
{
	peLETTER = L;
	
	if(L == P_LETTER)
		cursorX = GetMaxX();
	else
		cursorX = 0;
}	//*SetLetter

void SetLine(unsigned char line,unsigned char column)
{
	if(peLETTER == P_LETTER)
		cursorX =GetMaxX() - (unsigned int)FontWidth  * FontXScale * column;
	else
		cursorX =(unsigned int)FontWidth  * FontXScale * column;

	cursorY =(unsigned int)(FontHeight +FontSpaceY)* FontYScale * line;
}	//*SetCursor

void SetLineX(unsigned char line,unsigned char x)
{
		if(peLETTER == P_LETTER)
		{
			cursorX =GetMaxX() - x;
		}
		else{
			cursorX = x;
		}
	cursorY =(unsigned int)(FontHeight +FontSpaceY)* FontYScale * line;
}	//*SetLineX

//-------------------------------------------------
//**** draw char
void PutChar(unsigned char c)
{
  if(peLETTER == P_LETTER)
		PutCharPE(c);
	else
			PutCharEN(c);
}	//*PutChar

//**** draw string
void Puts(char *Text)
{	
	unsigned int		i = 0;
	
  if(peLETTER == P_LETTER)
  {
		PutsPE(Text);
	}
	else
	{

		while(Text[i]) PutCharEN(Text[i++]);

	}
}	//*Puts



unsigned char Bit_Is_Set(unsigned char Byte ,unsigned char Mask)
{
	if(Byte&(0x01<<Mask))
		return 1;
	else
		return 0;
}


/*void PutsP(char *Text)
{
	unsigned int 	i = 0;
	
	while(_pgm_read_byte(Text[i]))
		PutChar(_pgm_read_byte(Text[i++]));
}*/	//*PutsP

//-------------------------------------------------
void PutLong(unsigned long src, unsigned char digit, unsigned char decimal, unsigned char Parameter)
{
	char 			text[10+1];
	unsigned char 	i;
	Lt_Mode		cMode;
	
	cMode = peLETTER;
	SetLetter(E_LETTER);
	
	text[digit] = 0;
	for(i = digit; i >0; i--)
	{
		text[i-1] =(src % 10) + 48;
		src = src/10;
	}//for digit
	
	if (Parameter & (STYLE_NO_ZERO | STYLE_NO_SPACE))
	{
		while(text[i] == '0')
		{
		
			if (Parameter & (STYLE_NO_ZERO))
				PutChar(' ');
			
			i++;
			if (i > digit - decimal -1 -1) // include lead 0.xx
				break;
		}
	}
	
	while(text[i])
	{
		if (i == digit - decimal) // include lead 0.xx
			PutChar('.');
		
		PutChar(text[i++]);
	}

	SetLetter(cMode);
}	//*PutLong

void PutInt(unsigned short src, unsigned char digit, unsigned char decimal, unsigned char Parameter)
{
	unsigned long 		n = src;
	
	PutLong(n, digit, decimal, Parameter);
}	//*PutInt

void PutByte(unsigned char src, unsigned char digit, unsigned char decimal, unsigned char Parameter)
{
	unsigned long 		n = src;
	
	PutLong(n, digit, decimal, Parameter);
}	//*PutByte



void PutText(unsigned short left, unsigned short top, unsigned short right, unsigned short bottom, char *str, unsigned char style)
	{
		unsigned short 			sizeofstring;
	
		sizeofstring = CalcTextWidth(str);
		top = top + (bottom - top - ((unsigned short)(FontHeight)*FontYScale))/2;
	
			if(peLETTER == P_LETTER)
			{
				switch (style & ALINE_MARK)
				{
					case ALINE_RIGHT:
						break;

					case ALINE_CENTER:
							right = right - (right - left - sizeofstring) / 2;
						break;

					case ALINE_LEFT:
						right = left + sizeofstring;
						right = right + FontSpaceX;
						break;
				}//switch

				SetCursorX(right);
			}
			else
			{
				switch (style & ALINE_MARK)
				{
					case ALINE_LEFT:
						left = left + FontSpaceX;
						break;

					case ALINE_CENTER:
							left = left + (right - left - sizeofstring) / 2;
						break;

					case ALINE_RIGHT:
						if (right > sizeofstring)
							left = right - sizeofstring;
						break;
				}//switch

				SetCursorX(left);
			}

		SetCursorY(top);
		Puts(str);
	}	//*PutText

/*void PutTextP(unsigned short left, unsigned short top, unsigned short right, unsigned short bottom, _const char *str, unsigned char style)
{
	char 				strP[100+1];
	
	strncpy(strP, str, strnlen(str,100));
	strP[100] = 0;	// terminate string
	PutText(left, top, right, bottom, strP, style);
}*/	//*PutTextP


void TextBox(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, char *str, unsigned char style)
{
	unsigned int 			r;
	unsigned short 		temp;

	if (style & BORDER_RECT)
	{
		r = (style & BORDER_BEVEL) >> 4;	// get bevel radius
		if (r)	// bevel
		{
			if (style & BORDER_FILL)
				BevelFill(x1+1, y1+1, x2-1, y2-1, r, BkColor);
			
			Bevel(x1, y1, x2, y2, r, FgColor);
		}
		else	// rect
		{
			if (style & BORDER_FILL)
				RectangleFill(x1+1, y1+1, x2-1, y2-1, BkColor);

			Rectangle(x1, y1, x2, y2, FgColor);
		}
	}
	else if (style & BORDER_FILL)
	{
		RectangleFill(x1, y1, x2, y2, BkColor);
	}

	if(rot)
	{
		temp = x1; 		x1 = y1; 		y1 = temp;
		temp = x2; 		x2 = y2; 		y2 = temp;
	}

	if ((style & BORDER_RECT) || (style & BORDER_FILL))
		PutText(x1+1, y1+1, x2-1, y2-1, str, style & ALINE_MARK);
  else
		PutText(x1, y1, x2, y2, str, style & ALINE_MARK);
}	//*TextBox


