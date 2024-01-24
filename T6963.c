//-----------------------------------------------------------------------------
// Copyright:      www.micronik.ir
// Author:         Hossein Ghiasvand
// Remarks:        
// known Problems: none
// Version:        1.1.0
// Description:    Graphic Library for T6963C- (and compatible) based LCDs
//-----------------------------------------------------------------------------

#include "T6963.h"


static  void Input_DB_GLCD(void);
static 	void Output_DB_GLCD(void);
static  void Write_DB_GLCD(unsigned char x);
static 	unsigned char Read_DB_GLCD(void);
static 	void T6963_delay(void);


static void Input_DB_GLCD(void)
{

	GPIO_InitTypeDef GPIO_InitStruct= {0};
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(T6963_DB_PRT, &GPIO_InitStruct);
}
static void Output_DB_GLCD(void)
{
	GPIO_InitTypeDef GPIO_InitStruct= {0};
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(T6963_DB_PRT, &GPIO_InitStruct);

}
static void Write_DB_GLCD(unsigned char command)
{
	HAL_GPIO_WritePin(T6963_DB_PRT,0xFF,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(T6963_DB_PRT,(command),GPIO_PIN_SET);
}

static unsigned char Read_DB_GLCD(void)
{
	unsigned int 	Data=0;
	if(HAL_GPIO_ReadPin(T6963_D0_GPIO_Port,T6963_D0_Pin))
		Data|=1;
	if(HAL_GPIO_ReadPin(T6963_D1_GPIO_Port,T6963_D1_Pin))
		Data|=2;
	if(HAL_GPIO_ReadPin(T6963_D2_GPIO_Port,T6963_D2_Pin))
		Data|=4;
	if(HAL_GPIO_ReadPin(T6963_D3_GPIO_Port,T6963_D3_Pin))
		Data|=8;
	if(HAL_GPIO_ReadPin(T6963_D4_GPIO_Port,T6963_D4_Pin))
		Data|=16;
	if(HAL_GPIO_ReadPin(T6963_D5_GPIO_Port,T6963_D5_Pin))
		Data|=32;
	if(HAL_GPIO_ReadPin(T6963_D6_GPIO_Port,T6963_D6_Pin))
		Data|=64;
	if(HAL_GPIO_ReadPin(T6963_D7_GPIO_Port,T6963_D7_Pin))
		Data|=128;
	return Data;
}


static void T6963_delay(void)
{
	volatile int i;
	for(i=0; i<(SYSTEM_CORE_CLOCK / 1000000); i++)
	{
		__ASM("NOP");
	}
}

void T6963_Init_Port(void)																		// Initial hardware ...
{
	T6963_RST_init();
	T6963_BKL_init();
	
		T6963_DB_init();
	
		T6963_CE_init();
		T6963_CD_init();
		T6963_WR_init();
		T6963_RD_init();
		T6963_FS_init();
}	//T6963_Init_Port

void T6963_BusyWait(void)
{	
		uint8_t 			dat = 0x00;
		
		// wait until GLCD busy bits goes to zero
		T6963_DB_IN();
		
		T6963_RD(LOW);
		T6963_CE(LOW);
		
		T6963_delay();

		//while(!(dat & 0x00))
		//{
			dat = T6963_DB_RD();
		//}

		T6963_CE(HIGH);
		T6963_RD(HIGH);
		T6963_DB_OUT();
		
} //T6963_BusyWait

void T6963_WriteCommand(unsigned char cmd)
{

	T6963_BusyWait();

		T6963_DB_WR(cmd);

		T6963_WR(LOW);
		T6963_CE(LOW);

		
		T6963_delay();

		T6963_CE(HIGH);
		T6963_WR(HIGH);

}	//T6963_WriteCommand

unsigned char T6963_ReadData(void)
{
	unsigned char 			dat;
	
	T6963_BusyWait();
	
		T6963_DB_IN();

		T6963_CD(LOW);
		T6963_RD(LOW);
		T6963_CE(LOW);
		
		T6963_delay();
		dat = T6963_DB_RD();
		
		T6963_CE(HIGH);
		T6963_RD(HIGH);
		T6963_CD(HIGH);
		T6963_DB_OUT();

	return dat;
}	//T6963_ReadData

void T6963_WriteData(unsigned char dta)
{
	T6963_BusyWait();

		T6963_DB_WR(dta);

		T6963_CD(LOW);
		T6963_WR(LOW);
		T6963_CE(LOW);
		
		T6963_delay();

		T6963_CE(HIGH);
		T6963_WR(HIGH);
		T6963_CD(HIGH);

}	//T6963_WriteData

void T6963_SetAddressPointer(unsigned int addr)								// Set address pointer for display RAM memory
{
	T6963_WriteData(addr &0xFF);
	T6963_WriteData(addr >>8);
	T6963_WriteCommand(T6963_SET_ADDRESS_POINTER);
}	//T6963_SetAddressPointer

void T6963_WriteDisplayData(unsigned char x)									// Writes display data and increment address pointer
{
	T6963_WriteData(x);
	T6963_WriteCommand(T6963_DATA_WRITE_AND_INCREMENT);
}	//T6963_WriteDisplayData


//-------------------------------------------------
//-------------------------------------------------
void T6963_Initalize(void)																		// Display initalization
{
	T6963_Init_Port();

	T6963_RST(LOW);
	HAL_Delay(5);
	T6963_RST(HIGH);

	#if (T6963_FONT_WIDTH == 8)
		T6963_FS(LOW);
	#endif

	//----------------
	T6963_WriteData(T6963_GRAPHIC_HOME &0xFF);
	T6963_WriteData(T6963_GRAPHIC_HOME >>8);
	T6963_WriteCommand(T6963_SET_GRAPHIC_HOME_ADDRESS);

	T6963_WriteData(T6963_GRAPHIC_AREA);
	T6963_WriteData(0x00);
	T6963_WriteCommand(T6963_SET_GRAPHIC_AREA);

	T6963_WriteData(T6963_TEXT_HOME);
	T6963_WriteData(T6963_TEXT_HOME >>8);
	T6963_WriteCommand(T6963_SET_TEXT_HOME_ADDRESS);

	T6963_WriteData(T6963_TEXT_AREA);
	T6963_WriteData(0x00);
	T6963_WriteCommand(T6963_SET_TEXT_AREA);

	T6963_WriteData(T6963_OFFSET_REGISTER);
	T6963_WriteData(0x00);
	T6963_WriteCommand(T6963_SET_OFFSET_REGISTER);

	T6963_WriteCommand( T6963_DISPLAY_MODE | T6963_GRAPHIC_DISPLAY_ON |	T6963_TEXT_DISPLAY_ON );
										  //| T6963_CURSOR_DISPLAY_ON

	T6963_WriteCommand(T6963_MODE_SET | 0x00);
}	//T6963_Initalize


//-------------------------------------------------
void T6963_Backlight(unsigned char x)													// GLCD backlight ON/OFF
{
	T6963_BKL(x);
}	//T6963_Backlight


//-------------------------------------------------
//-------------------------------------------------
void T6963_ClearCG(void)																			// Clear characters generator area of display RAM memory
{
	unsigned int 			i;

	T6963_SetAddressPointer(T6963_EXTERNAL_CG_HOME);

	for(i=0; i<256 *8; i++)				T6963_WriteDisplayData(0x00);
}	//T6963_ClearCG

void T6963_ClearText(void)																		// Clear text area of display RAM memory
{
	unsigned int			i;
	
	T6963_SetAddressPointer(T6963_TEXT_HOME);
	
	for(i=0; i<T6963_TEXT_SIZE; i++)				T6963_WriteDisplayData(0x00);
}	//T6963_ClearText

void T6963_ClearGraphic(void)																	// Clear graphics area of display RAM memory
{
	unsigned int 			i;

	T6963_SetAddressPointer(T6963_GRAPHIC_HOME);
	
	for(i=0; i<T6963_GRAPHIC_SIZE; i++)				T6963_WriteDisplayData(0x00);
}	//T6963_ClearGraphic

void T6963_CLS(void)																					// Clear all area of display RAM memory
{
	T6963_ClearCG();
	T6963_ClearText();
	T6963_ClearGraphic();
}	//T6963_CLS


//-------------------------------------------------
void T6963_TextGoTo(unsigned char x, unsigned char y)					// Set display coordinates
{
	unsigned int 				addr;

	addr = T6963_TEXT_HOME +x +(T6963_TEXT_AREA *y);
	T6963_SetAddressPointer(addr);
}	//T6963_TextGoTo

void T6963_GraphicGoTo(unsigned char x, unsigned char y)			// Set graphic coordinates
{
	unsigned int 				addr;
	
	addr = T6963_GRAPHIC_HOME +(x /T6963_FONT_WIDTH) +(T6963_GRAPHIC_AREA *y);
	T6963_SetAddressPointer(addr);
}	//T6963_GraphicGoTo


//-------------------------------------------------
void T6963_PutChar(char chr)																	// Write a single character (ASCII code) to display RAM memory
{
	T6963_WriteDisplayData(chr -32);
}	//T6963_PutChar

void T6963_PutString(char *str)																// Write null-terminated string to display RAM memory
{
	while(*str++)				T6963_PutChar(*str);
}	//T6963_PutString

void T6963_PutStringf(const char *str)											// Write null-terminated string from program memory to display RAM memory
{
	
	while(*str++)				T6963_PutChar(*str);
}	//T6963_PutStringflash

void T6963_DefineCharacter(unsigned char charCode, unsigned char *defChar)				// Write single char pattern to character generator area of display RAM memory
{
	unsigned int 				addr;
	unsigned char 			i; 

	addr = T6963_EXTERNAL_CG_HOME +(8 *charCode);
	T6963_SetAddressPointer(addr);

	for(i=0; i<8 ; i++)			T6963_WriteDisplayData(*(defChar +i));
}	//T6963_DefineCharacter


//-------------------------------------------------
void T6963_SetPixel(unsigned char x, unsigned char y, T6963_Color color)					// Set a pixel on screen (color: BLACK or WHITE)
{
	unsigned char				dta;
	unsigned int 				addr;

	addr = T6963_GRAPHIC_HOME +(x /T6963_FONT_WIDTH) +(T6963_GRAPHIC_AREA *y);
	T6963_SetAddressPointer(addr);

	T6963_WriteCommand(T6963_DATA_READ_AND_NONVARIABLE);
	dta = T6963_ReadData();

	if(color)		dta |=  (1 <<(T6963_FONT_WIDTH -1 -(x %T6963_FONT_WIDTH)));			// BLACK (set dot)
	else				dta &= ~(1 <<(T6963_FONT_WIDTH -1 -(x %T6963_FONT_WIDTH)));			// WHITE (clear dot)

	T6963_WriteDisplayData(dta);
}	//T6963_SetPixel

void T6963_Line(int X1, int Y1,int X2,int Y2, T6963_Color color)
{
	int						Dx, Dy;
	int						TwoDx, TwoDy;
	int 					CurrentX, CurrentY;
	int						Xinc, Yinc;
	int						TwoDxAccumulatedError, TwoDyAccumulatedError;

	Dx 				= (X2 -X1);
	Dy 				= (Y2 -Y1);

	TwoDx 		= Dx +Dx;
	TwoDy 		= Dy +Dy;

	CurrentX 	= X1;
	CurrentY 	= Y1;

	Xinc 			= 1;
	Yinc 			= 1;

	//--------------
	if(Dx<0)
  {
  	Xinc 	= -1;
  	Dx 		= -Dx;
  	TwoDx = -TwoDx;
  }

	if(Dy<0)
  {
  	Yinc 	= -1;
  	Dy 		= -Dy;
  	TwoDy	= -TwoDy;
  }

	T6963_SetPixel(X1, Y1, color);

	//--------------
	if((Dx !=0) || (Dy !=0))
  {
  	if(Dy<=Dx)
    { 
    	TwoDxAccumulatedError = 0;
    	
    	do
	  	{
      	CurrentX += Xinc;
      	TwoDxAccumulatedError += TwoDy;
      	
      	if(TwoDxAccumulatedError>Dx)
        {
        	CurrentY += Yinc;
        	TwoDxAccumulatedError -= TwoDx;
        }
       	
       	T6963_SetPixel(CurrentX, CurrentY, color);
      }while (CurrentX !=X2);
    }
   	else
		{
      TwoDyAccumulatedError = 0; 
      
      do 
	    {
        CurrentY += Yinc; 
        TwoDyAccumulatedError += TwoDx;
        
        if(TwoDyAccumulatedError>Dy) 
        {
        	CurrentX += Xinc;
        	TwoDyAccumulatedError -= TwoDy;
        }
         
         T6963_SetPixel(CurrentX, CurrentY, color); 
			}while (CurrentY !=Y2);
    }
  }
}	//T6963_Line

void T6963_FillRect(int X1, int Y1,int X2,int Y2, T6963_Color color)
{
	unsigned char				dta;
	unsigned int 				xx, yy;

	for(yy=Y1; yy<Y2+1; yy++)
	{
		for(xx=X1; xx<X2+1; xx++)
		{
			T6963_GraphicGoTo(xx, yy);

			T6963_WriteCommand(T6963_DATA_READ_AND_NONVARIABLE);
			dta = T6963_ReadData();
		
			if(color)		dta |=  (1 <<(T6963_FONT_WIDTH -1 -(xx %T6963_FONT_WIDTH)));			// BLACK (set dot)
			else				dta &= ~(1 <<(T6963_FONT_WIDTH -1 -(xx %T6963_FONT_WIDTH)));			// WHITE (clear dot)
		
			T6963_WriteDisplayData(dta);			
		}
	}
}	//T6963_FillRect

void T6963_InvertRect(int X1, int Y1,int X2,int Y2)
{
	unsigned char				dta;
	unsigned int 				xx, yy;

	for(yy=Y1; yy<Y2+1; yy++)
	{
		for(xx=X1; xx<X2+1; xx++)
		{
			T6963_GraphicGoTo(xx, yy);

			T6963_WriteCommand(T6963_DATA_READ_AND_NONVARIABLE);
			dta = T6963_ReadData();
		
			dta ^=  (1 <<(T6963_FONT_WIDTH -1 -(xx %T6963_FONT_WIDTH)));
			T6963_WriteDisplayData(dta);
		}
	}
}	//T6963_InvertRect


//-------------------------------------------------
void T6963_DrawBitmap(const unsigned char *bitmap, unsigned char x, unsigned char y, TShow_Mode mode)				// Draw bitmap from program memory
{
	unsigned char 			width, height, header;
	unsigned char 			displayData;

	unsigned char 			xx, yy;
	unsigned char				hh, ww;
	
	unsigned int				xy;

	unsigned char 			dnm, dn;
	unsigned char				xsl, xsr;


  header = (bitmap[0]);
  width  = (bitmap[1]);
  height = (bitmap[2]);

	// Drawing position calculation
	ww = width;
	hh = height;
	
	if((x+ww) > DISPLAY_WIDTH)			ww = DISPLAY_WIDTH  -x;
	if((y+hh) > DISPLAY_HEIGHT) 		hh = DISPLAY_HEIGHT -y;
	
	if(ww %T6963_FONT_WIDTH)				ww = ww /T6963_FONT_WIDTH +1;
	else														ww = ww /T6963_FONT_WIDTH;

	xsr 	= x %T6963_FONT_WIDTH;
	xsl 	= T6963_FONT_WIDTH -xsr;

	// Draw my BMP!
	if(mode != TRANS)				T6963_FillRect(x, y, x +width -1, y +height -1, WHITE);		//no transparent

	for(yy=0; yy<hh; yy++)
	{
		T6963_GraphicGoTo(x, y +yy);
		xy = (unsigned int)(yy)*ww +header;

		dnm = 0x00;
		for(xx=0; xx<ww; xx++)
  	{
			dn  = (bitmap[xy])   >>xsr; 			//n
			displayData = dnm | dn;
			dnm = (bitmap[xy++]) <<xsl; 			//n-1
			
			T6963_WriteCommand(T6963_DATA_READ_AND_NONVARIABLE);
			displayData |= T6963_ReadData();
			
			T6963_WriteDisplayData(displayData);
  	}

		T6963_WriteCommand(T6963_DATA_READ_AND_NONVARIABLE);
		displayData = dnm | T6963_ReadData();

		T6963_WriteDisplayData(displayData);
	}

	if(mode == INVERS)				T6963_InvertRect(x, y, x +width -1, y +height -1);			//invers color
}	//T6963_DrawBitmap
