#include "clean-disk.h"

using namespace std;

char path[PATH_MAX];

char *combine(char *dir, char *entry){
  snprintf(path,PATH_MAX,"%s/%s",dir,entry);
  return path;
}

ClObj::ClObj(char *dir, char *entry,struct timespec &at):
  name(combine(dir,entry)),
  atime(at)
{
  cout << "constructing" << endl;
}
