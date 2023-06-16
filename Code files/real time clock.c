/*
 * real_time_clock.c
 *
 * Created: 9/12/2022 11:56:07 PM
 *  Author: HP.SXH08
 */ 


#include <avr/io.h>
#include "avr/interrupt.h"
#include "timer.h"
#include "seven segment.h"
#include "std_macros.h"
#include "LCD.h"
#include "LCD_config.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "keypad_driver.h"

volatile unsigned char sec=0; 
volatile unsigned char min=0; 
volatile unsigned char hour=0; 
char value,h1,h2,m1,m2,s1,s2;
int main(void)
{
	LCD_vInit();
	keypad_vInit();
	seven_seg_vinit('B');
	SET_BIT(DDRC,0);
	SET_BIT(DDRC,1);
	SET_BIT(DDRC,2);
	SET_BIT(DDRC,3);
	SET_BIT(DDRC,4);
	SET_BIT(DDRC,5);
	LCD_vSend_string("press 1 to");
	LCD_movecursor(2,1);
	LCD_vSend_string("set clock");
	timer2_OVF_init();
	
    while(1)
    {
		value=keypad_u8check_press();
		if(value==NOTPRESSED)
		{
			CLR_BIT(PORTC,0);
			SET_BIT(PORTC,1);
			SET_BIT(PORTC,2);
			SET_BIT(PORTC,3);
			SET_BIT(PORTC,4);
			SET_BIT(PORTC,5);
			seven_seg_write('B',(sec%10));
			_delay_ms(5);
			
			
			SET_BIT(PORTC,0);
			CLR_BIT(PORTC,1);
			SET_BIT(PORTC,2);
			SET_BIT(PORTC,3);
			SET_BIT(PORTC,4);
			SET_BIT(PORTC,5);
			seven_seg_write('B',(sec/10));
			_delay_ms(5);
			
			SET_BIT(PORTC,0);
			SET_BIT(PORTC,1);
			CLR_BIT(PORTC,2);
			SET_BIT(PORTC,3);
			SET_BIT(PORTC,4);
			SET_BIT(PORTC,5);
			seven_seg_write('B',(min%10));
			_delay_ms(5);
			
			SET_BIT(PORTC,0);
			SET_BIT(PORTC,1);
			SET_BIT(PORTC,2);
			CLR_BIT(PORTC,3);
			SET_BIT(PORTC,4);
			SET_BIT(PORTC,5);
			seven_seg_write('B',(min/10));
			_delay_ms(5);
			
			SET_BIT(PORTC,0);
			SET_BIT(PORTC,1);
			SET_BIT(PORTC,2);
			SET_BIT(PORTC,3);
			CLR_BIT(PORTC,4);
			SET_BIT(PORTC,5);
			seven_seg_write('B',(hour%10));
			_delay_ms(5);
			
			SET_BIT(PORTC,0);
			SET_BIT(PORTC,1);
			SET_BIT(PORTC,2);
			SET_BIT(PORTC,3);
			SET_BIT(PORTC,4);
			CLR_BIT(PORTC,5);
			seven_seg_write('B',(hour/10));
			_delay_ms(5);
		}
		else if(value!='1')
		{
			LCD_clearscreen();
			LCD_movecursor(1,5);
			LCD_vSend_string("wrong answer");
			_delay_ms(2000);
			LCD_clearscreen();
			LCD_vSend_string("press 1 to");
			LCD_movecursor(2,1);
			LCD_vSend_string("set clock");
		}
		else if(value=='1')
		{
			LCD_clearscreen();
			LCD_vSend_string("hours:--");
			LCD_movecursor(1,7);
			_delay_ms(500);
			while(keypad_u8check_press()==NOTPRESSED);
			h1=keypad_u8check_press();
			LCD_vSend_char(h1);
			_delay_ms(300);
			while(keypad_u8check_press()==NOTPRESSED);
			h2=keypad_u8check_press();
			LCD_vSend_char(h2);
			_delay_ms(300);
			hour=(h1-48)*10+(h2-48);
			
			LCD_clearscreen();
			LCD_vSend_string("minutes:--");
			LCD_movecursor(1,9);
			_delay_ms(500);
			while(keypad_u8check_press()==NOTPRESSED);
			m1=keypad_u8check_press();
			LCD_vSend_char(m1);
			_delay_ms(300);
			while(keypad_u8check_press()==NOTPRESSED);
			m2=keypad_u8check_press();
			LCD_vSend_char(m2);
			_delay_ms(300);
			min=(m1-48)*10+(m2-48);
			
			LCD_clearscreen();
			LCD_vSend_string("secs:--");
			LCD_movecursor(1,6);
			_delay_ms(500);
			while(keypad_u8check_press()==NOTPRESSED);
			s1=keypad_u8check_press();
			LCD_vSend_char(s1);
			_delay_ms(300);
			while(keypad_u8check_press()==NOTPRESSED);
			s2=keypad_u8check_press();
			LCD_vSend_char(s2);
			_delay_ms(300);
			sec=(s1-48)*10+(s2-48);
			
			LCD_clearscreen();
			LCD_vSend_string("press 1 to");
			LCD_movecursor(2,1);
			LCD_vSend_string("set clock");
		}						
				
    }
}

ISR(TIMER2_OVF_vect)
{
	sec++;
	if(sec==60)
	{
		sec=0;
		min++;
	}
	
	if(min==60)
	{
		min=0;
		hour++;
	}
	
	if(hour==24)
	{
		hour=0;
	}
}