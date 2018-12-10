#include "clean-disk.h"

using namespace std;


class ClObj {
public:
  string name;
  time_t atime;
  shared_ptr<ClObj> next;
public:
  ClObj(char *path, time_t at):
    name(path),atime(at) {};
};

shared_ptr<ClObj> chain;

time_t rec_oldest=time(NULL);
const int binCnt=2000;
int bins[binCnt];
int files=0;


int getBin(time_t atime){
   int bin=(atime-_glob.oldest)*binCnt/(_glob.cutOff-_glob.oldest);
  if(bin<0)
    bin=0;
  if(bin>=binCnt)
    bin=binCnt;
  return bin;
}

void checkMem(bool forced=false) {
  static int ignores=0;
  if(!forced && (++ignores > 1))
    return; // not doing a check each time
  ignores=0;
  long am=sysconf(_SC_AVPHYS_PAGES);
  if(am<1000) {
    if(_glob.verbose>2)
      cout << "memory shortage" << endl;
    _glob.maxFiles=files/2;
  }
  if(!forced && (files<_glob.maxFiles))
    return;
  int i=0,n=0;
  for(i=0; i<binCnt; ++i) {
    n+=bins[i];
    if(n>_glob.maxFiles)
      break;
  }
  ++i;
  auto nc=i*(_glob.cutOff-_glob.oldest)/binCnt+_glob.oldest;
  _glob.cutOff=nc;
  if(rec_oldest>=nc)
    rec_oldest=nc-3600;
  _glob.oldest=rec_oldest;
  memset(bins,0,sizeof(bins));
  files=0;
  while((chain!=nullptr) &&(chain->atime>_glob.cutOff))
    chain=chain->next;
  shared_ptr<ClObj> p=chain;
  while(p!=nullptr){
    ++bins[getBin(p->atime)];
    ++files;
    while((p->next != nullptr)&&(p->next->atime >_glob.cutOff))
      p->next=p->next->next;
    p=p->next;
  }
}

void record(char *path, time_t atime) {
  if(atime<rec_oldest)
    rec_oldest=atime;
  int bin=getBin(atime);
  ++bins[bin];
  ++files;
  shared_ptr<ClObj> old=chain;
  chain=make_shared<ClObj>(path,atime);
  chain->next=old;
  checkMem();
}

void removeFiles(){
  checkMem(true);
  // checkMem(true);
  // checkMem(true);
  int i,n=0;
  for(i=0; i<binCnt; ++i) {
    n+=bins[i];
    if(n>_glob.maxFiles)
      break;
  }
  auto maxAge=i*(_glob.cutOff-_glob.oldest)/binCnt+_glob.oldest;
  while(chain!=nullptr){
    if(chain->atime < maxAge){
      if(_glob.verbose>2)
        cout << "removing "<< chain->name << endl;
      if(unlink(chain->name.c_str())){
        perror("unlinking old files");
      }
    }
    chain=chain->next;
  }
}
