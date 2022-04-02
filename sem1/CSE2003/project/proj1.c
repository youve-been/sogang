#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>

int b[25][40], time_out, game_over, n, m;
int obs, period = 0;
int score = -1;

void init(){
	n = 25, m = 40;
	time_out = game_over = 0;

	/* user code */
	/* init board */
	for(int i = 0 ; i < 25; i++) {
		for(int j = 0; j < 40; j++)
			b[i][j] = ' ';
	}
	n /= 2;
	m /= 4;
	b[n][m] = '@';
}

void draw_board(){
	system("clear");

	/* user code */
	printf("Score : ");
	if(score<0)
		printf("\033[31m0\033[0m\n");
	else
		printf("\033[31m%d\033[0m\n", score);

	printf(" \n");
	for(int i = 0; i < 25; i++) {
		for(int j = 0; j < 40; j++) {
			if(b[i][j] == '@')
				printf("\033[36m%c\033[0m", b[i][j]);
			else
				printf("\033[32m%c\033[0m", b[i][j]);
		}
		printf("\n");
	}
}

int temp_val = 0;

void Do(int sig) {
	system("clear");
	

	/* user code */
	/* update board b[25][40] */
	/* update bird position*/	

	srand(time(NULL));

	for(int i = 0 ; i < 25; i++) {
		for(int j = 0; j < 40; j++)
			b[i][j] = b[i][j+1];
	}

	if(b[n-1][m-1] == '+')
		game_over = 1;

	b[n][m-1] = ' ';
	n++;

	if(b[n][m] == '+')
		game_over = 1;

	b[n][m] = '@';

	if(period > 9) {
		for(int i = 0; i < 25; i++)
			b[i][39] = ' ';

		if(period == 14)
			score++;
	}
	else {
		if(period == 0)
			obs = rand() % 9;

		for(int i = 0; i < 25; i++) {
			if(i<obs+3 || i>obs+12)
				b[i][39] = '+';
			else
				b[i][39] = ' ';
		}
	}
	period++;

	if(period == 25)
		period = 0;

	if(n<0 || n> 24)
		game_over = 1;

	/* do not erase this code */
	time_out = 0;
}

int getch(void)
{
	char   ch;
	int   error;
	static struct termios Otty, Ntty;

	fflush(stdout);
	tcgetattr(0, &Otty);
	Ntty = Otty;
	Ntty.c_iflag = 0;
	Ntty.c_oflag = 0;
	Ntty.c_lflag &= ~ICANON;
#if 1
	Ntty.c_lflag &= ~ECHO;
#else
	Ntty.c_lflag |= ECHO;
#endif
	Ntty.c_cc[VMIN] = 0;
	Ntty.c_cc[VTIME] = 1;

#if 1
#define FLAG TCSAFLUSH
#else
#define FLAG TCSANOW
#endif

	if (0 == (error = tcsetattr(0, FLAG, &Ntty)))
	{
		error = read(0, &ch, 1);
		error += tcsetattr(0, FLAG, &Otty);
	}

	return (error == 1 ? (int)ch : -1);
}


int GetCommand() {
	int ch = getch();

	switch (ch)
	{
	case 'd':
	case 'D': return 0;
	case 'w':
	case 'W': return 1;
	case 'a':
	case 'A': return 2;
	case 's':
	case 'S': return 3;
	default: return -1;
	}

	return -1;
}


int main() {
	int command = -1;
	srand(time(NULL));
	static struct sigaction act, oact;
	act.sa_handler = Do;
	sigaction(SIGALRM, &act, NULL);

	init();
	draw_board();

	int count = 0;

	do {

		if (time_out == 0) {
			ualarm(200000, 0); /* 20,000 = 0.2 sec, call Do function */
			time_out = 1;
		}

		command = GetCommand();

		/* user code */
		if(command > -1) {
			b[n][m] = ' ';
			n -= 3;
			b[n][m] = '@';
			count++;
		}
		else {
			if(count == 1) {
				b[n][m] = ' ';
				n -= 2;
				b[n][m] = '@';
				count = 0;
			}
		}
		
		draw_board();

	} while (!game_over);

	system("clear");
	printf("game over!\n");
}
