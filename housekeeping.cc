#include "clean-disk.h"

using namespace std;

void housekeeping(){
  long am=sysconf(_SC_AVPHYS_PAGES);
  long ps=sysconf(_SC_PAGESIZE);
  cout << "got "<< am << " as memory"<<endl;
}
