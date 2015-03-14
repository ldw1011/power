#include "testvector.h"
#include "golden.h"
#include <stdio.h>
#include <stdlib.h>
void dct(char indata[64], short outdata[64], short buf[64]);
FILE* outfile;
int main(int argc, char** argv)
{
  char indata[64];
  short outdata[64];
  short buf[64];
  short ref[64];
  char* testvector;
  short* golden;
  int total=0;
  if(argv[1][0]=='r')
  {
    total=roki_total;
    golden=roki_golden;
    testvector=roki_testvector;
  }
  else if(argv[1][0]=='a')
  {
    total=      audi_total;
    golden=     audi_golden;
    testvector= audi_testvector;
  }
  else if(argv[1][0]=='l')
  {
    total=      lena_total;
    golden=     lena_golden;
    testvector= lena_testvector;
  }
  outfile=fopen(argv[2],"w");
  if(outfile==0)
  {
    fprintf(stderr,"cannot create file %s\n",argv[2]);
    exit(2);
  }
  for(int i=0; i<total; i+=64)
  {
    for(int j=0; j<64; j++)
    {
      indata[j]=testvector[i+j];
      ref[j]=golden[i+j];
      fprintf(outfile,"%d ",indata[j]);
    }
    dct(indata, outdata, buf);
    for(int j=0; j<64; j++)
    {
      if(outdata[j]!=ref[j])
      {
        printf("error %d\n",i);
      }
      fprintf(outfile,"%d ",outdata[j]);
    }
    fprintf(outfile,"\n");

  }
  fclose(outfile);
  return 0;
}
