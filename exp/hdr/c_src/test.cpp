#include <iostream>
#include <stdlib.h>
#include <stdio.h>

short sqrt_t[]={0,
  128,
  181,
  221,
  256,
  286,
  313,
  338,

  0,
  362,
  512,
  627,
  724,
  809,
  886,
  957,

  0,
  1024,
  1448,
  1773,
  2048,
  2289,
  2508,
  2709,

  0,
  2048,
  2896,
  3547,
  4096,
  4579,
  5016,
  5418};
short exp_t[]={
  8192,
  7695,
  7229,
  6791,
  6379,
  5993,
  5630,
  5289,
  4968,
  4667,
  4384,
  4119,
  3869,
  3635,
  3414,
  3208,
  3013,
  2831,
  2659,
  2498,
  2347,
  2204,
  2071,
  1945,
  1827,
  1717,
  1613,
  1515,
  1423,
  1337,
  1256,
  1180,
  1108,
  1041,
  978,
  919,
  863,
  811,
  761,
  715,
  672,
  631,
  593,
  557,
  523,
  491,
  462,
  434,
  407,
  383,
  359,
  338,
  317,
  298,
  280,
  263,
  247,
  232,
  218,
  205,
  192,
  180,
  170,
  159};

#define MIN(A,B) ((A>B) ? B : A)
#define ROW 8
#define COL 8
void computeWeightRGB_fxp(short ret[ROW][COL], short R[ROW][COL],short G[ROW][COL], short B[ROW][COL], short tmp[ROW][COL], short sqrt_t[64], short exp_t[64],short row, short col);
// extern "C" double getTicks();
// extern "C" double getEnergy();
// extern "C" void resetTicks();
// extern "C" void resetEnergy();
FILE* fout;
#include <iostream>
using namespace std;
int main(int argc, char** argv)
{
  //  FILE* input=fopen("/home/polaris/dlee/aspdac/hdr/hls/src/test_data1","r");
  int count=0;
  //FILE* input=fopen("small_house_data","r");
  FILE* input=fopen(argv[1],"r");
  fout=fopen(argv[2],"w");
  printf("%s %s %s\n", argv[0], argv[1], argv[2]);
  if(input ==0)
  {
    fprintf(stderr, "Cannot find file %s\n", argv[1]);
    return 0;
  }
  if(fout ==0)
  {
    fprintf(stderr, "Cannot find file %s\n", argv[2]);
    return 0;
  }
  short R[ROW][COL];
  short G[ROW][COL];
  short B[ROW][COL];
  short ret[ROW][COL];
  short refret[ROW][COL];
  short tmp[ROW][COL];
  int r,g,b;
  int rt;
  int tot_row=atoi(argv[3]);
  int tot_col=atoi(argv[4]);
  for(int m=0; m<4; m++){
    for(int i=0; i<tot_col; i+=8)
    {
      for(int j=0; j<tot_row; j+=8)
      {
        for(int k=0; k<(ROW); k++)
        {
          for(int l=0;l<(COL ); l++)
          {
            fscanf(input, "%d,%d,%d,%d\n", &r,&g,&b,&rt);
            R[k][l]=r;
            G[k][l]=g;
            B[k][l]=b;
            refret[k][l]=rt;
          }
        }
        int k_min=MIN(ROW,tot_col-i);
        int l_min=MIN(COL,tot_row-j);
        computeWeightRGB_fxp(ret, R,G,B,tmp,sqrt_t,exp_t,k_min,l_min);
        count++;
        //cout<<getTicks()<<" "<<getEnergy()<<endl;
        //    resetTicks();
        //    resetEnergy();
        for(int k=0; k<(ROW); k++)
        {
          for(int l=0;l<(COL ); l++)
          {
            if(refret[k][l]!=ret[k][l])
            {
              std::cout<<"err: "<<k<<" "<<l<<" "<<ret[k][l]<<" "<<refret[k][l]<<std::endl;
            }
          }
        }
      }
    }
  }
  printf("%d\n",count);
  fclose(input);
  return 0;
}
