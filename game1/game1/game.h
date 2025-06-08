#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 5
#define COL 5
#define ARRAYNUM 3

void Menu(void);

char* GetPointer(char* board, int x, int y, int row);

void Init(char* board, int row, int col);

void Display(char* board, int row, int col);

void Clear_tmp();

void PlayerMove(char* board, int row, int col);

void ComputerMove(char* board, int row, int col);

int IsFull(char* board, int row, int col);

int IsWin(char* board, int row, int col, int arraynum);