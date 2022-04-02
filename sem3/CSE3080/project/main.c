#include "fish.h"

static struct sigaction act, oact;

int main(void)
{
    initscr();
    noecho();
	keypad(stdscr, TRUE);
    if(has_colors() == TRUE)
        start_color();
    else {
        printw("Your screen doesn't support color\n");
        getch();
        return 0;
    }
    Init();
    CreateRankList();
    while(true)
    {
        switch(Menu())
        {
        case MENU_PLAY:
            Play();
            break;
        case MENU_RANK:
            Rank();
            break;
        case MENU_EXIT:
            FreeAll();
            endwin();
	        system("clear");
            return 0;
        }
    }
    FreeAll();
    endwin();
	system("clear");
	return 0;
}

void Init()
{
    //게임 실행을 위한 변수 초기화
    srand(time(NULL));
    InitField();

    current_frame = 0;
    game_over = 0;
    score = 0;

    mob_count = 0;
    for(int i = 0; i < 6; i++) count_by_size[i] = 0;

    InitPlayer();
    InitScreen();

    timed_out = 0;
}

void InitPlayer()
{
    //주인공 정보 초기화
    pos.x = rand() % (WIDTH*2);
    pos.y = rand() % (HEIGHT*2);
    speed.x = 0;
    speed.y = 0;
    fish_direction = NOTHING;
    fish_size = 0;
    fish_state = 0;
    nitro = 5;
    boost_flag = 0;
    minimap = GetMinimap(pos.y, pos.x);
}

void InitScreen()
{
    //색상정보 초기화
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, PLAYER_COLOR_1, COLOR_BLACK);
    init_pair(3, PLAYER_COLOR_2, COLOR_BLACK);
    init_pair(4, MOB_COLOR_1, COLOR_BLACK);
    init_pair(5, MOB_COLOR_2, COLOR_BLACK);
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    //게임화면 그리기
    DrawOutline();
    DrawFish(pos.y, pos.x, fish_size, fish_state);
    DrawMinimap();
    PrintScore();
    
    move(HEIGHT, WIDTH+4);
    //getch();
}

void InitField()
{
    for(int i=0;i<HEIGHT*2;i++)
		for(int j=0;j<WIDTH*2;j++)
			field[i][j]=0;

    int num_of_puffer = rand() % 3 + 3;
    for(int i = 0; i < num_of_puffer; i++)
    {
        int x = rand() % (WIDTH*2);
        int y = rand() % (HEIGHT*2);

        field[y][x] = 3;
    }

    int num_of_branch = rand() % 3 + 7;
    for(int i = 0; i < num_of_branch; i++)
    {
        RockBranching();
    }
    for(int i = 0; i < HEIGHT*2; i++)
    {
        for(int j = 0; j < WIDTH*2; j++)
        {
            if(field[i][j] == 2 || field[i][j] == 3) continue;
            if((i == 0 || field[i-1][j] == 1) || (j == 0 || field[i][j-1] == 1))
            {
                field[i][j] = 1;
            }
        }
    }
    for(int i = HEIGHT*2-1; i >= 0; i--)
    {
        for(int j = WIDTH*2-1; j >= 0; j--)
        {
            if(field[i][j] == 2 || field[i][j] == 3) continue;
            if((i == HEIGHT*2-1 || field[i+1][j] == 1) || (j == WIDTH*2-1 || field[i][j+1]))
            {
                field[i][j] = 1;
            }
        }
    }
}

void RockBranching()
{
    int num_of_rock = rand() % 11 + 7;

    COORD rocks[20];
    rocks[0].x = rand() % (WIDTH*2);
    rocks[0].y = rand() % (HEIGHT*2);

    int current = 0;
    int size = 1;

    while(size < num_of_rock)
    {
        int count = rand() % 7;
        switch(count)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            count = 1;
            break;
        case 4:
        case 5:
            count = 2;
            break;
        case 6:
            count = 3;
            break;
        }

        while(count-- && size < num_of_rock)
        {
            int direction = rand() % 8;
            COORD branch_direction;
            do {
                branch_direction.x = rand() % 3 - 1;
                branch_direction.y = rand() % 3 - 1;
            } while(branch_direction.x == 0 && branch_direction.y == 0);

            if(CheckToBranch(branch_direction, rocks[current]))
            {
                rocks[size].x = rocks[current].x + branch_direction.x;
                rocks[size].y = rocks[current].y + branch_direction.y;
                size++;
            }
            else
            {
                num_of_rock--;
            }
        }
        current++;
        if(current >= size) current = size - 1;
    }

    AddBranchToField(field, rocks, num_of_rock);
}

