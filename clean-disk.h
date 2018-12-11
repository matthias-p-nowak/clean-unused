#ifndef CLEAN_DISK_H
#define CLEAN_DISK_H


#include <cstdlib>
#include <dirent.h>
#include <fcntl.h>      /* Definition of AT_* constants */
#include <iostream>
#include <limits.h>
#include <memory>
#include <proc/readproc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define UNREACHED fprintf(stderr,"REACHED:%s:%d\n",__FILE__,__LINE__);

void housekeeping();
void record(char *path, time_t atime);
void removeFiles();

struct _global{
  time_t cutOff;
  time_t oldest;
  int maxFiles;
  dev_t device;
  int verbose;
  bool removeLinks;
};

extern _global _glob;

#endif
