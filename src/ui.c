/**
 * User Interface functions
 */

#include <atari.h>
#include <conio.h>
#include <peekpoke.h>
#include <string.h>
#include <stdlib.h>
#include "format.h"
#include "bootsect.h"
#include "vtoc.h"
#include "directory.h"

static unsigned char* dlist_ptr;
static unsigned char* video_ptr;
static unsigned short screen_memory;
extern unsigned char drive_num;

#define SetChar(x,y,a) video_ptr[(x)+(y)*40]=(a);
#define GetChar(x,y) video_ptr[(x)+(y)*40]
#define GRAPHICS_0_SCREEN_SIZE (40*25)

void clear_screen()
{
  memset(video_ptr,0,GRAPHICS_0_SCREEN_SIZE);
}

void print_string(unsigned char x,unsigned char y,char *s)
{
  do
    {
      if (*s < 32)
	{
	  SetChar(x++,y,*s+64);
	}
      else if (*s<96)
	{
	  SetChar(x++,y,*s-32);
	}
      else
	{
	  SetChar(x++,y,*s);
	}
      ++s;
    } while(*s!=0);
}

void get_key(void)
{
  POKE(764,255);
  while (PEEK(764)==0xFF) { }
}

void ui_do_format(unsigned char drive_num)
{
  print_string(0,7,"FORMATTING DISK...");
  format_disk(drive_num);
  print_string(0,8,"WRITING BOOT SECTOR...");
  bootsect_write(drive_num);
  print_string(0,9,"WRITING VTOC...");
  vtoc_write(drive_num);
  print_string(0,10,"WRITING DIRECTORY...");
  directory_write(drive_num);
}

void ui_bye(void)
{
  __asm__("JMP $E477");
}

void ui_run(unsigned char drive_num)
{
  POKE(708,0x5A);
  POKE(709,15);
  POKE(710,144);
  POKE(712,144);
  dlist_ptr=(unsigned char *)(PEEKW(560));
  dlist_ptr[3]=0x46;
  dlist_ptr[6]=0x06;
  screen_memory=PEEKW(560)+4;
  video_ptr=(unsigned char*)(PEEKW(screen_memory));
 rerun:
  clear_screen();
  print_string(0,0,"     MR. ROBOT        DISK FORMATTER");
  print_string(0,2,"\x80\xa5\xb3\xa3\x80 EXITS TO DOS.");
  print_string(0,4,"FORMAT DISK IN DRIVE: ");

  SetChar(23,4,drive_num+16+128);
 get_drive_number:
  get_key();

  switch(PEEK(764))
    {
    case 12:
      drive_num=drive_num;
      break;
    case 28:
      ui_bye();
    case 31:
      drive_num=1;
      break;
    case 30:
      drive_num=2;
      break;
    case 26:
      drive_num=3;
      break;
    case 24:
      drive_num=4;
      break;
    case 29:
      drive_num=5;
      break;
    case 27:
      drive_num=6;
      break;
    case 51:
      drive_num=7;
      break;
    case 53:
      drive_num=8;
      break;
    default:
      goto get_drive_number;
    }

  SetChar(23,4,drive_num+16);

  print_string(0,5,"        ARE YOU SURE?");

  SetChar(23,5,185);

 get_confirmation:
  get_key();

  switch(PEEK(764))
    {
    case 43:
      SetChar(23,5,57);
      ui_do_format(drive_num);
      break;
    case 35:
      SetChar(23,5,46);
      goto do_again;
      break;
    default:
      goto get_confirmation;
    }

 do_again:
  print_string(0,15,"           RUN AGAIN?");

  SetChar(23,15,57+128);

  get_key();
  switch(PEEK(764))
    {
    case 43:
      goto rerun; 
      break;
    }
  ui_bye();
  
}
