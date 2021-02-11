#include <iostream>
#include <vector>
using namespace std;
struct spot {
	int row;
	int col;
};
class TicTacToe
{
private:
	char** board;
	char playerOne;
	char playerTwo;
	int turn;
	int count;
	bool gameFinished;
public:
	TicTacToe() {
		gameFinished = false;
		board = new char* [3];
		for (int i = 0; i < 3; i++) {
			board[i] = new char[3];
			board[i][0] = board[i][1] = board[i][2] = ' ';
		}
		playerOne = 'x';
		playerTwo = 'o';
		turn = 1;
		count = 0;
	}
	char winner() {
		for (int i = 0; i < 3; i++) {
			if ((board[i][0] == 'o') && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
				return 'o';
			if ((board[i][0] == 'x') && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
				return 'x';
		}
		for (int i = 0; i < 3; i++) {
			if ((board[0][i] == 'o') && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
				return 'o';
			if ((board[0][i] == 'x') && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
				return 'x';
		}
		if (board[0][0] == 'o' && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
			return 'o';
		if (board[0][0] == 'x' && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
			return 'x';
		if (board[0][2] == 'o' && (board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
			return 'o';
		if (board[0][2] == 'x' && (board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
			return 'x';
		return NULL;
	}
	void draw() {
		system("CLS");
		cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
		cout << "---------" << endl;
		cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
		cout << "---------" << endl;
		cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
	}
	void play() {
		draw();
		if (gameFinished || count == 9) {
			endGame();
			return;
		}
		if (turn == 1) {
			turn = 2;
			count++;
			move(playerOne);
		}
		else {
			turn = 1;
			count++;
			moveAI(playerTwo);
		}
	}
	void moveAI(char player) {
		spot bestMove = findBestMove();
		board[bestMove.row][bestMove.col] = player;
		if (winner() != NULL)
			gameFinished = true;
		play();
	}
	void move(char player) {
		int choice;
		cout << "It's " << player << " turn!" << endl;
		cout << "Enter Your choice (1-9) : ";
		cin >> choice;
		int row = (choice - 1) / 3;
		int col = (choice - 1) % 3;
		if (choice > 9 || choice < 1) {
			cout << "Invalid input!" << endl;
			move(player);
		}
		if (board[row][col] != ' ') {
			cout << "Cell is occupied!" << endl;
			move(player);
		}
		else {
			board[row][col] = player;
			if (winner() != NULL)
				gameFinished = true;
			play();
		}
	}
	void endGame() {
		system("CLS");
		draw();
		cout << "\n\n";
		char isWinner = winner();
		if (isWinner == NULL)
			cout << "It's a DROW" << endl;
		else
			cout << "The winner is: " << isWinner << endl;
	}
	vector<spot> isAvailable() {
		vector<spot> emptySpots;
		spot tempCell;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == ' ') {
					tempCell.row = i;
					tempCell.col = j;
					emptySpots.push_back(tempCell);
				}
			}
		}
		return emptySpots;
	}

	spot findBestMove() {
		vector<spot> emptySpots = isAvailable();
		spot bestSpot;
		bestSpot.row = bestSpot.col = -1;
		int bestVal = -1000;
		for (spot each : emptySpots) {
			board[each.row][each.col] = 'o';
			int moveVal = minimax(false);
			board[each.row][each.col] = ' ';
			if (moveVal > bestVal) {
				bestSpot = each;
				bestVal = moveVal;
			}
		}
		return bestSpot;
	}

	int minimax(bool isMax) {
		if (isAvailable().size() == 0 && winner() == NULL) {
			return 0;
		}
		char scoreTemp = winner();
		if (scoreTemp == 'o') {
			return 1;
		}
		if (scoreTemp == 'x') {
			return -1;
		}
		if (isMax) {
			vector<spot> emptySpots = isAvailable();
			int best = -100000000;
			for (spot emptySpot : emptySpots) {
				board[emptySpot.row][emptySpot.col] = 'o';
				best = max(best, minimax(!isMax));
				board[emptySpot.row][emptySpot.col] = ' ';
			}
			return best;
		}
		else {
			vector<spot> emptySpots = isAvailable();
			int best = 100000000;
			for (spot emptySpot : emptySpots) {
				board[emptySpot.row][emptySpot.col] = 'x';
				best = min(best, minimax(!isMax));
				board[emptySpot.row][emptySpot.col] = ' ';
			}
			return best;
		}
	}

	~TicTacToe() {
		for (int i = 0; i < 3; i++) delete[]board[i];
		delete[] board;
	}
};

int main() {
	while (true) {
		TicTacToe game;
		game.play();
		system("pause");
		system("CLS");
	}
	return 0;
}