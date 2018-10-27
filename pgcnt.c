#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int c1;
  
  c1 = pgcnt();

  printf(1, "%d\n", c1);

  exit();
}