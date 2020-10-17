#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int v_flag = 0;
  char *s_value = NULL;
  int index;
  int c;

  opterr = 0;

  while ((c = getopt(argc, argv, "vs:")) != -1)
    switch (c)
    {
    case 'v':
      v_flag = 1;
      break;
    case 's':
      s_value = optarg;
      break;
    default:
      abort();
    }

  // printf("v_flag = %d, s_value = %s\n",
  //        v_flag, s_value);
}