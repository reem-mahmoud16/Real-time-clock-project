/*
 * seven_segment.c
 *
 * Created: 8/6/2018 10:31:18 PM
 *  Author: Mohamed Zaghlol
 */ 

#include "DIO.h"
void seven_seg_vinit(unsigned char port_name)
{
	DIO_set_port_direction(port_name,0xFF);
}

void seven_seg_write(unsigned char portname,unsigned char number)
{
unsigned char arr[]={ 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x47,0x7f,0x6f};

DIO_write_port(portname,arr[number]);
}