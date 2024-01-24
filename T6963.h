//-----------------------------------------------------------------------------
// Copyright:      www.micronik.ir
// Author:         Hossein Ghiasvand
// Remarks:        
// known Problems: none
// Version:        1.1.0
// Description:    Graphic Library for T6963C- (and compatible) based LCDs
//-----------------------------------------------------------------------------

#ifndef	T6963_H
#define T6963_H
	
	#include "main.h"

#define  SYSTEM_CORE_CLOCK                    168  //72 Mhz

	#define DISPLAY_WIDTH										  	240
	#define DISPLAY_HEIGHT											128
	
	#define T6963_FONT_WIDTH										8   //FS=0


		#define T6963_DB_PRT											GPIOC
		#define T6963_DB_PIN											Read_DB_GLCD()
		#define T6963_DB_High()										HAL_GPIO_WritePin(T6963_DB_PRT,0xFF,1)
		#define T6963_DB_Low()										HAL_GPIO_WritePin(T6963_DB_PRT,0xFF,0)

		//--- CTRL ---
		#define T6963_CE_High()										HAL_GPIO_WritePin(T6963_CE_GPIO_Port,T6963_CE_Pin,1)
		#define T6963_CE_Low()										HAL_GPIO_WritePin(T6963_CE_GPIO_Port,T6963_CE_Pin,0)
		#define T6963_CE_Toggle()									HAL_GPIO_TogglePin(T6963_CE_GPIO_Port,T6963_CE_Pin);

		#define T6963_CD_High()										HAL_GPIO_WritePin(T6963_CD_GPIO_Port,T6963_CD_Pin,1)
		#define T6963_CD_Low()										HAL_GPIO_WritePin(T6963_CD_GPIO_Port,T6963_CD_Pin,0)
		#define T6963_CD_Toggle()									HAL_GPIO_TogglePin(T6963_CD_GPIO_Port,T6963_CD_Pin);

		#define T6963_WR_High()										HAL_GPIO_WritePin(T6963_WR_GPIO_Port,T6963_WR_Pin,1)
		#define T6963_WR_Low()										HAL_GPIO_WritePin(T6963_WR_GPIO_Port,T6963_WR_Pin,0)
		#define T6963_WR_Toggle()									HAL_GPIO_TogglePin(T6963_WR_GPIO_Port,T6963_WR_Pin);

		#define T6963_RD_High()										HAL_GPIO_WritePin(T6963_RD_GPIO_Port,T6963_RD_Pin,1)
		#define T6963_RD_Low()										HAL_GPIO_WritePin(T6963_RD_GPIO_Port,T6963_RD_Pin,0)
		#define T6963_RD_Toggle()									HAL_GPIO_TogglePin(T6963_RD_GPIO_Port,T6963_RD_Pin);

		#define T6963_FS_High()										HAL_GPIO_WritePin(T6963_FS_GPIO_Port,T6963_FS_Pin,1)
		#define T6963_FS_Low()										HAL_GPIO_WritePin(T6963_FS_GPIO_Port,T6963_FS_Pin,0)
		#define T6963_FS_Toggle()									HAL_GPIO_TogglePin(T6963_FS_GPIO_Port,T6963_FS_Pin);

	#define T6963_RST_High()							    	HAL_GPIO_WritePin(T6963_RST_GPIO_Port,T6963_RST_Pin,1)
	#define T6963_RST_Low()								    	HAL_GPIO_WritePin(T6963_RST_GPIO_Port,T6963_RST_Pin,0)
	#define T6963_RST_Toggle()							    HAL_GPIO_TogglePin(v,T6963_RST_Pin);


		#define T6963_DB_WR(x)										Write_DB_GLCD(x)//HAL_GPIO_WritePin(T6963_DB_PRT,0XFF,GPIO_PIN_RESET); HAL_GPIO_WritePin(T6963_DB_PRT,(x),GPIO_PIN_SET)
		#define T6963_DB_RD()										  Read_DB_GLCD()

		#define T6963_DB_OUT()										Output_DB_GLCD()//T6963_DB_DDR = 0xFF
		#define T6963_DB_IN()										Input_DB_GLCD()//T6963_DB_DDR = 0x00

		#define T6963_DB_CLR()										HAL_GPIO_WritePin(T6963_DB_PRT,0xFF,GPIO_PIN_RESET)//T6963_DB_PRT = 0x00
		#define T6963_DB_PLU()										HAL_GPIO_WritePin(T6963_DB_PRT,0xFF,GPIO_PIN_SET)//T6963_DB_PRT = 0xFF

		#define T6963_DB_init()										T6963_DB_OUT(); T6963_DB_CLR()

		//-------------------------
		#define T6963_CE_init()										T6963_CE_Low()
		#define T6963_CD_init()										T6963_CD_Low()
		#define T6963_WR_init()										T6963_WR_Low()
		#define T6963_RD_init()										T6963_RD_Low()
		#define T6963_FS_init()										T6963_FS_Low()

		#define T6963_CE(x)											(x ? (T6963_CE_High()) : (T6963_CE_Low()))
		#define T6963_CD(x)											(x ? (T6963_CD_High()) : (T6963_CD_Low()))
		#define T6963_WR(x)											(x ? (T6963_WR_High()) : (T6963_WR_Low()))
		#define T6963_RD(x)											(x ? (T6963_RD_High()) : (T6963_RD_Low()))
		#define T6963_FS(x)											(x ? (T6963_FS_High()) : (T6963_FS_Low()))