int CheckToBranch(COORD branch_direction, COORD pos)
{
    if(branch_direction.x < 0 && pos.x < 0) return 0;
    if(branch_direction.x > 0 && pos.x > WIDTH*2 - 2) return 0;
    if(branch_direction.y < 0 && pos.y < 0) return 0;
    if(branch_direction.y > 0 && pos.y > HEIGHT*2 - 2) return 0;

    return 1;
}

void AddBranchToField(char field[HEIGHT*2][WIDTH*2], COORD rocks[20], int size)
{
    for(int i = 0; i < size; i++)
    {
        field[rocks[i].y][rocks[i].x] = 2;
        field[rocks[i].y+1][rocks[i].x] = 2;
        field[rocks[i].y][rocks[i].x+1] = 2;
        field[rocks[i].y+1][rocks[i].x+1] = 2;
    }
}

void DrawOutline()
{
    int i, j;

    //게임이 진행되는 메인화면
    DrawBox(0, 0, HEIGHT, WIDTH);

    //미니맵
    move(0,WIDTH+4);
    printw("MINIMAP");
    DrawBox(1, WIDTH+4, 10, 20);

    //점수
    move(13,WIDTH+4);
    printw("SCORE");
    DrawBox(14, WIDTH+4, 1, 20);

    //부스터게이지
    move(17,WIDTH+4);
    printw("NITRO");
    DrawBox(18, WIDTH+4, 1, 20);
}
//키를 입력받는 함수
int GetCommand()
{
	int command;
	command = wgetch(stdscr);
	switch(command){
    case 'w':
	case KEY_UP:
        command = KEY_UP;
		break;
    case 's':
	case KEY_DOWN:
        command = KEY_DOWN;
		break;
    case 'a':
	case KEY_LEFT:
        command = KEY_LEFT;
		break;
    case 'd':
	case KEY_RIGHT:
        command = KEY_RIGHT;
		break;
	case ' ':	/* space key*/
		/*nitro*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		break;
	}
	return command;
}

int ProcessCommand(int command)
{
	int ret=1;
	switch(command) {
    case KEY_UP:
	case KEY_DOWN:
	case KEY_LEFT:
	case KEY_RIGHT:
        fish_direction = command;
        break;
    case ' ':
        boost_flag = 1;
        break;
    case QUIT:
		ret = QUIT;
		break;
    case 'g':
        fish_size += 1;
    default:
        break;
    }
	return ret;	
}

void DrawField() // minimap을 받아 처리해야 함
{
    int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j+(int)(minimap >= 2)*HEIGHT][i+(int)(minimap % 3 == 0)*WIDTH]==2){
				attron(A_REVERSE);
				printw("+");
				attroff(A_REVERSE);
			}
			else if(field[j+(int)(minimap >= 2)*HEIGHT][i+(int)(minimap % 3 == 0)*WIDTH]==3) {
                attron(COLOR_PAIR(6));
                printw("#");
                attroff(COLOR_PAIR(6));
            }
            else printw(" ");
		}
	}
}

void DrawBox(int y, int x, int height, int width)
{
    int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void DrawFish(int y, int x, int size, int state)
{
    if(y >= HEIGHT) y -= HEIGHT;
    if(x >= WIDTH) x -= WIDTH;

    move(y + 1, x + 1);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            graphic part = player_graphic[size][fish_state][i][j];
            if(part.shape == ' ') continue;
            move(y + i, x - 1 + j);
            attron(COLOR_PAIR(part.color == PLAYER_COLOR_1 ? 2 : 3));
            printw("%c", part.shape);
            attroff(COLOR_PAIR(part.color == PLAYER_COLOR_1 ? 2 : 3));
        }
    }
}

void EraseFish(int y, int x, int size, int state)
{
    if(y >= HEIGHT) y -= HEIGHT;
    if(x >= WIDTH) x -= WIDTH;

    move(y + 1, x + 1);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            graphic part = player_graphic[size][fish_state][i][j];
            if(part.shape == ' ') continue;
            move(y + i, x - 1 + j);
            printw(" ");
        }
    }
}

void DrawMinimap()
{
    move(0,WIDTH+4);
    printw("MINIMAP");
    for(int i = 0; i < 10; i++)
    {
        move(2+i,WIDTH+4);
        printw("                     ");
    }
    DrawBox(1, WIDTH+4, 10, 20);

    attron(COLOR_PAIR(1));
    switch(minimap){
        case 0:
            DrawBox(1, WIDTH+14, 5, 10);
            break;
        case 1:
            DrawBox(1, WIDTH+4, 5, 10);
            break;
        case 2:
            DrawBox(6, WIDTH+4, 5, 10);
            break;
        case 3:
            DrawBox(6, WIDTH+14, 5, 10);
            break;
    }
    attroff(COLOR_PAIR(1));
}
//입력된 움직임이 가능한지 확인하는 함수
int CheckToMove(char field[HEIGHT*2][WIDTH*2], int y, int x)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            graphic part = player_graphic[fish_size][fish_state][i][j];
            if(part.shape == ' ') continue;
            if(y + i - 1 < 0 || y + i - 1 > HEIGHT*2 - 1) return 0;
            if(x + j - 2 < 0 || x + j - 2 > WIDTH*2 - 1) return 0;
            if(field[y+i-1][x+j-2] == 2) return 0;
            if(field[y+i-1][x+j-2] == 3) return -1;
        }
    }
    return 1;
}

void PrintScore()
{
    move(15,WIDTH+5);
    printw("%20d", score);
}

void DrawNitro()
{
    //19, WIDTH+5
    for(int i = 0; i < nitro; i++)
    {
        move(19, WIDTH + 5 + i*2);
        attron(A_REVERSE);
        printw("  ");
        attroff(A_REVERSE);
    }
    for(int i = nitro; i < 10; i++)
    {
        move(19, WIDTH + 5 + i*2);
        printw("  ");
    }
}

void PrintTitle()
{
    move(0, 0);
    printw("            ________  ___          ___\n");
    printw("           /  _____/\\/__/\\        /  /\n");
    printw("          /  /_____\\/  /\\/_____  / ,/___\n");
    printw("         /  _____/\\/  / /',__ /\\/  ,__  \\\n");
    printw("        /  / ____\\/  / /__,  /\\/  /\\_/  /\\\n");
    printw("       /_ / /    /__/ /_____/ /__/ //__/ /\n");
    printw("       \\ _\\/     \\__\\/\\_____\\/\\__\\/ \\__\\/\n");
    printw("                                       grows  ___    ___  ________    ___\n");
    printw("                                             /  /\\  /  /\\/  ,___  \\  /  /\\\n");
    printw("                                            /  / / /  / /  /___/  /\\/  / /\n");
    printw("                                           /  / / /  / /  ______,/ /  / /\n");
    printw("                                           \\  \\/_/  / /  /\\______\\/__/ /\n");
    printw("                                            \\_____,/ /__/ /      /__/\\/\n");
    printw("                                             \\_____\\/\\__\\/       \\__\\/\n");
}

int Menu()
{
    int select = 1;
    int command;
    while(true) {
        clear();
        PrintTitle();
        DrawBox(17, 37, 1, 6);
        move(18, 39);
        printw("PLAY");
        if(select == 1)
        {
            move(18, 47);
            printw("<-");
        }
        DrawBox(21, 37, 1, 6);
        move(22, 39);
        printw("RANK");
        if(select == 2)
        {
            move(22, 47);
            printw("<-");
        }
        DrawBox(25, 37, 1, 6);
        move(26, 39);
        printw("EXIT");
        if(select == 3)
        {
            move(26, 47);
            printw("<-");
        }
        move(0,0);
        command = GetCommand();
        if(command == 10) break;
        switch(command) {
        case KEY_LEFT:
        case KEY_UP:
            select -= 1;
            break;
        case KEY_RIGHT:
        case KEY_DOWN:
            select += 1;
            break;
        }
        if(select >= MENU_SIZE) select = MENU_SIZE;
        if(select < 1) select = 1;
    };
    system("clear");
    return select;
}

void Play()
{
    int command;
	clear();
	Init();
    //sleep(1);
    act.sa_handler = Run;
	sigaction(SIGALRM,&act,&oact);
	do{
		if(timed_out==0){
            timed_out=1;
			ualarm(1000000 / FPS, 0);
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			ualarm(0, 0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();
			NewRank(score);
			return;
		}
	}while(!game_over);

	ualarm(0, 0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
    sleep(1);
	getch();
	NewRank(score);
}

void Run(int sig)
{
    current_frame = (current_frame + 1) % INPUT_PER_FRAME; //프레임번호 처리
    DrawField();
    move(HEIGHT + 2, 0);

    //printw("currFrame : %2d    direction : %03d    speedX : %02d  speedY : %02d", current_frame, fish_direction, speed.x, speed.y); //테스트를 위한 임시 출력

    ProcessPlayer(current_frame);
    ProcessMobs(current_frame);
    ProcessFeed();

    PrintScore();
    DrawNitro();

    timed_out = 0;
}

void ProcessMobs(int frame)
{
    if(mob_count < fish_size * 2 + 7)
    {
        GenerateMob();
    }
    for(int i = 0; i < mob_count; i++)
    {
        if(!frame) // 입력을 받을 프레임이면 pq로 확인
        {
            int index = mobs[i].pq[1].fish_index;
            int evaluate = mobs[i].pq[1].evaluate;
            int direction = GetDirection(i, index); //remove when pq done
            ProcessMovementMob(i, direction);
            PopPQ(i);
            mobs[i].pq_clear_flag -= 1;
            if(mobs[i].pq_clear_flag <= 0) {
                PushAll(i);
            }
            else {
                PushPQ(i, index, evaluate * 0.9);
            }
            //move(21 + i, WIDTH + 4);
            //printw("FISH %2d: direction=%3d, flag=%d, index=%d", i, direction, index);
        }

        if(mobs[i].speed.x < -MAX_SPEED || mobs[i].speed.x > MAX_SPEED || mobs[i].speed.y < -MAX_SPEED || mobs[i].speed.y > MAX_SPEED) //에러 핸들링
        {
            mobs[i].speed.x = 0;
            mobs[i].speed.y = 0;
        }

        if(mobs[i].speed.x < 0) mobs[i].state = 0;
        if(mobs[i].speed.x > 0) mobs[i].state = 1;

        COORD temp = mobs[i].pos;

        if(mobs[i].speed.x != 0 || mobs[i].speed.y != 0) EraseMob(i);

        /*아래 두 조건문은 따로 함수로 빼도 될 듯?*/
        if(mobs[i].speed.x != 0 && (frame % (INPUT_PER_FRAME / ABS(mobs[i].speed.x)) == 0)) //이동을 처리할 프레임인지 확인하고 움직임 적용
        {
            if(mobs[i].speed.x > 0) temp.x += 1;
            else temp.x -= 1;
        }

        if(mobs[i].speed.y != 0 && (frame % (INPUT_PER_FRAME / ABS(mobs[i].speed.y)) == 0)) //이동을 처리할 프레임인지 확인하고 움직임 적용
        {
            if(mobs[i].speed.y > 0) temp.y += 1;
            else temp.y -= 1;
        }

        /*필드 밖으로 나가지 않도록 처리, 더 발전한다면 CheckToMove()에 합쳐야 함*/
        if(!CheckToMoveMob(field, temp.y, temp.x, mobs[i].size, mobs[i].state)) continue;

        mobs[i].pos.x = temp.x;
        mobs[i].pos.y = temp.y;

        if(mobs[i].speed.x != 0 || mobs[i].speed.y != 0) DrawMob(i);
    }
}

