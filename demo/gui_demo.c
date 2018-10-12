#include "ugui.h"
#include "ugui_config.h"

extern UG_RESULT _HW_DrawLine( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c );
extern UG_RESULT _HW_FillFrame( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c );
extern void _HW_DrawPoint(UG_S16 x, UG_S16 y, UG_COLOR c);
extern void *_HW_FillAREA( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2);

UG_GUI gui;
/* Window 1 */
UG_WINDOW window_1;
UG_OBJECT obj_buff_wnd_1[10];
UG_BUTTON button1_1;
UG_BUTTON button1_2;
UG_BUTTON button1_3;
UG_BUTTON button1_4;
UG_BUTTON button1_5;
UG_BUTTON button1_6;

void window_1_callback( UG_MESSAGE* msg )
{
	if ( msg->type == MSG_TYPE_OBJECT )
	{
		
		if (msg->id == OBJ_TYPE_BUTTON ))
		{
			switch( msg->sub_id )
			{
				case BTN_ID_0: 
				{
					UG_ConsolePutString(“0000”);
					 break;
				}				
				case BTN_ID_1: 
				{
					UG_ConsolePutString(“1111”);
					 break;
				}					
				
			}
			
		}	
	}
}
#define LCD_W 320
#define LCD_H 240

int main()
{
	int keyvalue;
	struct tpdev_typedef tp_dev;
	
	UG_Init(&gui,(void(*)(UG_S16,UG_S16,UG_COLOR))_HW_DrawPoint,LCD_W,LCD_H);
	UG_FontSelect(&FONT_8X14);
	UG_HZFontSelect(&FONT_HANZI_32);//Chinese Font select
	UG_DriverRegister(DRIVER_DRAW_LINE,_HW_DrawLine);
	UG_DriverRegister(DRIVER_FILL_FRAME,_HW_FillFrame);
	UG_DriverRegister(DRIVER_FILL_AREA,_HW_FillAREA);
	UG_FillScreen( C_BLACK );
	
//	/* Create Window 1 */
	UG_WindowCreate( &window_1, obj_buff_wnd_1, 10, window_1_callback );
	UG_WindowSetTitleText( &window_1, "STM32F1 PLATFORM" );
	UG_WindowSetTitleTextFont( &window_1, &FONT_12X20 );
//	/* Create some Buttons */
	UG_ButtonCreate( &window_1, &button1_1, BTN_ID_0, 10, 10, 120, 60 );
	UG_ButtonCreate( &window_1, &button1_2, BTN_ID_1, 10, 70, 120, 120 );	

	// Configure Button 1 
	UG_ButtonSetFont( &window_1, BTN_ID_0, &FONT_12X20 );
	UG_ButtonSetBackColor( &window_1, BTN_ID_0, C_ALICE_BLUE );
	UG_ButtonSetText( &window_1, BTN_ID_0, "PLAY" );
	// Configure Button 2 
	UG_ButtonSetFont( &window_1, BTN_ID_1, &FONT_12X20 );
	UG_ButtonSetBackColor( &window_1, BTN_ID_1, C_GREEN );
	UG_ButtonSetText( &window_1, BTN_ID_1, "PREV" );	
	//show window1: flag
	UG_WindowShow( &window_1 );
	//Configure Console window
	UG_ConsoleSetArea(0,UG_WindowGetInnerHeight(&window_1)-80,UG_WindowGetXEnd(&window_1),UG_WindowGetYEnd(&window_1));
	UG_ConsoleSetForecolor(C_GREEN_YELLOW);
	UG_ConsoleSetBackcolor(C_BLACK);	
	
	while(1)
	{
		UG_Update();	//Windows Refresh
		
		if(keyscan(keyvalue))//KEY BOARD
		{
			switch(keyvalue)
			{
				case 1:
				UG_Button_CLICK(&window_1,BTN_ID_0);
				break;
				
				case 2:
				UG_Button_CLICK(&window_1,BTN_ID_1);
				break;	
			}
				
		}
		if(touch_scan(tp_dev))//Touch Screen
		{
			if(tp_dev.x<LCD_W&&tp_dev.y<LCD_H)
			{
				UG_TouchUpdate(tp_dev.x,tp_dev.y,TOUCH_STATE_PRESSED);
			}
		}
		else
		{
			UG_TouchUpdate(-1,-1,TOUCH_STATE_RELEASED);	
		}
	}
	return 0;
}