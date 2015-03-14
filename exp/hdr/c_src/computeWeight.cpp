#include <iostream>
#include <stdlib.h>
#define ROW 8
#define COL 8
#define FXP_N 13
#define THREE   24579
#define SIG     327
#define COEFF   -4096
#define COEFF_R 1741
#define COEFF_G 5859
#define COEFF_B 591
#define MFOUR   -32768
inline
short sqrt_xp(short t , short table[32])
{
  short idx3= (t>>10) &0x7;
  if(idx3!=0) return table[idx3+24];
  short idx2= (t>>7) &0x7;
  if(idx2!=0) return table[idx2+16];
  short idx1= (t>>4) &0x7;
  if(idx1!=0) return table[idx1+8];
  short idx0= (t>>1) & 0x7;
  if(idx0!=0) return table[idx0];
  return 0;
}
inline
short exp_xp(short t, short table[64])
{
//  std::cout<<(t/(1.0*(1<<13)))<<std::endl;
  if(t>= (4*(1<<13))) return  10;
  return table[(((-t)>>9) & 0x3f)];
}
inline
short MUL(short a, short b)
{
  int ret = a;
  return ((ret*b)>>FXP_N);
}
inline
short DIV(short a, short b)
{
  int ret = a;;
  return (ret<<FXP_N)/b;
}
void computeWeightRGB_fxp(short ret[ROW][COL], short R[ROW][COL],short G[ROW][COL], short B[ROW][COL], short tmp[ROW][COL], short sqrt_t[32], short exp_t[64], short row, short col)
{

  short tmp_gray;
  computeWeightRGB_fxp_label0:for(short i=0; i<ROW; i++)
  {
    for(short j=0; j<COL; j++)
    {
      tmp_gray=MUL(COEFF_R,R[i][j]);
      tmp_gray+=MUL(COEFF_G,G[i][j]);
      tmp_gray+=MUL(COEFF_B,B[i][j]);
      tmp[i][j]=tmp_gray;
 //     std::cout<<"gr: "<<(tmp[i][j])/(1.0*(1<<13))<<std::endl;
    }
  }

  computeWeightRGB_fxp_label2:for(short i=0; i<ROW; i++)
  {

	computeWeightRGB_fxp_label1:for(short j=0; j<COL; j++)
    {
      short c= tmp[i][j];
      short a= ((i>0) ? tmp[i-1][j] : tmp[i][j])-c;
      short b= ((j>0) ? tmp[i][j-1] : tmp[i][j])-c;
      short d= ((j<col-1) ? tmp[i][j+1] : tmp[i][j])-c;
      short e= ((i<row-1) ? tmp[i+1][j] : tmp[i][j])-c;
      short contrast=a+b+d+e; // contrast
      contrast = (contrast<0) ? -contrast: contrast;
//      std::cout<<"gr: "<<(contrast)/(1.0*(1<<13))<<std::endl;
      short mean=((R[i][j] + G[i][j] + B[i][j]))/3;

#define SQ(A) (MUL((A),(A)))
      short saturation  = sqrt_xp( ( SQ(R[i][j]-mean) + SQ(G[i][j]-mean) + SQ(B[i][j]-mean) )/3 , sqrt_t);
//      std::cout<<"gr: "<<(( SQ(R[i][j]-mean) + SQ(G[i][j]-mean) + SQ(B[i][j]-mean) )/3 )/(1.0*(1<<13))<<std::endl;
//      std::cout<<"gr: "<<sqrt_xp(( SQ(R[i][j]-mean) + SQ(G[i][j]-mean) + SQ(B[i][j]-mean) )/3,sqrt_t )/(1.0*(1<<13))<<std::endl;
      short up =  MUL(COEFF , (SQ(R[i][j]+COEFF)+SQ(G[i][j]+COEFF)+SQ(B[i][j]+COEFF)));
      short well_exp;
      if(up> -(1310))
      {
         well_exp  = exp_xp ( up *25 , exp_t);
      }
      else
      {
         well_exp  = 1;
      }
//      std::cout<<"gr: "<<(well_exp)/(1.0*(1<<13))<<std::endl;
      ret[i][j]  =MUL( (MUL(well_exp , saturation)<<3),  contrast);
      if(ret[i][j]==0) ret[i][j]=1;
//      std::cout<<"gr: "<<(contrast)/(1.0*(1<<13))<<" "<<(contrast)/(1.0*(1<<13))<<" "<<(contrast)/(1.0*(1<<13))<<" "<<ret[i][j]<<std::endl;
//      std::cout<<"gr: "<<ret[i][j]<<std::endl;
#undef SQ
    }
  }
  //exit(0);
}
/*
short main()
{
  fxp_t a=1.5;
  fxp_t b=-1.4;
  std::cout<<exp_f(a)<<std::endl;
  std::cout<<exp_f(b)<<std::endl;
  return 0;
}*/
