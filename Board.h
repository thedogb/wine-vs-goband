
#ifndef  _BOARD
#define  _BOARD
typedef unsigned long long U64;
const int win = 7;              // 连五
const int flex4 = 6;            // 活四
const int block4 = 5;           // 冲四
const int flex3 = 4;            // 活三
const int block3 = 3;           // 眠三
const int flex2 = 2;            // 活二
const int block2 = 1;           // 眠二
const int Ntype = 8;            // 棋型个数
const int MaxSize = 20;         // 棋盘最大尺寸
const int MaxMoves = 40;        // 最大着法数
const int hashSize = 1 << 22;   // 普通置换表尺寸
const int pvsSize = 1 << 20;    // pvs置换表尺寸
const int MaxDepth = 5;        // 最大搜索深度

// hash表相关
const int hash_exact = 0;
const int hash_alpha = 1;
const int hash_beta = 2;
const int unknown = -20000;

// 点的状态
const int Outside = 3;
const int Empty = 2;
const int Black = 1;
const int White = 0;
// 方向向量
const int dx[4] = { 1, 0, 1, 1 };
const int dy[4] = { 0, 1, 1, -1 };

// 坐标
struct Pos {
  int x;
  int y;
};

// 带评价的点
struct Point {
  Pos p;
  int val;
};

// 棋盘单点结构
struct Cell {
  int piece;
  int IsCand;
  int pattern[2][4];
};

// 哈希表结构
struct Hashe {
  U64 key;
  int depth;
  int hashf;
  int val;
};
struct Pv {
  U64 key;
  Pos best;
};

// 走法路线
struct Line {
  int n;
  Pos moves[MaxDepth];
};

struct MoveList {
    int phase,n,index;
    bool first;
    Pos hashMove;
    Pos moves[64];
};

class Board {
public:
  int step = 0;                                 // 棋盘落子数
  int size = 15;                                // 棋盘当前尺寸
  int b_start, b_end;                           // 棋盘坐标索引
  U64 zobristKey = 0;                           // 表示当前局面的zobristKey
  U64 zobrist[2][MaxSize + 4][MaxSize + 4];     // zobrist键值表
  Hashe hashTable[hashSize];                    // 哈希表
  Pv pvsTable[pvsSize];                         // pvs置换表
  int typeTable[10][6][6][3];                   // 初级棋型表
  int patternTable[65536][2];                   // 完整棋型表
  int pval[8][8][8][8];                         // 棋形分值表
  Cell cell[MaxSize + 8][MaxSize + 8];          // 棋盘
  Pos remMove[MaxSize * MaxSize];               // 记录落子
  Point cand[256];                              // 临时存储合理着法(两格内有子)
  bool IsLose[MaxSize + 4][MaxSize + 4];        // 记录根节点的必败点
  int who = Black;                              // 下子方
  int opp = White;                              // 另一方
  Point rootMove[64];                           // 根节点着法
  int rootCount;                                // 根节点着法个数

    Board();
   ~Board();
  void InitType();
  void InitPval();
  void InitPattern();
  void InitZobrist();
  void SetSize(int _size);
  void Display();    //绘制棋盘
  void MakeMove(Pos next);
  void DelMove();
  void Undo();
  void ReStart();
  void UpdateType(int x, int y);
  U64 Rand64();
  int GetKey(int x, int y, int i);
  int GetPval(int a, int b, int c, int d);
  int LineType(int role, int key);
  int ShortLine(int *line);
  int CheckFlex3(int *line);
  int CheckFlex4(int *line);
  int GetType(int len, int len2, int count, int block);
  Pos MoveNext(MoveList &MoveList);


  /* 可内联成员函数 */

  // 返回第step步棋的颜色，先手黑棋，后手白棋
  int color(int step) {
    return step & 1;
  }
  // 检查坐标x,y是否越界
  bool CheckXy(int x, int y) {
    return cell[x][y].piece != Outside;
  }
  // 返回最后一步棋的Cell指针
  Cell * LastMove(){
    return &cell[remMove[step - 1].x][remMove[step - 1].y];
  }
  // role:黑棋-1 白棋-0 type:统计棋形个数的数组 c:棋盘该位置的Cell指针
  void TypeCount(Cell *c, int role, int *type) {
    ++type[c->pattern[role][0]];
    ++type[c->pattern[role][1]];
    ++type[c->pattern[role][2]];
    ++type[c->pattern[role][3]];
  }
  // role:黑棋-1 白棋-0 type:要判断的棋形 c:棋盘该位置的Cell指针
  // 返回该位置4个方向是否存在棋形type
  bool IsType(Cell *c, int role, int type) {
    return c->pattern[role][0] == type
      || c->pattern[role][1] == type
      || c->pattern[role][2] == type
      || c->pattern[role][3] == type;
  }
 // 检查最后一步棋是否成连五
  bool CheckWin() {
    Cell *c = LastMove();

    return c->pattern[opp][0] == win
      || c->pattern[opp][1] == win
      || c->pattern[opp][2] == win
      || c->pattern[opp][3] == win;
  }

