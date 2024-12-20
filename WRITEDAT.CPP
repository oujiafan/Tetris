#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
void main(){
  FILE *fp;
  int i,j,k,m;
  static int a[7][4][16];
  if((fp=fopen("block.dat","w+"))==NULL) exit(1);
  for(i=0;i<7;i++){
    cout<<"m:";
    cin>>m;
    fwrite(&m,2,1,fp);
    for(j=0;j<m;j++)
      for(k=0;k<16;k++)
	cin>>a[i][j][k];
    fwrite(a[i],2,m*16,fp);
  }
    //printf("\n%d %d %d\n",i[0],i[1],i[2]);
  fclose(fp);
}