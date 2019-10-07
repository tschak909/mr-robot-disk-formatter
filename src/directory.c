/**
 * Routine to write DOS 2 directory for Mr. Robot formatted disk
 */

#include <6502.h>
#include <atari.h>
#include <_atarios.h>
#include <string.h>
#include "directory.h"

#define DIR_FLAG 0x42

static DirectoryEntries directory_sector[8];

void directory_write(unsigned char drive_num)
{
  struct regs r;
  unsigned char i;
  memset(&directory_sector,0x00,sizeof(directory_sector));
  strcpy(directory_sector[0][0].filename,"***********");
  strcpy(directory_sector[0][1].filename,"*THIS IS A*");
  strcpy(directory_sector[0][2].filename,"*MR. ROBOT*");
  strcpy(directory_sector[0][3].filename,"* FACTORY *");
  strcpy(directory_sector[0][4].filename,"*  LEVEL  *");
  strcpy(directory_sector[0][5].filename,"*  DISK.  *");
  strcpy(directory_sector[0][6].filename,"***********");

  directory_sector[0][0].flag=DIR_FLAG; // Normal file
  directory_sector[0][0].total_sectors=0;
  directory_sector[0][0].starting_sector=0;

  directory_sector[0][1].flag=DIR_FLAG; // Normal file
  directory_sector[0][1].total_sectors=0;
  directory_sector[0][1].starting_sector=0;

  directory_sector[0][2].flag=DIR_FLAG; // Normal file
  directory_sector[0][2].total_sectors=0;
  directory_sector[0][2].starting_sector=0;

  directory_sector[0][3].flag=DIR_FLAG; // Normal file
  directory_sector[0][3].total_sectors=0;
  directory_sector[0][3].starting_sector=0;

  directory_sector[0][4].flag=DIR_FLAG; // Normal file
  directory_sector[0][4].total_sectors=0;
  directory_sector[0][4].starting_sector=0;

  directory_sector[0][5].flag=DIR_FLAG; // Normal file
  directory_sector[0][5].total_sectors=0;
  directory_sector[0][5].starting_sector=0;

  directory_sector[0][6].flag=DIR_FLAG; // Normal file
  directory_sector[0][6].total_sectors=0;
  directory_sector[0][6].starting_sector=0;

  // Write directory to disk
  OS.dcb.ddevic=0x30; // Disk drive
  OS.dcb.dunit=drive_num;
  OS.dcb.dcomnd='P'; // Write, no verify
  OS.dcb.dtimlo=0x0F; // Default timeout
  OS.dcb.dstats=0x80; // Write

  for (i=0;i<8;i++)
    {
      OS.dcb.daux=361+i;    // Directory sector
      OS.dcb.dbuf=&directory_sector[i];
      r.pc=0xE453; // DSKINV
      _sys(&r);
    }
}
