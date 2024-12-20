#include <bios.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include "block.hpp"

int screen[22][12],img[59],top,level=0,speed=0,speed0=speed;
long score;
void main(){
  int gm,gd=DETECT;
  int z,z1,z2;
  long i;
  int j,k,t1,t2,quit,play=1;
  randomize();
  initgraph(&gd,&gm,"");
  //i=reask("Brick World\nDesigned by OJF");
  //if(!i) {closegraph();exit(0);}
  initdata();
  drawscr();
  block b;
  while(play){
    play=choose();if(!play) break;
    initscr();
    quit=0;
    t1=random(7);
    do{
      t2=t1;
      t1=random(7);
      b.init(t1);
      setfillstyle(1,1);
      bar(422,282,498,338);
      for(i=0;i<4;i++)
	for(j=0;j<4;j++)
	  if(b.blocks[b.mode][i*4+j]){
	    drawblock(430+15*j,295+15*i);
	  }
      b.init(t2);
      b.display(1,4);
      for(i=0;i<4;i++)
	if(screen[b.bh+2][4+i]&&b.blocks[b.mode][b.bh*4+i]) {top=1;break;}
      //while(kbhit()) z=getch();
      while(!quit&&!b.freezed&&top>1){
	for(i=1;i<(10-speed)*55000+6000;i++){
	  if(kbhit()){
	    z=bioskey(0);z1=z&127;
	    if(z1==0) z2=z>>8; else z2=z1;
	    switch (z2){
	      case 80:
		b.down();break;
	      case 75:
		b.left();break;
	      case 77:
		b.right();break;
	      case '0':
	      case 32:
		b.change();break;
	      case 27:
		quit=reask("Stop Playing?");
		break;
	      default:sound(1000);delay(30);nosound();
	    }
	    if(z2==80||quit) break;
	  }
	}
	b.down();
      }
    }while(!quit&&top>1);
    reask("GAME OVER");
  }
  closegraph();
}

void line3d(int x1,int y1,int x2,int y2,int c,int n,int mode){
  int c1=8,c2=15,tmp,i;
  if(mode) {tmp=c2;c2=c1;c1=tmp;}
  setfillstyle(1,c1);
  bar(x1,y1,x2,y2);
  setcolor(c2);
  for(i=1;i<=n;i++){
    line(x2-n+i,y1+n-i,x2-n+i,y2);
    line(x1+n-i,y2-n+i,x2,y2-n+i);
  }
  setfillstyle(1,c);
  bar(x1+n,y1+n,x2-n,y2-n);
}

void initdata(){
  int i,x=0,y=0;
  setfillstyle(1,0);
  for(i=1;i<4;i++)
    bar(x+i,y+i,x+15-i,y+15-i);
  setcolor(7);
  line(x+4,y+4,x+12,y+4);
  line(x+12,y+4,x+4,y+12);
  line(x+4,y+12,x+4,y+4);
  setfillstyle(1,7);
  floodfill(x+5,y+5,7);
  arc(x+8,y+8,225,360,2);
  arc(x+8,y+8,225,360,2);
  setcolor(0);
  arc(x+8,y+8,45,225,2);
  putpixel(x+7,y+7,0);
  putpixel(x+8,y+7,0);
  putpixel(x+7,y+8,0);
  putpixel(x+9,y+9,7);
  putpixel(x+8,y+9,7);
  putpixel(x+9,y+8,7);
  putpixel(x+10,y+7,7);
  getimage(1,1,14,14,img);

}
void drawblock(int x,int y){
  putimage(x+1,y+1,img,0);

}

void drawblank(int x,int y){
  setfillstyle(1,2);
  bar(x,y,x+15,y+15);
}

void drawscr(){
  int i,j;
  setfillstyle(6,1);
  bar(0,0,639,479);
  line3d(20,50,230,340,7,1,1);
  line3d(22,52,228,338,1,1,0);
  line3d(30,100,114,120,7,1,0);
  line3d(140,100,220,120,7,1,0);
  line3d(40,300,200,320,7,1,1);
  line3d(42,302,198,318,3,1,0);
  line3d(420,280,500,340,7,1,1);
  line3d(422,282,498,338,1,1,0);
  setcolor(13);
  outtextxy(40,107,"Level: 0");
  outtextxy(150,107,"Speed: 0");
  setcolor(4);
  outtextxy(50,306,"Score: 0");
  line3d(241,96,399,404,14,1,1);
  line3d(243,98,397,402,2,1,0);
}

