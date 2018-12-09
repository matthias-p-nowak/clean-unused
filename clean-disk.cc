#include "clean-disk.h"

using namespace std;

void print_usage(char *progname) {
  printf("Clean the disk\n"
  "usage: %s\n"
  ,progname);
  exit(EXIT_SUCCESS);
}

struct _global _glob;

int main(int argc, char *argv[]) {
  UNREACHED
  memset(&_glob,0,sizeof(_glob));
  if(argc<2) {
    print_usage(argv[0]);
  }
  int opt;
  int n;
  while ((opt = getopt(argc, argv, "vn:t:")) != -1) {
    switch (opt) {
      case 'v':
      UNREACHED
      break;
    case 'n':
      UNREACHED
      n=atoi(optarg);
      
      break;
    case 't':
      UNREACHED
      break;
    default:
      UNREACHED
      print_usage(argv[0]);
      break;
    }
  UNREACHED
  }
  return 0;
}