void GenerateMob()
{
    mobs[mob_count].size = GetNewSize();
    do {
        mobs[mob_count].pos.x = rand() % (WIDTH*2);
        mobs[mob_count].pos.y = rand() % (WIDTH*2);

        mobs[mob_count].state = rand() % 2;
    } while(CheckToMoveMob(field, mobs[mob_count].pos.y, mobs[mob_count].pos.x, mobs[mob_count].size, mobs[mob_count].state) == 0);

    //set pq
    PushAll(mob_count);
    count_by_size[mobs[mob_count].size]++;
    mob_count++;
}

int CheckToMoveMob(char field[HEIGHT*2][WIDTH*2], int y, int x, int size, int state)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            graphic part = mob_graphic[size][state][i][j];
            if(part.shape == ' ') continue;
            if(y + i - 1 < 0 || y + i - 1 > HEIGHT*2 - 1) return 0;
            if(x + j - 2 < 0 || x + j - 2 > WIDTH*2 - 1) return 0;
            if(field[y+i-1][x+j-2] == 2) return 0;
            if(field[y+i-1][x+j-2] == 0) return 0;
        }
    }
    return 1;
}

void ProcessMovementMob(int fish_index, int direction)
{
    switch(direction){
	case KEY_UP:
        if(mobs[fish_index].speed.y > -MAX_SPEED) mobs[fish_index].speed.y -= 1;
        if(mobs[fish_index].speed.y > 0) mobs[fish_index].speed.y -= 1;
        if(mobs[fish_index].speed.x > 0) mobs[fish_index].speed.x -= 1;
        else if(mobs[fish_index].speed.x < 0) mobs[fish_index].speed.x += 1;
		break;
	case KEY_DOWN:
        if(mobs[fish_index].speed.y < MAX_SPEED) mobs[fish_index].speed.y += 1;
        if(mobs[fish_index].speed.y < 0) mobs[fish_index].speed.y += 1;
        if(mobs[fish_index].speed.x > 0) mobs[fish_index].speed.x -= 1;
        else if(mobs[fish_index].speed.x < 0) mobs[fish_index].speed.x += 1;
		break;
	case KEY_RIGHT:
        if(mobs[fish_index].speed.x < MAX_SPEED) mobs[fish_index].speed.x += 1;
        if(mobs[fish_index].speed.x < 0) mobs[fish_index].speed.x += 1;
        if(mobs[fish_index].speed.y > 0) mobs[fish_index].speed.y -= 1;
        else if(mobs[fish_index].speed.y < 0) mobs[fish_index].speed.y += 1;
		break;
	case KEY_LEFT:
        if(mobs[fish_index].speed.x > -MAX_SPEED) mobs[fish_index].speed.x -= 1;
        if(mobs[fish_index].speed.x > 0) mobs[fish_index].speed.x -= 1;
        if(mobs[fish_index].speed.y > 0) mobs[fish_index].speed.y -= 1;
        else if(mobs[fish_index].speed.y < 0) mobs[fish_index].speed.y += 1;
		break;
	default:
        if(mobs[fish_index].speed.x > 0) mobs[fish_index].speed.x -= 1;
        else if(mobs[fish_index].speed.x < 0) mobs[fish_index].speed.x += 1;
        if(mobs[fish_index].speed.y > 0) mobs[fish_index].speed.y -= 1;
        else if(mobs[fish_index].speed.y < 0) mobs[fish_index].speed.y += 1;
		break;
	}
}

