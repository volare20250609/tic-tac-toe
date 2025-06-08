#include "game.h"

int main()
{
	int i = 0;

menu:
	Menu();
	printf("Input here:>");
	//´íÎóÊ¾·¶
	//scanf("Type:> %d", &i);
	scanf("%d", &i);
	switch (i)
	{
	case 1:
		goto initiate;
	case 2:
		goto exit;
	default:
		printf("Wrong input!\n");
		Clear_tmp();
		goto menu;
	}

initiate:
	srand((unsigned int)time(NULL));
	char board[ROW][COL] = { 0 };
	Init(board, ROW, COL);
	int stage = 0;

fork:
	if (stage == 1)
	{
		goto computer;
	}
	else
	{
		goto player;
	}

player:
	stage = 1;
	Display(board, ROW, COL);
	PlayerMove(board, ROW, COL);
	goto judge;

computer:
	stage = 0;
	ComputerMove(board, ROW, COL);
	goto judge;

judge:
	if (IsFull(board, ROW, COL))
	{
		Display(board, ROW, COL);
		printf("Board is full!\n");
		goto menu;
	}
	else if (IsWin(board, ROW, COL, ARRAYNUM) == 1)
	{
		Display(board, ROW, COL);
		printf("Player win!\n");
		goto menu;
	}
	else if (IsWin(board, ROW, COL, ARRAYNUM) == 0)
	{
		Display(board, ROW, COL);
		printf("Computer win!\n");
		goto menu;
	}
	else
	{
		goto fork;
	}

exit:
	return 0;
}