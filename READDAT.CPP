#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include <conio.h>

void main(){
  FILE *fp;
  int i,j,k,n;
  static int blockc[7][4][16];
  clrscr();
  if((fp=fopen("block.dat","r"))==NULL) exit(1);
  for(i=0;i<7;i++){
    fread(&n,2,1,fp);
    cout<<n<<endl;
    fread(blockc[i],2,n*16,fp);
    for(j=0;j<n;j++){
      for(k=0;k<16;k++)
	cout<<blockc[i][j][k]<<' ';
      cout<<endl;
    }
  }
  fclose(fp);
}