int choose(){
  int qt=0,ch=1;
  int z,z1,z2,x,y;
  line3d(80,200,180,220,7,1,1);
  setcolor(13);
  outtextxy(110,207,"Start");
  setcolor(14);outtextxy(96,126,"\30");
  while(!qt){
    if(kbhit()){
      z=bioskey(0);z1=z&127;
      if(z1==0) z2=z>>8; else z2=z1;
      switch(z2){
	case '+':
	  if(ch==1){
	    level++;if(level>13) level-=14;
	    setfillstyle(1,7);
	    bar(96,107,112,116);
	    setcolor(13);
	    outnumxy(96,107,level);
	  }
	  if(ch==2){
	    speed++;if(speed>9) speed-=10;
	    setfillstyle(1,7);
	    bar(206,107,214,116);
	    setcolor(13);
	    outnumxy(206,107,speed);
	  }
	  break;
	case '-':
	  if(ch==1){
	    level--;if(level<0) level+=14;
	    setfillstyle(1,7);
	    bar(96,107,112,116);
	    setcolor(13);
	    outnumxy(96,107,level);
	  }
	  if(ch==2){
	    speed--;if(speed<0) speed+=10;
	    setfillstyle(1,7);
	    bar(206,107,214,116);
	    setcolor(13);
	    outnumxy(206,107,speed);
	  }
	  break;
	case 13:
	  if(ch==3){
	    qt=1;
	    setcolor(1);outtextxy(124,224,"\333");
	    line3d(80,200,180,220,7,1,0);
	    setcolor(13);
	    outtextxy(110,207,"Start");
	  }
	  break;
	case 75:
	  x=96+(ch==2)*110+(ch==3)*28;y=126+(ch==3)*98;
	  setcolor(1);outtextxy(x,y,"\333");
	  ch--;if(ch<=0) ch+=3;
	  x=96+(ch==2)*110+(ch==3)*28;y=126+(ch==3)*98;
	  setcolor(14);outtextxy(x,y,"\30");
	  break;
	case 77:
	  x=96+(ch==2)*110+(ch==3)*28;y=126+(ch==3)*98;
	  setcolor(1);outtextxy(x,y,"\333");
	  ch++;if(ch>=4) ch-=3;
	  x=96+(ch==2)*110+(ch==3)*28;y=126+(ch==3)*98;
	  setcolor(14);outtextxy(x,y,"\30");
	  break;
	case 27:
	  if(reask("Do you want\nto QUIT?")==1) return 0;
	  break;
	default:
	  break;
      }
    }
  }
  speed0=speed;
  return 1;
}

void initscr(){
  int i,j;
  score=0;top=20-level;
  for(i=1;i<21;i++)
    for(j=1;j<11;j++)
      screen[i][j]=0;
  for(i=0;i<11;i++){
    screen[0][i]=1;
    screen[21][i]=1;
  }
  for(i=0;i<21;i++){
    screen[i][0]=1;
    screen[i][11]=1;
  }
  for(i=20;i>top;i--)
    for(j=1;j<11;j++)
      if(random(100)<80) screen[i][j]=1;
  setfillstyle(1,7);
  bar(96,107,112,116);bar(206,107,214,116);
  setcolor(13);
  outnumxy(96,107,level);outnumxy(206,107,speed);
  setfillstyle(1,3);
  bar(106,306,196,316);
  setcolor(4);
  outnumxy(106,306,score);
  drawblocks(1,20);
}

void drawblocks(int mini,int maxi){
  int i,j;
  if(mini<=0) mini=1;
  if(maxi>20) maxi=20;
  for(i=mini;i<=maxi;i++)
    for(j=1;j<11;j++)
      if(screen[i][j])
	drawblock(230+15*j,85+15*i);
      else
	drawblank(230+15*j,85+15*i);
}

int reask(char *s){
  char ch;int i,j=0;
  char *tmp=new char[imagesize(260,210,380,270)];
  getimage(260,210,380,270,tmp);
  line3d(260,210,380,270,7,2,1);
  line3d(270,240,315,260,7,2,1);
  line3d(325,240,370,260,7,2,1);
  setcolor(1);
  for(i=0;s[i];i++)
    if(s[i]=='\n') {j=i;s[i]=0;}
  if(j){
    outtextxy(320-j*4,215,s);
    outtextxy(320-(i-j-1)*4,225,s+j+1);
    s[j]='\n';
  }
  else
    outtextxy(320-i*4,220,s);
  setcolor(5);
  outtextxy(280,247,"Yes");
  outtextxy(340,247,"No");
  while(ch!='y'&&ch!='n'&&ch!=27&&ch!=13)
    ch=getch();
  if(ch=='y'||ch==13){
    line3d(270,240,315,260,7,2,0);
    outtextxy(280,247,"Yes");
  }
  else{
    line3d(325,240,370,260,7,2,0);
    outtextxy(340,247,"No");
  }
  delay(400);
  putimage(260,210,tmp,0);
  delete tmp;
  if(ch=='y'||ch==13) return 1; else return 0;
}

void outnumxy(int x,int y,long num){
  char s[7];
  ltoa(num,s,10);
  outtextxy(x,y,s);
}

void block::init(int m){
  int i,j,k;
  FILE *fp;
  type=m;freezed=0;
  cx=1;cy=4;
  if((fp=fopen("block.dat","r"))==NULL) exit(1);
  for(i=0;i<=type;i++){
    fread(&modes,2,1,fp);
    for(j=0;j<modes;j++)
      fread(blocks[j],2,16,fp);
  }
  fclose(fp);
  mode=0;
  block::compute();
}

