#define _CRT_SECURE_NO_WARNINGS

#include "snake.h"

int enve[HIGH][WEITH];

static void load_food(PFOOD p_food)
{
	if (YES == p_food->flag)
		enve[p_food->row][p_food->col] = SNAKE_FOOD;
}

static void load_snake(PSNAKE pSnake)
{
	int i = 0;

	enve[pSnake->row[0]][pSnake->col[0]] = WALL;
	for (i = 1; i < pSnake->node; i++)
	{
		enve[pSnake->row[i]][pSnake->col[i]] = WALL;
	}
}

PSNAKE init(PFOOD p_food)
{
	SNAKE tmp = { { 1 }, { 1 }, 1, RIGHT, YES };
	PSNAKE s = (PSNAKE)malloc(sizeof(SNAKE));
	
	*s = tmp;

	assert(p_food);
	
	p_food->flag = YES;
	p_food->col = 10;
	p_food->row = 10;

	load(s, p_food);
	
	return s;
}

void load(PSNAKE pSnake, PFOOD p_food)
{
	int i = 0, j = 0;

	for (i = 0; i < HIGH; i++)
	{
		for (j = 0; j < WEITH; j++)
		{
			if (i == 0 || j == WEITH - 1 || j == 0 || i == HIGH - 1)
				enve[i][j] = WALL;
			else
				enve[i][j] = ' ';
		}
	}
	load_snake(pSnake);
	load_food(p_food);
}

void distroy(PSNAKE pSnake)
{ 
	assert(pSnake);

	free(pSnake);
	pSnake = NULL;
}
void print(PSNAKE pSnake)
{
	int i = 0, j = 0;
	Sleep(300);
	system("CLS");
	printf("Score: %d\n", (pSnake->node - 1) * 10);
	for (i = 0; i < HIGH; i++)
	{
		for (j = 0; j < WEITH; j++)
		{
			printf("%c", enve[i][j]);
		}
		if (HIGH - 1 != i)
			printf("\n");
	}
}

void set_life(PSNAKE pSnake)
{
	int i = 0, j = 0;

	assert(pSnake);

	//撞到墙死?
	if (0 == pSnake->col[0] || WEITH - 1 == pSnake->col[0])
	{
		pSnake->life = NO;
		return;
	}
	else if (0 == pSnake->row[0] || HIGH - 1 == pSnake->row[0])
	{
		pSnake->life = NO;
		return;
	}
	//撞到自己死?
	for (i = 1; i < pSnake->node; i++)			
	{
		if (pSnake->col[0] == pSnake->col[i] && pSnake->row[0] == pSnake->row[i])
		{
			pSnake->life = NO;
			return;
		}
	}

	pSnake->life = YES;
}

void control_dir(PSNAKE pSnake)
{
	int dire = pSnake->dir;

	assert(pSnake);

	if (GetAsyncKeyState(VK_UP) && pSnake->dir != -2)
	{
		pSnake->dir = 2;
	}
	else if (GetAsyncKeyState(VK_DOWN) && pSnake->dir != 2)
	{
		pSnake->dir = -2;
	}
	else if (GetAsyncKeyState(VK_LEFT) && pSnake->dir != 1)
	{
		pSnake->dir = -1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && pSnake->dir != -1)
	{
		pSnake->dir = 1;
	}
}


void move(PSNAKE pSnake)
{
	assert(pSnake);

	switch (pSnake->dir)
	{
	case 2:
		memmove(pSnake->row + 1, pSnake->row, (pSnake->node - 1) * sizeof(int));
		memmove(pSnake->col + 1, pSnake->col, (pSnake->node - 1) * sizeof(int));
		pSnake->row[0] -= 1;
		break;
	case -1:
		memmove(pSnake->row + 1, pSnake->row, (pSnake->node - 1) * sizeof(int));
		memmove(pSnake->col + 1, pSnake->col, (pSnake->node - 1) * sizeof(int));
		pSnake->col[0] -= 1;
		break;
	case -2:
		memmove(pSnake->row + 1, pSnake->row, (pSnake->node - 1) * sizeof(int));
		memmove(pSnake->col + 1, pSnake->col, (pSnake->node - 1) * sizeof(int));
		pSnake->row[0] += 1;
		break;
	case 1:
		memmove(pSnake->row + 1, pSnake->row, (pSnake->node - 1) * sizeof(int));
		memmove(pSnake->col + 1, pSnake->col, (pSnake->node - 1) * sizeof(int));
		pSnake->col[0] += 1;
		break;
	default:
		break;
	}
}

void rand_food(PFOOD p_food)
{
	assert(p_food);

	srand((unsigned)time(NULL));
	if (NO == p_food->flag)
	{
		p_food->flag = YES;
		p_food->col = rand() % (HIGH - 2) + 1;
		p_food->col = rand() % (WEITH - 2) + 1;
	}
}
void eat_food(PSNAKE pSnake, PFOOD p_food)
{
	assert(NULL != pSnake && NULL != p_food);

	if (NO == p_food->flag)
		return;
	if (pSnake->node >= SNAKE_LEN_MAX)
	{
		p_food->flag = NO;
		return;
	}
	if (pSnake->row[0] == p_food->row && pSnake->col[0] == p_food->col)
	{
		(pSnake->node)++;
		memmove(pSnake->row + 1, pSnake->row, (pSnake->node - 1) * sizeof(int));
		memmove(pSnake->col + 1, pSnake->col, (pSnake->node - 1) * sizeof(int));
		pSnake->row[0] = p_food->row;
		pSnake->col[0] = p_food->col;
		p_food->flag = NO;
	}
}


void play(PSNAKE pSnake, PFOOD p_food)
{
	system("CLS");
	while (1)
	{
		print(pSnake);
		control_dir(pSnake);
		move(pSnake);
		load(pSnake, p_food);
		set_life(pSnake);
		if (NO == pSnake->life)
			return;
		eat_food(pSnake, p_food);
		rand_food(p_food);
		load(pSnake, p_food);
	}
}