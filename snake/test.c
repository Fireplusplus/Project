#define _CRT_SECURE_NO_WARNINGS

#include "snake.h"

void menu()
{
	printf("snake:\n");
	printf("\n");
	printf("\n");
	printf("\t\t1. start\n");
	printf("\t\t2. exit\n");
	printf("\t    please choose: ");
}

enum option
{
	START = 1,
	EXIT
};
int main()
{
	FOOD food;
	PSNAKE p_snake = init(&food);

	int input = 1;
	
	while (input)
	{
		menu(); 
		scanf("%d", &input);
		switch (input)
		{
		case START:
			play(p_snake, &food);
			input = 0;
			print(p_snake);
			printf("\tGame is Over....:(\n");
			break;
		case EXIT:
			input = 0;
			break;
		}
	}

	distroy(p_snake);
	system("pause");
	return 0;
}
