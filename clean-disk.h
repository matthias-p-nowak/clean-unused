#ifndef CLEAN_DISK_H
#define CLEAN_DISK_H


#include <cstdlib>
#include <dirent.h>
#include <fcntl.h>      /* Definition of AT_* constants */
#include <iostream>
#include <limits.h>
#include <memory>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#include "cl-obj.h"

#define UNREACHED fprintf(stderr,"REACHED:%s:%d\n",__FILE__,__LINE__);

void housekeeping();

struct _global{
  std::shared_ptr<ClObj> old;
  time_t cutOff;
  int maxFiles;
  dev_t device;
};

extern _global _glob;

#endif
