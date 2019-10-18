#include<iostream>
#include <string>
using namespace std;
void GameBoard();
bool WinnerCheck(int n, int m);
int InsertP(int c, char piece);
char grid[6][7];	//Make sure the grid is available for whole program

void GameBoard() {								//Drawing the gameboard
	cout << " 1   2   3   4   5   6   7\n";		//Numbers for 7 colunms at the top of the gameboard.
	for (int r = 0; r <= 5; r++)				//r Represents 6 rows, c represents 7 colunms
	{
		for (int c = 0; c <= 6; c++) cout << char(218) << char(196) << char(191) << " ";		//Using specific characters to build rectangles
		cout << '\n';
		for (int c = 0; c <= 6; c++) cout << char(179) << grid[r][c] << char(179) << " ";		//grid[r][c] Will show the piece in the middle of these rectangles.
		cout << '\n';
		for (int c = 0; c <= 6; c++) cout << char(192) << char(196) << char(217) << " ";
		cout << '\n';
	}
}

int main(){
	bool restart = false;								//Restart condition
	do {
		for (int r = 0; r <= 5; r++) {					//Initializing the gameboard.
			for (int c = 0; c <= 6; c++)
				grid[r][c] = ' ';
		}
		GameBoard();									//Show the gameboard when game starts
		int colunm_Num;									//Stores players' inputs
		int row_Num = 0;									//
		int space_Occupied = 0;							//Use to check the grid is not full.
		bool gameOver = false;							//Will be changed to true when game is won and will exit while loop
		char player = 88;								//Player2's piece. When game starts, it's set to 88 so first turn is player1
		char answer;
		while (!gameOver) {								//will stop when game is won, ! means NOT makes the oppisite be checked
			if (row_Num != -1) {							//check if there was a error in the last drop
				if (player == 88) {						//If player 2 lasted dropped a piece so its player 1s turn，
					cout << "player 1's turn! Type the column number to insert a piece.";
					player = 254;						//char of players piece
				}
				else {
					cout << "player 2's turn! Type the column number to insert a piece.";
					player = 88;						//char of player piece
				}
			}
			while (true) {								//will run untill 'break;'
				if (space_Occupied == 42) break;		//if draw
				cin >> colunm_Num;						//get user input
				colunm_Num--;							//take off 1 to account for arrays starting at 0 not 1
				if (colunm_Num <= 6 && colunm_Num >= 0) break;							//if within valid range stop loop
				else cout << "\nInvalid input\nplease enter a value between 1 and 7 :";				//ask for input and loop again

				if (cin.fail())							//Detects the type of players' inputs
				{
					cin.clear();						//Stops storing cin
					char trashbin;						//To store invalid inputs
					cin >> trashbin;					//Stores invalid inputs 
				}

			}
			if (space_Occupied == 42) break;						//If the grid is full and no one wins, it's a draw game.

			row_Num = InsertP(colunm_Num, player);					//Gets the piece's location of the row
			if (row_Num == -1)	cout << "\nColomn is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
			else {
				gameOver = WinnerCheck(row_Num, colunm_Num);		//check if game is run
				space_Occupied++;									//Adds 1 each time a space is occupied
				system("cls");										//Clears the screen to show one gameboard each time insert a piece
				GameBoard();										//Shows updated board
			}
		}


		if (space_Occupied == 42) {									//If the grid is full and no one wins, it's a draw game.
			cout << "No winner, Game was draw\nWould you like to play again? \nEnter y to play again, other keys to quit\n";
			cin >> answer;
			if (answer == 'y' || answer == 'Y') {					//If players enter y or Y, restarts the game.
				restart = true;
			}
			else restart = false;									//If players enter other keys, exits.

		}
		if (player == 88) {											//Check if player2 won the game
			cout << "Player 2 won the game!\nWould you like to play again? \nEnter y to play again, other keys to quit\n";
			cin >> answer;
			if (answer == 'y' || answer == 'Y') {
				restart = true;
			}
			else restart = false;
		}
		else {														//Else player1 won the game
			cout << "Player 1 won the game!\nWould you like to play again? \nEnter y to play again, other keys to quit\n";
			cin >> answer;
			if (answer == 'y' || answer == 'Y') {
				restart = true;
			}
			else restart = false;
		}
	} while (restart);
	system("pause");
	return 0;
}



int InsertP(int c, char piece) {					//Pieces insert function
	if (c >= 0 && c <= 6)							//Check the value p that players typed is a valid number between 0 and 6 for 1 to 7 colunms
	{
		if (grid[0][c] == ' ') {					//Check the top rectangle for each colunm is empty or not.
			int i;
			for (i = 0; grid[i][c] == ' '; i++)		//Check which row in colunm "p" is occupied.
				if (i == 5) {						//If this colunm is empty, than place a piece at the bottom.
					grid[i][c] = piece;
					return i;						//Returns row 5.
				}
			i--;									//If current row in colunm "p" is occupied, place a piece above this row.
			grid[i][c] = piece;						//Put the piece at current empty place
			return i;								//Returns the value of current row

		}
		else {
			return -1;
		}

	}
	else {
		return -1;
	}

}


bool WinnerCheck(int n, int m) {						//This is the function for winner checking
	int vertical_Check = 1;								//"1" means there are 1 piece
	int horizontal_Check = 1;
	int diagonal_CheckL = 1;
	int diagonal_CheckR = 1;
	char piece = grid[n][m];							//Piece location
	int i;//vertical
	int j;//horizontal
	
	//Vertical checking
	for (i = n + 1; grid[i][m] == piece && i <= 5; i++, vertical_Check++);			//Check the space below the just added piece
	if (vertical_Check >= 4)return true;					//Return true if there are 4 or more pieces in current colunm
	

	//Horizontal checking
	for (j = m + 1; grid[n][j] == piece && j <= 6; j++, horizontal_Check++);				//Check the space on the right of added piece
	for (j = m - 1; grid[n][j] == piece && j >= 0; j--, horizontal_Check++); 			//Check the space on the left of added piece
	if (horizontal_Check >= 4) return true;				//Return true if there are 4 or more pieces in current row
	
	//Left slash diagonal checking
	for (i = n - 1, j = m - 1; grid[i][j] == piece && i >= 0 && j >= 0; diagonal_CheckL++, i--, j--);			//Check the space on the top left of added piece
	for (i = n + 1, j = m + 1; grid[i][j] == piece && i <= 5 && j <= 6; diagonal_CheckL++, i++, j++);			//Check the space on the bottom right of added piece
	if (diagonal_CheckL >= 4) return true;				//Return true if there are 4 or more pieces diagonally(left slash) are lined up
	
	//Right slash diagonal checking
	for (i = n - 1, j = m + 1; grid[i][j] == piece && i >= 0 && j <= 6; diagonal_CheckR++, i--, j++);			//Check the space on the top right of added piece
	for (i = n + 1, j = m - 1; grid[i][j] == piece && i <= 5 && j >= 0; diagonal_CheckR++, i++, j--);			//Check the space on the bottom left of added piece
	if (diagonal_CheckR >= 4) return true;				//Return true if there are 4 or more pieces diagonally(right slash) are lined up

	return false;
}