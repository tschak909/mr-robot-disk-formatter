/**
 * Mr. Robot Disk formatter
 */

#include "format.h"
#include "vtoc.h"

void main(void)
{
  format_disk(2);
  vtoc_write(2);
}
