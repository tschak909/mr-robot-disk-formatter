/**
 * Boot sector routines
 */

#include <6502.h>
#include <atari.h>
#include <_atarios.h>
#include <string.h>
#include "bootsect.h"

const unsigned char bootsects[3][128] =
  {
   {
    0x00, 0x03, 0x00, 0x07, 0x40, 0x15, 0x4c, 0x14, 0x07, 0x03, 0x03, 0x00,
    0x7c, 0x1a, 0x01, 0x04, 0x00, 0x7d, 0xcb, 0x07, 0xac, 0x0e, 0x07, 0xf0,
    0x36, 0xad, 0x12, 0x07, 0x85, 0x43, 0x8d, 0x04, 0x03, 0xad, 0x13, 0x07,
    0x85, 0x44, 0x8d, 0x05, 0x03, 0xad, 0x10, 0x07, 0xac, 0x0f, 0x07, 0x18,
    0xae, 0x0e, 0x07, 0x20, 0x6c, 0x07, 0x30, 0x17, 0xac, 0x11, 0x07, 0xb1,
    0x43, 0x29, 0x03, 0x48, 0xc8, 0x11, 0x43, 0xf0, 0x0e, 0xb1, 0x43, 0xa8,
    0x20, 0x57, 0x07, 0x68, 0x4c, 0x2f, 0x07, 0xa9, 0xc0, 0xd0, 0x01, 0x68,
    0x0a, 0xa8, 0x60, 0x18, 0xa5, 0x43, 0x6d, 0x11, 0x07, 0x8d, 0x04, 0x03,
    0x85, 0x43, 0xa5, 0x44, 0x69, 0x00, 0x8d, 0x05, 0x03, 0x85, 0x44, 0x60,
    0x8d, 0x0b, 0x03, 0x8c, 0x0a, 0x03, 0xa9, 0x52, 0xa0, 0x40, 0x90, 0x04,
    0xa9, 0x57, 0xa0, 0x80, 0x8d, 0x02, 0x03, 0x8c
   },
   {
    0x03, 0x03, 0xa9, 0x31, 0xa0, 0x0f, 0x8d, 0x00, 0x03, 0x8c, 0x06, 0x03,
    0xa9, 0x03, 0x8d, 0xff, 0x12, 0xa9, 0x00, 0xa0, 0x80, 0xca, 0xf0, 0x04,
    0xa9, 0x01, 0xa0, 0x00, 0x8d, 0x09, 0x03, 0x8c, 0x08, 0x03, 0x20, 0x59,
    0xe4, 0x10, 0x1d, 0xce, 0xff, 0x12, 0x30, 0x18, 0xa2, 0x40, 0xa9, 0x52,
    0xcd, 0x02, 0x03, 0xf0, 0x09, 0xa9, 0x21, 0xcd, 0x02, 0x03, 0xf0, 0x02,
    0xa2, 0x80, 0x8e, 0x03, 0x03, 0x4c, 0xa2, 0x07, 0xae, 0x01, 0x13, 0xad,
    0x03, 0x03, 0x60, 0xaa, 0x08, 0x14, 0x0b, 0xbe, 0x0a, 0xcb, 0x09, 0x00,
    0x0b, 0xa6, 0x0b, 0x07, 0x85, 0x44, 0xad, 0x0a, 0x07, 0x8d, 0xd6, 0x12,
    0xad, 0x0c, 0x07, 0x85, 0x43, 0xad, 0x0d, 0x07, 0x85, 0x44, 0xad, 0x0a,
    0x07, 0x8d, 0x0c, 0x13, 0xa2, 0x07, 0x8e, 0x0d, 0x13, 0x0e, 0x0c, 0x13,
    0xb0, 0x0d, 0xa9, 0x00, 0x9d, 0x11, 0x13, 0x9d
   },
   {
    0x29, 0x13, 0x9d, 0x31, 0x13, 0xf0, 0x36, 0xa0, 0x05, 0xa9, 0x00, 0x91,
    0x43, 0xe8, 0x8e, 0x01, 0x03, 0xa9, 0x53, 0x8d, 0x02, 0x03, 0x20, 0x53,
    0xe4, 0xa0, 0x02, 0xad, 0xea, 0x02, 0x29, 0x20, 0xd0, 0x01, 0x88, 0x98,
    0xae, 0x0d, 0x13, 0x9d, 0x11, 0x13, 0xa5, 0x43, 0x9d, 0x29, 0x13, 0xa5,
    0x44, 0x9d, 0x31, 0x13, 0x20, 0x70, 0x08, 0x88, 0xf0, 0x03, 0x20, 0x70,
    0x08, 0xca, 0x10, 0xb2, 0xac, 0x09, 0x07, 0xa2, 0x00, 0xa9, 0x00, 0x88,
    0x10, 0x01, 0x98, 0x9d, 0x19, 0x13, 0x98, 0x30, 0x0d, 0xa5, 0x43, 0x9d,
    0x39, 0x13, 0xa5, 0x44, 0x9d, 0x49, 0x13, 0x20, 0x70, 0x08, 0xe8, 0xe0,
    0x10, 0xd0, 0xe2, 0xa5, 0x43, 0x8d, 0xe7, 0x02, 0xa5, 0x44, 0x8d, 0xe8,
    0x02, 0x4c, 0x7e, 0x08, 0x18, 0xa5, 0x43, 0x69, 0x80, 0x85, 0x43, 0xa5,
    0x44, 0x69, 0x00, 0x85, 0x44, 0x60, 0xa0, 0x7f
   }
  };

void bootsect_write(unsigned char drive_num)
{
  struct regs r;
  unsigned char i;

  // Write boot sectors to disk
  OS.dcb.ddevic=0x30; // Disk drive
  OS.dcb.dunit=drive_num;
  OS.dcb.dcomnd='P'; // Write, no verify
  OS.dcb.dtimlo=0x0F; // Default timeout
  OS.dcb.dstats=0x80; // Write

  for (i=0;i<3;i++)
    {
      OS.dcb.daux=1+i;    // Directory sector
      OS.dcb.dbuf=&bootsects[i];
      r.pc=0xE453; // DSKINV
      _sys(&r);
    }
  
}

#include "bootsect.h"

