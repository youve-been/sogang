/*가장 메인이 되는 헤더*/
#ifndef _FISH_H_
#define _FISH_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "player-graphic-info.h"
#include "mob-graphic-info.h"

#define MENU_SIZE 3

#define MENU_PLAY 1
#define MENU_RANK 2
#define MENU_EXIT 3

#define WIDTH  60   //게임 메인화면의 너비
#define HEIGHT  30   //게임 메인화면의 높이
#define ACCEL 2  //주인공의 이동 시 가속도
#define NOTHING 0
#define QUIT 'q'
#define FPS 18 //Run함수가 1초에 실행되는 횟수
#define INPUT_PER_FRAME 6 //입력을 처리하는 프레임 간격
#define MAX_SPEED 3 //이동시 최대 속도
#define NAMELEN 30 //이름 입력시 최대 길이

#define ABS(x) (x > 0 ? x : -x) //절댓값을 위한 매크로 함수
#define MIN(x, y) (x > y ? y : x) //최솟값을 위한 매크로 함수

typedef struct COORD {
    int x;
    int y;
} COORD;

/*랭킹 저장에 사용되는 노드*/
typedef struct _NODE *nptr;
typedef struct _NODE {
    char name[NAMELEN];
    int score;
    nptr link;
} NODE;

typedef struct _MOVENODE {
    int fish_index;
    int evaluate;
} MOVE;

typedef struct _MOB {
    COORD pos;
    COORD speed;
    int size;
    int state;
    MOVE pq[32];
    int pq_size;
    int pq_clear_flag;
} MOB;

char field[HEIGHT*2][WIDTH*2];   //게임의 필드(맵)

int score;   //점수를 저장
int game_over = 0;   //게임이 종료되면 1로 바뀜
nptr head;   //랭킹을 저장하는 리스트의 headnode
int numRank;   //랭킹에 저장된 정보의 수

COORD pos; //현재 주인공의 위치
COORD speed; //현재 주인공의 속도
int fish_size; //현재 주인공의 크기
int fish_direction; //방향을 저장
int fish_state; //바라보는 뱡향 상태
int minimap;   //전체 맵에서 현재 주인공의 위치. (minimap+1)사분면에 위치함 
int nitro; //부스트 게이지
int boost_flag; //부스트 사용 여부


int timed_out; //sigaction을 위한 변수
int current_frame; //inputFlag를 결정하기 위한 변수

MOB mobs[30];
int mob_count;
int count_by_size[6];

const int size_up_table[6] = { 0, 0, 500, 1800, 3500, 5600 };

/*Init Functions*/
//전체적으로 초기화하는 함수
void Init();
//플레이어 관련 데이터를 초기화하는 함수
void InitPlayer();
//게임 전체화면을 초기화하는 함수
void InitScreen();
//게임의 필드를 초기화하는 함수, 벽 생성을 담당함
void InitField();

/*Draw Functions*/
//게임의 모든 인터페이스를 그리는 함수
void DrawOutline();
//field 배열을 화면에 그려주는 함수
void DrawField();
//입력된 좌표에 원하는 크기의 박스를 그려주는 함수
void DrawBox(int y, int x, int height, int width);
//입력된 좌표에 원하는 크기의 물고기를 그려주는 함수
void DrawFish(int y, int x, int size, int state);
//입력된 좌표의 물고기를 지워주는 함수
void EraseFish(int y, int x, int size, int state);
//현재 화면의 위치를 미니맵에 표시하는 함수
void DrawMinimap();
//점수를 지정된 위치에 출력하는 함수
void PrintScore();
//부스트 게이지를 그려주는 함수
void DrawNitro();

/*Field Control Functions*/
//장애물을 가지치기로 생성하는 함수
void RockBranching();
//가지를 칠 수 있는지 확인하는 함수
int CheckToBranch(COORD branch_direction, COORD pos);
//가지 친 장애물들을 필드에 추가하는 함수
void AddBranchToField(char field[HEIGHT*2][WIDTH*2], COORD rocks[20], int size);

/*Mob Control Functions*/
//몹들을 전체적으로 다루는 함수
void ProcessMobs(int frame);
//몹을 생성하는 함수
void GenerateMob();
//몹이 이동할 수 있는지 확인하는 함수
int CheckToMoveMob(char field[HEIGHT*2][WIDTH*2], int y, int x, int size, int state);
//필요한 사이즈를 구하는 함수
int GetNewSize();
//몹의 이동을 처리하는 함수
void ProcessMovementMob(int fish_index, int direction);
//입력된 좌표에 몹을 그려주는 함수
void DrawMob(int fish_index);
//입력된 좌표의 몹을 지워주는 함수
void EraseMob(int fish_index);
//몹을 새롭게 생성하는 함수
void RegenerateMob(int fish_index);
//우선순위 큐(max heap)에 원소를 push하는 함수
void PushPQ(int current_index, int fish_index, int evaluate);
//우선순위 큐(max heap)에 원소를 pop하는 함수
void PopPQ(int current_index);
//모든 정보를 우선순위 큐에 push하는 함수
void PushAll(int current_index);
//평가 정보를 반환하는 함수
int GetEvaluate(int current_index, int opponent_index);
//우선순위 큐를 통해 방향을 결정하는 함수
int GetDirection(int current_index, int opponent_index);

/*Movement Functions*/
//키를 입력받는 함수
int GetCommand();
//GetCommand 함수로 입력받은 키에 대한 동작을 수행하는 함수
int ProcessCommand(int command);
//플레이어의 프레임당 행동을 처리하는 함수
void ProcessPlayer(int frame);
//입력받은 움직임을 적용하는 함수
void ProcessMovement(int direction);
//입력된 움직임이 가능한지 확인하는 함수
int CheckToMove(char field[HEIGHT*2][WIDTH*2], int y, int x);
//좌표의 사분면을 반환하는 함수
int GetMinimap(int y, int x);

//메뉴의 타이틀을 그려주는 함수
void PrintTitle();
//메뉴를 보여주고 선택을 담당하는 함수
int Menu();
//게임의 전반적인 플레이를 담당하는 함수
void Play();
//게임의 각 프레임마다 실행되는 내용을 처리하는 함수
void Run(int sig);

//몹과 플레이어간의 충돌을 다루는 함수
void ProcessFeed();

/*Ranking Functions*/
//랭킹을 보여주는 함수
void Rank();
//rank.txt 파일에서 랭킹을 읽어와 저장하는 함수
void CreateRankList();
//게임이 종료된 후 점수를 랭킹에 저장하는 함수
void NewRank();
//변경된 랭킹을 rank.txt에 다시 저장하는 함수
void UpdateRankFile();
//리스트의 모든 원소의 할당을 해제하는 함수
void FreeAll();
#endif