    //禁手检查
  bool islong(int x, int y){
        int i, j, m, n;
        int num;
        int san_num = 0;
        //横向长连
        for(i=x;cell[i][y].piece==Black; i--);
        for(j=x+1;cell[j][y].piece==Black; j++);
        if (j-i>6) return true;
        else if (j-i==4) san_num += 1;
        else if (j-i==3 && cell[i][y].piece == Empty && cell[j][y].piece == Empty && cell[i-1][y].piece == Black && cell[i-2][y].piece == Empty) san_num ++;
        else if (j-i==3 && cell[i][y].piece == Empty && cell[j][y].piece == Empty && cell[j+1][y].piece == Black && cell[j+2][y].piece == Empty) san_num ++;
        else if (j-i==2 && cell[i][y].piece == Empty && cell[j][y].piece == Empty && cell[i-1][y].piece == Black && cell[i-2][y].piece == Black && cell[i-3][y].piece == Empty) san_num ++;
        else if (j-i==2 && cell[i][y].piece == Empty && cell[j][y].piece == Empty && cell[j+1][y].piece == Black && cell[j+2][y].piece == Black && cell[j+3][y].piece == Empty) san_num ++;

        //纵向长连
        for(i=y;cell[x][i].piece==Black; i--);
        for(j=y+1;cell[x][j].piece==Black; j++);
        if (j-i>6) return true;
        else if (j-i==4) san_num += 1;
        else if (j-i==3 && cell[x][i].piece == Empty && cell[x][j].piece == Empty && cell[x][i-1].piece == Black && cell[x][i-2].piece == Empty) san_num ++;
        else if (j-i==3 && cell[x][i].piece == Empty && cell[x][j].piece == Empty && cell[x][j+1].piece == Black && cell[x][j+2].piece == Empty) san_num ++;
        else if (j-i==2 && cell[x][i].piece == Empty && cell[x][j].piece == Empty && cell[x][i-1].piece == Black && cell[x][i-2].piece == Black && cell[x][i-3].piece == Empty) san_num ++;
        else if (j-i==2 && cell[x][i].piece == Empty && cell[x][j].piece == Empty && cell[x][j+1].piece == Black && cell[x][j+2].piece == Black && cell[x][j+3].piece == Empty) san_num ++;


        // '/'向长连判断
        num = 0;
        for (i=x,j=y;cell[i][j].piece==Black; i++,j++)num++;
        for (m=x-1,n=y-1;cell[m][n].piece==Black; m--,n--)num++;
        if (num > 5)return true;
        else if (num == 3) san_num += 1;
        else if (num == 2 && cell[i][j].piece == Empty && cell[m][n].piece == Empty && cell[i+1][j+1].piece == Black && cell[i+2][j+2].piece == Empty) san_num ++;
        else if (num == 2 && cell[i][j].piece == Empty && cell[m][n].piece == Empty && cell[m-1][n-1].piece == Black && cell[m-2][n-2].piece == Empty) san_num ++;
        else if (num == 1 && cell[i][j].piece == Empty && cell[m][n].piece == Empty && cell[i+1][j+1].piece == Black && cell[i+2][j+2].piece == Black && cell[i+3][j+3].piece == Empty) san_num ++;
        else if (num == 1 && cell[i][j].piece == Empty && cell[m][n].piece == Empty && cell[m-1][n-1].piece == Black && cell[m-2][n-2].piece == Black && cell[m-3][n-3].piece == Empty) san_num ++;

        num = 0;
        for (i=x,j=y;cell[i][j].piece==Black; i++,j--)num++;
        for (m=x-1,n=y+1;cell[m][n].piece==Black; m--,n++)num++;
        if (num > 5)return true;
        else if (num == 3 && cell[i][j].piece == Empty && cell[m][n].piece == Empty) san_num += 1;
        else if (num == 2 && cell[i][j].piece == Empty && cell[m][n].piece == Empty && cell[i+1][j-1].piece == Black && cell[i+2][j-2].piece == Empty) san_num ++;
        else if (num == 2 && cell[i][j].piece == Empty && cell[m][n].piece == Empty && cell[m-1][n+1].piece == Black && cell[m-2][n+2].piece == Empty) san_num ++;
        else if (num == 1 && cell[i][j].piece == Empty && cell[m][n].piece == Empty && cell[i+1][j-1].piece == Black && cell[i+2][j-2].piece == Black && cell[i+3][j-3].piece == Empty) san_num ++;
        else if (num == 1 && cell[i][j].piece == Empty && cell[m][n].piece == Empty && cell[m-1][n+1].piece == Black && cell[m-2][n+2].piece == Black && cell[m-3][n+3].piece == Empty) san_num ++;

        if(san_num > 2) return true;

        return false;
  }


    bool CheckForbidden(int i, int j){
        //Cell * c = LastMove();
        Cell *c = &cell[i][j];
        int whoType[10]={0,0,0,0,0,0,0,0,0,0};
        for (int i=0; i<4; i++) {
            whoType[c->pattern[who][i]]++;
        }

        //禁手判断, 三三禁手、四四禁手
        if (who == Black){
            if (islong(i,j)) return true; //长连禁手
            if (whoType[win]>=1) return false;
            if (whoType[flex3] >= 2) return true; // 三三禁手
            if (whoType[block4] + whoType[flex4] >= 2) return true; // 四四禁手
        }
        return false;

    }

};
#endif
