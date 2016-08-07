#define _CRT_SECURE_NO_WARNINGS
#include "annotation_converter.h"
#include <assert.h>

void converter_NULL(FILE *read, FILE *write, STATE_TYPE *pstate)
{
	int first = 0, second = 0;

	while (*pstate == NULL_STATE)
	{
		first = fgetc(read);
		switch (first)
		{
		case '/':
		{
			second = fgetc(read);
			switch (second)
			{
			case '/':
				fputc(first, write);
				fputc(second, write);
				*pstate = CPP_STATE;
				break;
			case '*':
				fputc(first, write);
				fputc('/', write);
				*pstate = C_STATE;
				break;
			default:
				fputc(first, write);
				fputc(second, write);
				break;
			}
		}
			break;
		case EOF:
			*pstate = END_STATE;
			break;
		default:
			fputc(first, write);
			break;
		}
	}
}

void converter_c(FILE *read, FILE *write, STATE_TYPE *pstate)
{
	int first = 0, second = 0, third = 0;
	int flag = 0;

	while (C_STATE == *pstate)
	{	
		if (flag == 0)
			first = fgetc(read);
		switch (first)
		{
		case '*':
		{
			second = fgetc(read);
			if ('/' == second)
			{	
				third = fgetc(read);
				if (third != '\n')
					fputc('\n', write);
				ungetc(third, read);
				//flag = 0;
				*pstate = NULL_STATE;
			}
			else if ('*' == second)
			{
				fputc(first, write);
				first = second;
				flag = 1;
			}
			else
			{
				fputc(first, write);
				fputc(second, write);
			}
		}
			break;
		case '\n':
			fputc(first, write);
			fputc('/', write);
			fputc('/', write);
			break;
		case EOF:
			*pstate = END_STATE;
			break;
		default:
			fputc(first, write);
			break;
		}
	}
}

void converter_cpp(FILE *read, FILE *write, STATE_TYPE *pstate)
{
	int first = 0, second = 0;

	while (CPP_STATE == *pstate)
	{
		first = fgetc(read);
		switch (first)
		{
		case '\n':
			fputc(first, write);
			*pstate = NULL_STATE;
			break;
		case EOF:
			*pstate = END_STATE;
			break;
		default:
			fputc(first, write);
			break;
		}
	}
}

void converter_core(FILE *read, FILE *write)
{
	STATE_TYPE code_state = NULL_STATE;

	assert(read);
	assert(write);
	while (1)
	{
		switch (code_state)
		{
		case NULL_STATE:
			converter_NULL(read, write, &code_state);
			break;
		case C_STATE:
			converter_c(read, write, &code_state);
			break;
		case CPP_STATE:
			converter_cpp(read, write, &code_state);
			break;
		case END_STATE:
			return;
			break;
		default:
			break;
		}
	}
}

void converter()
{
	FILE *read = NULL;
	FILE *write = NULL;

	read = fopen(INPUT_FILE_NAME, "r");
	if (NULL == read)
	{
		perror("打开源文件错误\n");
		exit(0);
	}
	write = fopen(OUTPUT_FILE_NAME, "w");
	if (NULL == write)
	{
		perror("打开目标文件错误\n");
		fclose(read);
		exit(0);
	}

	converter_core(read, write);

	fclose(read);
	fclose(write);

}