int GetNewSize()
{
    int smaller = 0;
    int bigger = 0;
    for(int i = 0; i < fish_size; i++)
    {
        smaller += count_by_size[i];
    }
    for(int i = fish_size; i < MAX_SIZE; i++)
    {
        bigger += count_by_size[i];
    }

    if(smaller <= bigger)
    {
        if(fish_size == 0) return 0;
        return fish_size - 1;
    }
    else if(bigger - count_by_size[fish_size] <= count_by_size[fish_size])
    {
        if(fish_size == MAX_SIZE - 1) return fish_size;
        return fish_size + 1;
    }
    else
    {
        return fish_size;
    }
}

void DrawMob(int fish_index)
{
    int y = mobs[fish_index].pos.y;
    int x = mobs[fish_index].pos.x;

    if(minimap != GetMinimap(y, x)) return;

    if(y >= HEIGHT) y -= HEIGHT;
    if(x >= WIDTH) x -= WIDTH;

    move(y + 1, x + 1);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            graphic part = mob_graphic[mobs[fish_index].size][mobs[fish_index].state][i][j];
            if(part.shape == ' ') continue;
            move(y + i, x - 1 + j);
            attron(COLOR_PAIR(part.color == MOB_COLOR_1 ? 4 : 5));
            printw("%c", part.shape);
            attroff(COLOR_PAIR(part.color == MOB_COLOR_2 ? 4 : 5));
        }
    }
}

