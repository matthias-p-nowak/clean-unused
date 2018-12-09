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
  int n,r;
  char indicator;
  while ((opt = getopt(argc, argv, "vn:t:")) != -1) {
    switch (opt) {
      case 'v':
      UNREACHED
      break;
    case 'n':
      UNREACHED
      n=atoi(optarg);
      if(n>0)
        _glob.maxFiles=n;
      else{
        printf("the number of files to delete must be positive\n");
        print_usage(argv[0]);
      }
      break;
    case 't':
      UNREACHED
      r=sscanf(optarg,"%d%c",&n,&indicator);
      if(r==2){
        if(n<=0){
          printf("number of time units must be positive\n");
          print_usage(argv[0]);
        }
        switch(indicator){
          case 'h':
            n*=3600;
          break;
          case 'd':
            n*=3600*24;
            break;
          case 'w':
            n*=3600*24*7;
            break;
          case 'm':
            n*=3600*24*30;
            break;
          case 'y':
            n*=3600*24*365;
            break;
          default:
           printf("time unit must be one of h/d/w/m/y\n");
           print_usage(argv[0]);
           break;
        }
        
      }else{
        printf("the time argument needs a number followed by a character\n");
        print_usage(argv[0]);
      }
      break;
    default:
      UNREACHED
      print_usage(argv[0]);
      break;
    }
  UNREACHED
  }
   long am=sysconf(_SC_AVPHYS_PAGES);
   long ps=sysconf(_SC_PAGESIZE);
  cout << "got "<< am << " as memory"<<endl;
  

  return 0;
}
