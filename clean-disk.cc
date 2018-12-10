#include "clean-disk.h"

using namespace std;

void print_usage(char *progname) {
  printf("Clean the disk\n"
         "usage: %s\n"
         ,progname);
  exit(EXIT_SUCCESS);
}

struct _global _glob;

void checkDir(char *dirName) {
  DIR *d=opendir(dirName);
  if(d==NULL)
    return; // couldn't open that directory
  int fd=dirfd(d);
  struct dirent *dirent;
  struct stat statbuf;
  char path[PATH_MAX];
  if(_glob.verbose>1)
    cout << "checking content of dir: " << dirName <<endl;
  while(dirent=readdir(d)) {
    // going through the entries
    if(!strcmp(dirent->d_name,".")||(!strcmp(dirent->d_name,"..")))
      continue;
    if(!fstatat(fd,dirent->d_name,&statbuf, AT_SYMLINK_NOFOLLOW)) {
      if(statbuf.st_dev!=_glob.device)
        continue;
      snprintf(path,PATH_MAX,"%s/%s",dirName,dirent->d_name);
      if(S_ISLNK(statbuf.st_mode)) {
        if(fstatat(fd,dirent->d_name,&statbuf, 0)) {
          if(_glob.verbose>2)
            cout << dirName << " "<< dirent->d_name << " failed link...?"<< endl;
          // TODO: remove dead symlinks
        }
      }
      if(S_ISDIR(statbuf.st_mode)) {
        checkDir(path);
      } else {
        if(S_ISREG(statbuf.st_mode)) {
          auto t=statbuf.st_atim.tv_sec;
          if(t > _glob.cutOff)
            continue;
          record(path,t);
        }
      }
    }
  }
  closedir(d);
}

int main(int argc, char *argv[]) {
  UNREACHED
  memset(&_glob,0,sizeof(_glob));
  if(argc<2) {
    print_usage(argv[0]);
  }
  int opt;
  int n,r;
  char indicator;
  _glob.cutOff=time(NULL);
  _glob.maxFiles=1e9;
  while ((opt = getopt(argc, argv, "vn:t:")) != -1) {
    switch (opt) {
    case 'v':
      UNREACHED
      ++_glob.verbose;
      break;
    case 'n':
      UNREACHED
      n=atoi(optarg);
      if(n>0)
        _glob.maxFiles=n;
      else {
        printf("the number of files to delete must be positive\n");
        print_usage(argv[0]);
      }
      break;
    case 't':
      UNREACHED
      r=sscanf(optarg,"%d%c",&n,&indicator);
      if(r==2) {
        if(n<=0) {
          printf("number of time units must be positive\n");
          print_usage(argv[0]);
        }
        switch(indicator) {
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
        _glob.cutOff-=n;
      } else {
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
  _glob.oldest=_glob.cutOff-365*24*3600; // 1 year
  for (int i = optind; i < argc; ++i) {
    struct stat statbuf;
    if(!lstat(argv[i],&statbuf)) {
      if(_glob.verbose>0)
        cout << "checking " << argv[i] << endl;
      _glob.device=statbuf.st_dev;
      checkDir(argv[i]);
    }
  }
  cout << "all done" << endl;
  return 0;
}
