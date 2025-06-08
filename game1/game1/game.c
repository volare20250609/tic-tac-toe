#include "game.h"

void Menu(void)
{
	printf("#######################\n");
	printf("###### 1. Start #######\n");
	printf("###### 2. Exit  #######\n");
	printf("#######################\n");
}

char* GetPointer(char* board, int x, int y, int row)
{
	return board + x * row + y;
}

void Init(char* board, int row, int col)
{
	int i = 0;
	int j = 0;
	//错误示范
	//for (i = 0; i < row; i++)
	//for (i = 0; i < row; i += ROW)
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			//错误示范
			//*(board + row + col) = ' ';
			//用GetPointer替代
			// *(board + i + j) = ' ';
			*GetPointer(board, i, j, row) = ' ';
		}
	}
}

void Display(char* board, int row, int col)
{
	int i = 0;
	int j = 0;
	//错误示范
	//for (i = 0; i < row; i++)
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			//错误示范
			//printf(" %c ", *(board + row + col));
			printf(" %c ", *GetPointer(board, i, j, row));
			if (j != col - 1)
			{
				printf("|");
			}
			else
			{
				printf("\n");
			}
		}
		//错误示范
		//if (i = !(row - 1))
		//!和=写反了，会出现死循环，是因为i被重新赋值，无法跳出for循环
		if (i != (row - 1))
		{
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j != col - 1)
				{
					printf("|");
				}
				else
				{
					printf("\n");
				}
			}
		}
	}
}

void Clear_tmp()
{
loop:
	if (getchar() != '\n')
	{
		goto loop;
	}
}

void PlayerMove(char* board, int row, int col)
{
	int x = 0;
	int y = 0;
	printf("Your turn.\n");
	while (1)
	{
		Clear_tmp();
		printf("Input like x,y:> ");
		scanf("%d,%d", &x, &y);
		int act_x = x - 1;
		int act_y = y - 1;
		//错误示范
		//int* position = board + act_x * row + act_y;
		//这个功能封装成函数
		//char* position = board + act_x * row + act_y;
		
		char* pointer = GetPointer(board, act_x, act_y, row);

		if (*pointer != ' ')
		{
			printf("Occupied!\n");
		}
		else if (
			(act_x < 0) || (act_x > row)
			||
			(act_y < 0) || (act_y > col)
			)
		{
			printf("Input location beyond board!\n");
		}
		else
		{
			*pointer = 'P';
			break;
		}
	}
}

void ComputerMove(char* board, int row, int col)
{
	int x = 0;
	int y = 0;
	//错误示范
	//int* pointer = 0;
	char* pointer = 0;
reloop:
	x = rand() % row;
	y = rand() % col;
	pointer = GetPointer(board, x, y, row);

	if (*pointer != ' ')
	{
		goto reloop;
	}
	else
	{
		*pointer = 'C';
		printf("Computer placed %d,%d\n", x+1, y+1);
	}
}

int IsFull(char* board, int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			//错误示范
			//if (GetPointer(board, i, j, row) == ' ')
			if (*GetPointer(board, i, j, row) == ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}

int IsWin(char* board, int row, int col, int arraynum)
{
	int i = 0;
	int j = 0;
	int CCount = 0;
	int PCount = 0;

CountEveryRow:
	for (i = 0; i < row; i++)
	{
		CCount = 0;
		PCount = 0;
		for (j = 0; j < col; j++)
		{
			if ((*GetPointer(board, i, j, row) == 'C'))
			{
				CCount++;
				PCount = 0;
			}
			else if (*GetPointer(board, i, j, row) == 'P')
			{
				PCount++;
				CCount = 0;
			}
			else
			{
				CCount = 0;
				PCount = 0;
			}
			if (CCount >= arraynum)
			{
				return 0;
			}
			else if (PCount >= arraynum)
			{
				return 1;
			}
		}
	}

CountEveryCol:
	for (j = 0; j < row; j++)
	{
		CCount = 0;
		PCount = 0;
		for (i = 0; i < col; i++)
		{
			if (*GetPointer(board, i, j, row) == 'C')
			{
				CCount++;
				PCount = 0;
			}
			else if (*GetPointer(board, i, j, row) == 'P')
			{
				PCount++;
				CCount = 0;
			}
			else
			{
				CCount = 0;
				PCount = 0;
			}
			if (CCount >= arraynum)
			{
				return 0;
			}
			else if (PCount >= arraynum)
			{
				return 1;
			}
		}
	}

CountEveryLowerDiagonal:
	for (i = 0; i < row; i++)
	{
		CCount = 0;
		PCount = 0;
		for (j = 0; (j < col) && (i + j) < row ; j++)
		{
			if (*GetPointer(board, i + j, j, row) == 'C')
			{
				CCount++;
				PCount = 0;
			}
			else if (*GetPointer(board, i + j, j, row) == 'P')
			{
				PCount++;
				CCount = 0;
			}
			else
			{
				CCount = 0;
				PCount = 0;
			}
			if (CCount >= arraynum)
			{
				return 0;
			}
			else if (PCount >= arraynum)
			{
				return 1;
			}
		}
	}

CountEveryUpperDiagonal:
	for (j = 1; j < col; j++)
	{
		CCount = 0;
		PCount = 0;
		for (i = 0; (i < row) && (i + j) < col; i++)
		{
			if (*GetPointer(board, i, i + j, row) == 'C')
			{
				CCount++;
				PCount = 0;
			}
			else if (*GetPointer(board, i, i + j, row) == 'P')
			{
				PCount++;
				CCount = 0;
			}
			else
			{
				CCount = 0;
				PCount = 0;
			}
			if (CCount >= arraynum)
			{
				return 0;
			}
			else if (PCount >= arraynum)
			{
				return 1;
			}
		}
	}

ContinueGame:
	return -1;
}