void EraseMob(int fish_index)
{
    int y = mobs[fish_index].pos.y;
    int x = mobs[fish_index].pos.x;

    if(minimap != GetMinimap(y, x)) return;

    if(y >= HEIGHT) y -= HEIGHT;
    if(x >= WIDTH) x -= WIDTH;

    move(y + 1, x + 1);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            graphic part = mob_graphic[mobs[fish_index].size][mobs[fish_index].state][i][j];
            if(part.shape == ' ') continue;
            move(y + i, x - 1 + j);
            printw(" ");
        }
    }
}

void RegenerateMob(int fish_index)
{
    count_by_size[mobs[fish_index].size]--;
    mobs[fish_index].size = GetNewSize();
    do {
        mobs[fish_index].pos.x = rand() % (WIDTH*2);
        mobs[fish_index].pos.y = rand() % (WIDTH*2);

        mobs[fish_index].state = rand() % 2;
    } while(CheckToMoveMob(field, mobs[fish_index].pos.y, mobs[fish_index].pos.x, mobs[fish_index].size, mobs[fish_index].state) == 0);
    count_by_size[mobs[fish_index].size]++;
}

void PushPQ(int current_index, int fish_index, int evaluate)
{
    if(mobs[current_index].size >= 31) return;
    MOVE* pq = mobs[current_index].pq;
    int index = mobs[current_index].pq_size + 1;

    pq[index].evaluate = evaluate;
    pq[index].fish_index = fish_index;
    mobs[current_index].pq_size++;

    while(index > 1)
    {
        int next_index = index / 2;
        if(abs(pq[index].evaluate) > abs(pq[next_index].evaluate)) {
            int temp = pq[index].evaluate;
            pq[index].evaluate = pq[next_index].evaluate;
            pq[next_index].evaluate = temp;
            temp = pq[index].fish_index;
            pq[index].fish_index = pq[next_index].fish_index;
            pq[next_index].fish_index = temp;
            index = next_index;
        }
        else break;
    }
}