#ifdef T6963_RST_Pin
		#define T6963_RST_init()									T6963_RST_Low()
		#define T6963_RST(x)										(x ? (T6963_RST_High()) : (T6963_RST_Low()))
	#else
		#define T6963_RST_init()
		#define T6963_RST(x)
	#endif

	#ifdef T6963_BKL_Pin
		#define T6963_BKL_init()		T6963_BKL_Low()
		#define T6963_BKL(x)			(x ? (T6963_BKL_High()) : (T6963_BKL_Low()))
	#else
		#define T6963_BKL_init()
		#define T6963_BKL(x)
	#endif

	#ifndef True
		#define True															1
		#define False															0
	#endif

	#ifndef ON
		#define ON																1
		#define OFF																0
	#endif

	#ifndef HIGH
		#define HIGH															1
		#define LOW																0
	#endif

	#define T6963_SIZE_X											DISPLAY_WIDTH
	#define T6963_SIZE_Y											DISPLAY_HEIGHT


	#define GetMaxX()														((unsigned int)T6963_SIZE_X -1)
	#define GetMaxY()														((unsigned int)T6963_SIZE_Y -1)

	// Display definitions
	#define T6963_GRAPHIC_AREA									(T6963_SIZE_X /T6963_FONT_WIDTH)
	#define T6963_TEXT_AREA											(T6963_SIZE_X /T6963_FONT_WIDTH)
	#define T6963_GRAPHIC_SIZE									(T6963_GRAPHIC_AREA *T6963_SIZE_Y)
	#define T6963_TEXT_SIZE											(T6963_TEXT_AREA *(T6963_SIZE_Y /8))
	
	//
	#define T6963_TEXT_HOME										0
	#define T6963_OFFSET_REGISTER								2
	
	#define T6963_GRAPHIC_HOME								(T6963_TEXT_HOME +T6963_TEXT_SIZE)
	#define T6963_EXTERNAL_CG_HOME							(T6963_OFFSET_REGISTER <<11)
	
	//
	#define T6963_SET_CURSOR_POINTER						0x21
	#define T6963_SET_OFFSET_REGISTER						0x22
	#define T6963_SET_ADDRESS_POINTER						0x24
	
	#define T6963_SET_TEXT_HOME_ADDRESS					    0x40
	#define T6963_SET_TEXT_AREA								0x41
	#define T6963_SET_GRAPHIC_HOME_ADDRESS					0x42
	#define T6963_SET_GRAPHIC_AREA							0x43
	
	#define T6963_BUSY_FLAG									0x03

	#define T6963_MODE_SET									0x80
	
	//
	#define T6963_DISPLAY_MODE								0x90
	#define T6963_CURSOR_BLINK_ON							0x01
	#define T6963_CURSOR_DISPLAY_ON							0x02
	#define T6963_TEXT_DISPLAY_ON							0x04
	#define T6963_GRAPHIC_DISPLAY_ON						0x08				
	
	//
	#define T6963_CURSOR_PATTERN_SELECT							0xA0
	#define T6963_CURSOR_1_LINE									0x00
	#define T6963_CURSOR_2_LINE									0x01
	#define T6963_CURSOR_3_LINE									0x02
	#define T6963_CURSOR_4_LINE									0x03
	#define T6963_CURSOR_5_LINE									0x04
	#define T6963_CURSOR_6_LINE									0x05
	#define T6963_CURSOR_7_LINE									0x06
	#define T6963_CURSOR_8_LINE									0x07
	
	//
	#define T6963_SET_DATA_AUTO_WRITE						0xB0
	#define T6963_SET_DATA_AUTO_READ						0xB1
	#define T6963_AUTO_RESET								0xB2
	
	//
	#define T6963_DATA_WRITE_AND_INCREMENT			0xC0
	#define T6963_DATA_READ_AND_INCREMENT			0xC1
	#define T6963_DATA_WRITE_AND_DECREMENT			0xC2
	#define T6963_DATA_READ_AND_DECREMENT			0xC3
	#define T6963_DATA_WRITE_AND_NONVARIALBE		0xC4
	#define T6963_DATA_READ_AND_NONVARIABLE			0xC5
	
	//
	#define T6963_SCREEN_PEEK										0xE0
	#define T6963_SCREEN_COPY										0xE8
	

	// Colors                   		
	typedef enum {
		BLACK		= 1,
		WHITE		= 0
	} T6963_Color;

	// BMP draw modes
	typedef enum {
		INVERS,
		NORMAL,
		TRANS
	} TShow_Mode;

	// Useful user constants     		
	typedef enum {
	  NON_INVERTED	    = 0,
	  INVERTED			= 1
	} TInvert_Mode;
                            		
	// GLCD internal constants	
	typedef struct {
		unsigned char x;
		unsigned char y;
	} T6963Coord;
	

	//******************* Function Prototypes
	void T6963_Initalize(void);																	// Display initalization
	
	//-------------------------------------------------
	void T6963_Backlight(unsigned char x);					// GLCD backlight ON/OFF

	//-------------------------------------------------
	void T6963_ClearCG(void);																		// Clear characters generator area of display RAM memory
	void T6963_ClearText(void);																	// Clear text area of display RAM memory
	void T6963_ClearGraphic(void);															// Clear graphics area of display RAM memory
	void T6963_CLS(void);																				// Clear all area of display RAM memory

	//-------------------------------------------------
	void T6963_TextGoTo(unsigned char x, unsigned char y);			// Set display coordinates
	void T6963_GraphicGoTo(unsigned char x, unsigned char y);		// Set graphic coordinates
		
	//-------------------------------------------------
	void T6963_PutChar(char chr);																// Write a single character (ASCII code) to display RAM memory
	void T6963_PutString(char *str);														// Write null-terminated string to display RAM memory
	void T6963_PutStringf(const char *str);										// Write null-terminated string from program memory to display RAM memory
	void T6963_DefineCharacter(unsigned char charCode, unsigned char *defChar);			// Write single char pattern to character generator area of display RAM memory
	
	//-------------------------------------------------
	void T6963_SetPixel(unsigned char x, unsigned char y, T6963_Color color);				// Set a pixel on screen (color: BLACK or WHITE)
	void T6963_Line(int X1, int Y1,int X2,int Y2, T6963_Color color);
	void T6963_FillRect(int X1, int Y1,int X2,int Y2, T6963_Color color);
	void T6963_InvertRect(int X1, int Y1,int X2,int Y2);
	
	//-------------------------------------------------
	void T6963_DrawBitmap(const unsigned char *bitmap, unsigned char x, unsigned char y, TShow_Mode mode);				// Draw bitmap from program memory
	
	//-------------------------------------------------
	#define StringAt(row, col, str)						T6963_TextGoTo(col, row);		T6963_PutString(str)
	#define CharAt(row, col, chr)						T6963_TextGoTo(col, row);		T6963_PutChar(chr)



#endif	//T6963_H
