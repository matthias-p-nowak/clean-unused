#ifndef CL_OBJ_H
#define CL_OBJ_H

#include <memory>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


class ClObj {
public:
  std::string name;
  struct timespec atime;
  std::shared_ptr<ClObj> next;
public:
  ClObj(char *dir, char *entry, struct timespec &at);
};

#endif
