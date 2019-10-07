/**
 * Routine to write DOS 2 directory for Mr. Robot formatted disk
 */

#ifndef DIRECTORY_H
#define DIRECTORY_H

typedef struct _directory_entry {
  unsigned char flag;
  unsigned short total_sectors;
  unsigned short starting_sector;
  unsigned char filename[11];
} DirectoryEntry;

typedef DirectoryEntry DirectoryEntries[8];

void directory_write(unsigned char drive_num);

#endif /* DIRECTORY_H */
