#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h> 
#include <windows.h>

#define LEFT -1
#define RIGHT 1
#define UP 2
#define DOWN -2
#define SNAKE_LEN_MAX 100
#define YES 1
#define NO -1
#define SNAKE_FOOD 3
#define WALL 2
#define WEITH 50
#define HIGH 23

extern int enve[HIGH][WEITH];

typedef struct food
{
	//食物坐标
	int row;										
	int col;

	int flag;										//要出现食物？
}FOOD, *PFOOD;

typedef struct snake
{
	int row[SNAKE_LEN_MAX];
	int col[SNAKE_LEN_MAX];
	int node;										//蛇的节数
	int life;										//蛇活着？
	int dir;										//蛇的移动方向										
}SNAKE, *PSNAKE;

//初始化环境
PSNAKE init(PFOOD fo);

//加载环境
void load(PSNAKE pSnake, PFOOD p_food);

//销毁
void distroy(PSNAKE pSnake);

//输出游戏界面
void print(PSNAKE pSnake);

//判断是否撞墙
void set_life(PSNAKE pSnake);

//蛇移动
void move(PSNAKE pSnake);

//控制蛇方向
void control_dir(PSNAKE pSnake);

//生成食物
void rand_food(PFOOD p_food);

//吃食物
void eat_food(PSNAKE pSnake, PFOOD p_food);

//玩游戏
void play(PSNAKE pSnake, PFOOD p_food);

#endif