void block::down(){
  int i,j,k,l;
  if(freezed) return;
  for(i=bh;i>=th;i--)
    for(j=lw;j<=rw;j++)
      if(blocks[mode][i*4+j]){
	if((screen[cx+i+1][cy+j])&&!blocks[mode][(i+1)*4+j]){
	  freezed=1;
	  sound(30);delay(30);nosound();
	  if(cx<top) top=cx;
	  block::delline();
	  return;
	}
      }
  block::disappear(cx++,cy);
  block::display(cx,cy);
}

void block::up(){
}

void block::left(){
  int i,j,x0,y0;
  if(freezed) return;
  for(i=0;i<4;i++)
    if(screen[cx+i][cy+lw-1]&&blocks[mode][i*4+lw]) return;
  block::disappear(cx,cy);
  cy--;
  block::display(cx,cy);
}

void block::right(){
  int i,j,x0,y0;
  if(freezed) return;
  for(i=0;i<4;i++)
    if(screen[cx+i][cy+rw+1]&&blocks[mode][i*4+rw]) return;
  block::disappear(cx,cy);
  cy++;
  block::display(cx,cy);
}

void block::change(){
  int i,m0;
  if(freezed) return;
  block::disappear(cx,cy);
  m0=mode++;
  if(mode>=modes) mode=mode-modes;
  block::compute();
  for(i=0;i<4;i++){
    if(blocks[mode][th*4+i]&&screen[cx+th][cy+i]) break;
    if(blocks[mode][bh*4+i]&&screen[cx+bh][cy+i]) break;
    if(blocks[mode][i*4+lw]&&screen[cx+i][cy+lw]) break;
    if(blocks[mode][i*4+rw]&&screen[cx+i][cy+rw]) break;
  }
  if(i!=4) {mode=m0;block::compute();}
  block::display(cx,cy);
}

void block::display(int x,int y){
  int i,j;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(blocks[mode][i*4+j]){
	drawblock(230+15*(y+j),85+15*(x+i));
	screen[x+i][y+j]=1;
      }
}

void block::disappear(int x,int y){
  int i,j;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(blocks[mode][i*4+j]){
	drawblank(230+15*(y+j),85+15*(x+i));
	screen[x+i][y+j]=0;
      }
}

void block::compute(){
  for(lw=0;lw<4;lw++)
    if(blocks[mode][lw]||blocks[mode][lw+4]||blocks[mode][lw+8]||blocks[mode][lw+12]) break;
  for(rw=3;rw>=0;rw--)
    if(blocks[mode][rw]||blocks[mode][rw+4]||blocks[mode][rw+8]||blocks[mode][rw+12]) break;
  for(th=0;th<4;th++)
    if(blocks[mode][th*4]||blocks[mode][th*4+1]||blocks[mode][th*4+2]||blocks[mode][th*4+3]) break;
  for(bh=3;bh>=0;bh--)
    if(blocks[mode][bh*4]||blocks[mode][bh*4+1]||blocks[mode][bh*4+2]||blocks[mode][bh*4+3]) break;
}

void block::delline(){
  int i,j,k,sl=1,lines=0,line[4];
  for(i=0;i<4;i++)
    if(cx+i<21){
      for(j=1;j<11;j++)
	if(!screen[cx+i][j]) break;
      if(j==11){
	line[lines++]=cx+i;
	for(j=1;j<11;j++)
	  screen[line[lines-1]][j]=0;
      }
    }
  if(!lines) return;
  for(k=1;k<4;k++){
    for(i=0;i<=lines-1;i++)
      for(j=1;j<11;j++)
	drawblock(230+15*j,85+15*line[i]);
    delay(150);
    for(i=0;i<=lines-1;i++)
      for(j=1;j<11;j++)
	drawblank(230+15*j,85+15*line[i]);
    delay(80);
  }
  for(i=300;i<1100;i+=20){
    sound(i);delay(5);nosound();
  }
  for(i=0;i<lines-1;i++)
    if((sl=line[i+1]-line[i])!=1) break;
  if(sl!=1){
    for(j=0;j<sl-1;j++)
      for(k=1;k<11;k++){
	screen[line[lines-1]-j][k]=screen[line[i+1]-j-1][k];
	screen[line[i+1]-j-1][k]=0;
      }
  }
  for(i=line[0]-1;i>=top;i--)
    for(j=1;j<11;j++){
      screen[i+lines][j]=screen[i][j];
      screen[i][j]=0;
    }
  drawblocks(top,line[lines-1]);
  top+=lines;
  switch(lines){
    case 1:
      score+=100;break;
    case 2:
      score+=300;break;
    case 3:
      score+=600;break;
    case 4:
      score+=1000;break;
    default:
      break;
  }
  setfillstyle(1,3);
  bar(106,306,196,316);
  if(score>99999) score-=99999;
  setcolor(4);
  outnumxy(106,306,score);
  i=score/10000;
  if(speed!=(speed0+i)%10){
    speed=(speed0+i)%10;
    setfillstyle(1,7);
    bar(206,107,214,116);
    setcolor(13);
    outnumxy(206,107,speed);
  }
}