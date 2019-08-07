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
  
  string s;
  cin>>s;
  int fd = open("./openssl", O_RDONLY);
  size_t size = lseek(fd, 0, SEEK_END);
  if (size == 0)
    exit(-1);
  size_t map_size = size;
  cout<<map_size<<endl;
  if ((map_size & 0xFFF) != 0)
  {
    map_size |= 0xFFF;
    map_size += 1;
  }
  base = (char*) mmap(NULL, map_size, PROT_READ, MAP_SHARED, fd, 0);
  ending = base + size;

  char* sqrProbe = base + 0x4d78c0;
  char* mulProbe = base + 0x4d7360;
  long long int i=0;
  int count = 0;
  for(int i=0;i<s.length();i++)
    if(s[i]=='1')
      count++;
  for(int i=0;i<s.length();i++)
  {
    sleep(0.1);
    if(s[i]=='1')
    {
      maccess(sqrProbe);
      maccess(mulProbe);
    }
    else
    {
      maccess(sqrProbe);
    }
  }

  cout << count<<endl;
  // while(i < 1000)
  // {
  //   sleep(0.1);
  //   long long int j=0;
  //   maccess(sqrProbe);
  //   i++;
  // }

  close(fd);
  munmap(base, map_size);
  fflush(stdout);
  return 0;
}

