#include <iostream>
#include <vector>
#include <chrono>
#include <Windows.h>
#include <thread>


class game_of_life {
public:
	int width;
	int height;
	bool status;
	std::vector<bool>board;
	std::vector<bool>boardAfterSimulate;
		
	void setStatusAfterSimulate(int x, int y, bool status) {
		boardAfterSimulate[y * width + x] = status;
	}
	bool getStatus(int x, int y) {
		if (x >= width || x < 0 || y <0 || y >= height) {
			return 0;

		}
		return board[y * width + x];
	}

	void simulateCell(int i) {
		simulateCell(i % width, i / width);
	}

	void simulateCell(int x, int y) {

		int sum_living = getStatus(x - 1, y - 1) + getStatus(x, y - 1) + getStatus(x + 1, y - 1) + getStatus(x - 1, y) + getStatus(x + 1, y) + getStatus(x - 1, y + 1) + getStatus(x, y + 1) + getStatus(x + 1, y + 1);
		if (sum_living < 4 && sum_living >1 && getStatus(x, y) == 1)
		    setStatusAfterSimulate(x, y, 1);
		else if (sum_living >= 3 && getStatus(x, y) == 0)
			setStatusAfterSimulate(x, y, 1);
		else
			setStatusAfterSimulate(x, y, 0);
	}	
	void printBoard() {
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (getStatus(j, i) == 1)
					std::cout << 'O';
				else
					std::cout << '.';
			}
			std::cout << std::endl;
		}
	}
};
class application {
public:

	game_of_life game;
	application() {
		game.width = 4;
		game.height = 4;
		//for (int i = 0; i < game.width * game.height; i++) {
		//	game.board.push_back(rand() % 3);
		//}
		game.board = { 0,1,0,0,
			           1,0,0,1,
			           1,0,0,1,
			           0,0,1,0 };

		for (int i = 0; i < game.width * game.height; i++) {
			game.boardAfterSimulate.push_back(0);
		}
	}
};

class update_game_of_life {

};


int main() {
	application app;

	int a;
	int x = 0;
		while (x != 10) {
			app.game.printBoard();

			for (int i = 0; i < 10; i++) {
				app.game.simulateCell(i);
			}

			for (int i = 10; i < app.game.board.size(); i++) {
				app.game.simulateCell(i);
			}

			app.game.board = app.game.boardAfterSimulate;
			
			//Sleep(500);
			std::cout << "next" << std::endl;
			std::cin >> a;
			system("CLS");
			x++;
		}
	
	return 0;
}
