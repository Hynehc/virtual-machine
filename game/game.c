#include "game.h"

int x = 0;
int y = 0;

void Menu()
{
	printf("########################\n");
	printf("## 1.play      0.exit ##\n");
	printf("########################\n");
}

int ChessCount(int board[][COL], int row, int col, enum Dir d)
{
	int _x = x - 1;
	int _y = y - 1;
	int count  = 0;
	while (1)
	{
		switch(d)
		{
			case LEFT:
				_y -- ;
				break;
			case RIGHT:
				_y ++ ;
				break;
			case UP:
				_x -- ;
				break;
			case DOWN:
				_x ++ ;
				break;
			case LEFT_UP:
				_y -- , _x -- ;
				break;
			case LEFT_DOWN:
				_y -- , _x ++ ;
				break;
			case RIGHT_UP:
				_y ++ , _x -- ;
				break;
			case RIGHT_DOWN:
				_y ++ , _x ++ ;
				break;
			default:
				break;
		}
		if (_x < 0 || _x > row - 1 || _y < 0 || _y > col - 1) break;
		if (board[x - 1][y - 1] == board[_x][_y]) count ++ ;
		else break;
	}
	return count;
}

int IsOver(int board[][COL], int row, int col)
{
	int count1 = ChessCount(board, row, col, LEFT)      + ChessCount(board, row, col, RIGHT)      + 1;
	int count2 = ChessCount(board, row, col, UP)        + ChessCount(board, row, col, DOWN)       + 1;
	int count3 = ChessCount(board, row, col, LEFT_UP)   + ChessCount(board, row, col, RIGHT_DOWN) + 1;
	int count4 = ChessCount(board, row, col, LEFT_DOWN) + ChessCount(board, row, col, RIGHT_UP)   + 1;
	if (count1 >= 5 || count2 >= 5 || count3 >= 5 || count4 >= 5)
	{
		if (board[x - 1][y - 1] == PLAYER1)
			return PLAYER1_WIN;
		else 
			return PLAYER2_WIN;
	}
	for (int i = 0; i < row; i++ )
		for (int j = 0; j < col; j ++ )
			if (board[i][j] == 0)
				return NEXT;
	return DRAW;
}

void ShowBoard(int board[][COL],int row, int col)
{	printf("  ");
	for (int i = 1; i <= col; i ++ )
		printf("%3d", i);
	printf("\n");
	for (int i = 0; i < row; i ++ )
	{
		printf("%2d ", i + 1);
		for (int j = 0; j < col; j ++ )
		{
			if (board[i][j] == 0) printf(" . ");
			else if (board[i][j] == PLAYER1) printf(" x ");
			else printf(" o ");
		}
		printf("\n");
	}
}

void PlayerMove(int board[][COL],int row, int col, int who)
{
	while (1)
	{
		printf("Player[%d] Please Enter Your Pos# ", who);
		scanf("%d %d", &x, &y);
		if (x < 1 || x > row || y < 1 || y > col) 
		{
			printf("Pos Is Wrong\n");
			continue;
		}	
		if (board[x - 1][y - 1] != 0)
		{
			printf("Pos Is Occupied\n");
			continue;
		}
		board[x - 1][y - 1] = who;
		break;
	}
}

void Game()
{
	printf("welcome to game\n");
	int board[ROW][COL];
	memset(board, 0, sizeof board);
	int result = NEXT;
	do
	{
		ShowBoard(board, ROW, COL);
		PlayerMove(board, ROW, COL, PLAYER1);
		result = IsOver(board, ROW, COL);
		if (NEXT != result)
		{
			break;
		}

		ShowBoard(board, ROW, COL);
		PlayerMove(board, ROW, COL, PLAYER2);
		result = IsOver(board, ROW, COL);
		if (NEXT != result)
		{
			break;
		}
	}while (1);
	// p1-win or p2-win or draw	
	switch(result)
	{
		case PLAYER1_WIN:
			printf("congratulation player1 win!\n");
			break;
		case PLAYER2_WIN:
			printf("congratulation player2 win!\n");
			break;
		case DRAW:
			printf("sorry, nobody win\n");
			break;
		default:
			break;
	}
}