void PopPQ(int current_index)
{
    if(mobs[current_index].pq_size <= 0) return;
    MOVE* pq = mobs[current_index].pq;
    int index = 1;
    pq[1].evaluate = 0;
    pq[1].fish_index = 0;
    mobs[current_index].pq_size--;
    while(index < 16)
    {
        int next_index = index * 2;
        if(abs(pq[next_index].evaluate) > abs(pq[next_index+1].evaluate))
        {
            int temp = pq[index].evaluate;
            pq[index].evaluate = pq[next_index].evaluate;
            pq[next_index].evaluate = temp;
            temp = pq[index].fish_index;
            pq[index].fish_index = pq[next_index].fish_index;
            pq[next_index].fish_index = temp;
            index = next_index;
        }
        else
        {
            int temp = pq[index].evaluate;
            pq[index].evaluate = pq[next_index+1].evaluate;
            pq[next_index+1].evaluate = temp;
            temp = pq[index].fish_index;
            pq[index].fish_index = pq[next_index+1].fish_index;
            pq[next_index+1].fish_index = temp;
            index = next_index+1;
        }
    }
}

void PushAll(int current_index)
{
    for(int i = 0; i < 32; i++)
    {
        mobs[current_index].pq[i].evaluate = 0;
        mobs[current_index].pq[i].fish_index = 0;
    }
    mobs[current_index].pq_size = 0;

    mobs[current_index].pq_clear_flag = rand() % 3 + 5;
    PushPQ(current_index, -1, GetEvaluate(current_index, -1));
    for(int i = 0; i < mob_count; i++)
    {
        PushPQ(current_index, i, GetEvaluate(current_index, i));
    }
}

int GetEvaluate(int current_index, int opponent_index)
{
    int dx, dy, avoid = 1;
    if(opponent_index == -1)
    {
        dx = abs(pos.x - mobs[current_index].pos.x);
        dy = abs(pos.y - mobs[current_index].pos.y);

        if(fish_size > mobs[current_index].size) avoid = -1;
        if(fish_size == mobs[current_index].size) avoid = 0;
    }
    else
    {
        dx = abs(mobs[opponent_index].pos.x - mobs[current_index].pos.x);
        dy = abs(mobs[opponent_index].pos.y - mobs[current_index].pos.y);

        if(mobs[opponent_index].size > mobs[current_index].size) avoid = -1;
        if(fish_size == mobs[current_index].size) avoid = 0;
    }
    int distance = dx + dy;
    if(distance == 0) return 0;
    return 1000000000 / distance * avoid;
}

int GetDirection(int current_index, int opponent_index)
{
    int dx, dy;
    if(opponent_index == -1)
    {
        dx = pos.x - mobs[current_index].pos.x;
        dy = pos.y - mobs[current_index].pos.y;
    }
    else
    {
        dx = mobs[opponent_index].pos.x - mobs[current_index].pos.x;
        dy = mobs[opponent_index].pos.y - mobs[current_index].pos.y;
    }
    int avoid = mobs[current_index].pq[1].evaluate > 0 ? 1 : -1;
    int axis = rand() % 2;
    if(axis == 0) //X axis
    {
        if(dx * avoid > 0)
            return KEY_RIGHT;
        else
            return KEY_LEFT;
    }
    else //Y axis
    {
        if(dy * avoid > 0)
            return KEY_DOWN;
        else
            return KEY_UP;
    }
}

void ProcessFeed()
{
    /*first with player*/
    for(int i = 0; i < mob_count; i++)
    {
        int dx = abs(pos.x - mobs[i].pos.x);
        int dy = abs(pos.y - mobs[i].pos.y);
        if(dx < distance_table_x[fish_size] && dy < distance_table_y[fish_size])
        {
            if(fish_size < mobs[i].size)
            {
                game_over = 1;
            }
            else if(fish_size == mobs[i].size)
            {
                continue;
            }
            else
            {
                score += (mobs[i].size + 1) * 100;
                RegenerateMob(i);
            }
        }
    }
    /*next with just mobs*/
    for(int i = 0; i < mob_count; i++)
    {
        for(int j = 0; j < mob_count; j++)
        {
            int dx = abs(mobs[j].pos.x - mobs[i].pos.x);
            int dy = abs(mobs[j].pos.y - mobs[i].pos.y);
            if(dx < distance_table_x[fish_size] && dy < distance_table_y[fish_size])
            {
                if(mobs[j].size < mobs[i].size)
                {
                    RegenerateMob(j);
                }
                else if(mobs[j].size == mobs[i].size)
                {
                    continue;
                }
                else
                {
                    RegenerateMob(i);
                }
            }
        }
    }
}

