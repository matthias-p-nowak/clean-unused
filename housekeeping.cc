#include "clean-disk.h"

using namespace std;


class ClObj {
public:
  string name;
  struct timespec atime;
  shared_ptr<ClObj> next;
public:
  ClObj(char *path, struct timespec &at):
  name(path),atime(at){};
};




void housekeeping(){
  long am=sysconf(_SC_AVPHYS_PAGES);
  long ps=sysconf(_SC_PAGESIZE);
  cout << "got "<< am << " as memory"<<endl;
}
