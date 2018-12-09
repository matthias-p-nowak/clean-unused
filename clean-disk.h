#ifndef CLEAN_DISK_H
#define CLEAN_DISK_H


#include <cstdlib>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>


#include "cl-obj.h"

#define UNREACHED fprintf(stderr,"REACHED:%s:%d\n",__FILE__,__LINE__);

struct _global{
  std::shared_ptr<ClObj> old;
  struct timespec cutOff;
  int maxFiles;
};

extern _global _glob;

#endif