void ProcessPlayer(int frame)
{
    if(fish_size < MAX_SIZE - 1 && score >= size_up_table[fish_size+1]) fish_size+=1;
    if(!frame) // 입력을 받을 프레임이면 저장된 입력 처리
    {
        ProcessMovement(fish_direction);
        fish_direction = 0; //방향을 0으로 초기화
        if(boost_flag) nitro -= 1;
        else nitro += 1;
        if(nitro > 10) nitro = 10;
        if(nitro == 0) boost_flag = 0;
    }

    if(speed.x < -6 || speed.x > 6 || speed.y < -6 || speed.y > 6) //에러 핸들링
    {
        speed.x = 0;
        speed.y = 0;
    }

    if(boost_flag && speed.x >= MAX_SPEED) speed.x = 6;
    if(boost_flag && speed.x <= -MAX_SPEED) speed.x = -6;
    if(boost_flag && speed.y >= MAX_SPEED) speed.y = 6;
    if(boost_flag && speed.y <= -MAX_SPEED) speed.y = -6;

    if(speed.x < 0) fish_state = 0;
    if(speed.x > 0) fish_state = 1;

    COORD temp = pos;

    if(speed.x != 0 || speed.y != 0) EraseFish(pos.y, pos.x, fish_size, fish_state); //움직였다면 이전의 위치에 그려진 물고기를 지움

    /*아래 두 조건문은 따로 함수로 빼도 될 듯?*/
    if(speed.x != 0 && (frame % (INPUT_PER_FRAME / ABS(speed.x)) == 0)) //이동을 처리할 프레임인지 확인하고 움직임 적용
    {
        if(speed.x > 0) temp.x += 1;
        else temp.x -= 1;
    }

    if(speed.y != 0 && (frame % (INPUT_PER_FRAME / ABS(speed.y)) == 0)) //이동을 처리할 프레임인지 확인하고 움직임 적용
    {
        if(speed.y > 0) temp.y += 1;
        else temp.y -= 1;
    }

    /*필드 밖으로 나가지 않도록 처리, 더 발전한다면 CheckToMove()에 합쳐야 함*/
    int ret = CheckToMove(field, temp.y, temp.x);
    if(ret == 0) return;
    if(ret == -1) game_over = 1;
    pos.x = temp.x;
    pos.y = temp.y;

    minimap = GetMinimap(pos.y, pos.x);

    DrawFish(pos.y, pos.x, fish_size, fish_state); // 최종 위치에 물고기를 그려줌
    DrawOutline();
    DrawMinimap();
}

void ProcessMovement(int direction)
{
    switch(direction){
	case KEY_UP:
        if(speed.y > -MAX_SPEED) speed.y -= 1;
        if(speed.y > 0) speed.y -= 1;
        if(speed.x > 0) speed.x -= 1;
        else if(speed.x < 0) speed.x += 1;
		break;
	case KEY_DOWN:
        if(speed.y < MAX_SPEED) speed.y += 1;
        if(speed.y < 0) speed.y += 1;
        if(speed.x > 0) speed.x -= 1;
        else if(speed.x < 0) speed.x += 1;
		break;
	case KEY_RIGHT:
        if(speed.x < MAX_SPEED) speed.x += 1;
        if(speed.x < 0) speed.x += 1;
        if(speed.y > 0) speed.y -= 1;
        else if(speed.y < 0) speed.y += 1;
		break;
	case KEY_LEFT:
        if(speed.x > -MAX_SPEED) speed.x -= 1;
        if(speed.x > 0) speed.x -= 1;
        if(speed.y > 0) speed.y -= 1;
        else if(speed.y < 0) speed.y += 1;
		break;
	default:
        if(speed.x > 0) speed.x -= 1;
        else if(speed.x < 0) speed.x += 1;
        if(speed.y > 0) speed.y -= 1;
        else if(speed.y < 0) speed.y += 1;
		break;
	}
}

