/**
 * Mr. Robot Disk formatter
 */

#include <atari.h>
#include "charset.h"
#include "ui.h"

void main(void)
{
  /* _graphics(0); */
  __asm__("JSR $E450");
  charset_use();
  ui_run(1);
  /* format_disk(2); */
  /* bootsect_write(2); */
  /* vtoc_write(2); */
  /* directory_write(2); */
}
