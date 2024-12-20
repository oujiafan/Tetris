void drawblock(int x,int y);
void drawblocks(int mini,int maxi);
void drawblank();
void drawscr();
void initdata();
void initscr();
int choose();
void line3d(int x1,int y1,int x2,int y2,int c,int n,int mode);
void outnumxy(int x,int y,long num);
int reask(char *s);

enum blocktype{
  lS,
  rS,
  lL,
  rL,
  sT,
  sO,
  sI
};

class block
{
  public:
    int type,modes,mode,cx,cy;
    int blocks[4][16];
    int lw,rw,th,bh;
    int freezed;
    block(){freezed=0;};
    ~block(){ };
    void init(int m);
    void up();
    void down();
    void left();
    void right();
    void change();
    void compute();
    void delline();
    void display(int x,int y);
    void disappear(int x,int y);
};