int GetMinimap(int y, int x)
{
    if (y < HEIGHT && x < WIDTH)
    {
        return 1;
    }
    else if (y < HEIGHT && x >= WIDTH)
    {
        return 0;
    }
    else if (y >= HEIGHT && x < WIDTH)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

void Rank()
{
    int i, ch;
    char str[NAMELEN+1];
    nptr p;

    //CreateRankList();

    p = head;
    //print rank to screen
    move(0,0);
    printw("               Rank\n");
    for(i = 0; i < MIN(numRank, 10); i++) {
        printw("%6d   %10s    %5d     \n", i+1, p->name, p->score);
        p = p->link;
    }
    move (0, 40);
    printw("Choose : ");
    move (1, 40);
    printw("1. Search My Rank");
    move (2, 40);
    printw("2. Delete Rank");
    move (3, 40);
    printw("3. Exit Rank");
    ch = wgetch(stdscr);

    if((ch == '1')||(ch == '2')) {
		echo();
        move (5, 40);
		printw("Input the name : ");
		getstr(str);
		noecho();

        p = head;
		for(i = 0; i < numRank; i++) {
			if(strcmp(p->name, str) == 0)
				break;
			p = p->link;
		}
        move (6, 40);
		if(i == numRank)
			printw("Search failure : no name in the list\n");
		else {
            if(ch == '1')
			    printw("|%3d %10s %6d |\n", i, p->name, p->score);
            else {
                nptr del;

                numRank--;
                p = head;
                if(!i) {
                    head = p->link;
                    free(p);
			    }
			    else {
                    while(--i)
                        p = p->link;
                    del = p->link;
                    p->link = del->link;
                    free(del);
			    }

                clear();
                p = head;
                move(0,0);
                printw("               Rank\n");
                for(i = 0; i < MIN(numRank, 10); i++) {
                    printw("%6d   %10s    %5d     \n", i+1, p->name, p->score);
                    p = p->link;
                }
                printw("\n       Successfully Deleted\n");
            }
        }
        getch();
    }

    UpdateRankFile();
}

void CreateRankList()
{
    FILE *fp;
    int i;
    nptr new, curr;

    fp = fopen("rank.txt", "rt");

    if(fp == NULL) {
        fopen("rank.txt", "w");
        numRank = 0;
        return;
    }

    if(fscanf(fp, "%d", &numRank) != EOF) {
        head = (nptr)malloc(sizeof(NODE));
        fscanf(fp, "%s %d", head->name, &(head->score));
        head->link = NULL;
        curr = head;
        for(i = 0; i < numRank-1; i++) {
            new = (nptr)malloc(sizeof(NODE));
            fscanf(fp, "%s %d", new->name, &(new->score));
            new->link = NULL;
            curr->link = new;
            curr = curr->link;
        }
    }
    else {
        numRank = 0;
    }

    fclose(fp);
}

void NewRank(int score)
{
    int sameFlag = 0;   //같은 이름을 발견하면 1 = 점수 업데이트
    int sameName = 0;   //같은 이름이 있을 경우 그 위치 표시
    char name[NAMELEN+1];
    
    //CreateRankList();
    clear();
    echo();
    printw("Your name : ");
    getstr(name);
    noecho();

    if(numRank == 0) {
        head = (nptr)malloc(sizeof(NODE));
        strcpy(head->name, name);
        head->score = score;
    }
    else {
        nptr new, same = NULL, p = head;
        new = (nptr)malloc(sizeof(NODE));
        strcpy(new->name, name);
        new->score = score;
        //같은 이름 지우기
        while(p->link != NULL) {
            if(strcmp(p->link->name, new->name) == 0) {
                same = p;
            }
            p = p->link;
        }
        if(same != NULL) {
            if(same->link->score < new->score) {
                nptr temp = same->link;
                same->link = same->link->link;
                free(temp);
                numRank--;
            }
            else {
                free(new);
                return;
            }
        }
        else if(strcmp(head->name, new->name) == 0) {
            if(head->score < new->score) {
                head->score = new->score;
            }
            free(new);
            return;
        }
        p = head;
        //점수로 위치 찾아서 넣기
        while((p->link != NULL)&&(p->link->score > new->score)) {
            p = p->link;
        }
        if((p == head)&&(p->score < new->score)) {
            new->link = p;
            head = new;
        }
        else {
            new->link = p->link;
            p->link = new;
        }
    }
    numRank++;

    UpdateRankFile();
}

void UpdateRankFile()
{
    FILE *fp;
    int i;
    nptr p = head;

    fp = fopen("rank.txt", "wt");

    fprintf(fp, "%d\n", numRank);

    for(int i = 0; i < numRank; i++) {
        fprintf(fp, "%s %d\n", p->name, p->score);
        p = p->link;
    }

    fclose(fp);
}

void FreeAll()
{
    while(head != NULL)
    {
        nptr temp = head;
        head = head->link;
        free(temp);
    }
}