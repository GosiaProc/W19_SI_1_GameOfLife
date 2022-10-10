#include <iostream>
#include <vector>
#include <chrono>
#include <Windows.h>
#include <thread>
#include <functional>


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
		game.width = 150;
		game.height = 60;
		for (int i = 0; i < game.width * game.height; i++) {
			game.board.push_back(rand() % 3);
		}
		//game.board = { 0,1,0,0,
		//	           1,0,0,1,
		//	           1,0,0,1,
		//	           0,0,1,0 };

		for (int i = 0; i < game.width * game.height; i++) {
			game.boardAfterSimulate.push_back(0);
		}
	}

	void update_game_of_life(int start, int end) {
		for (int i = start; i < end; i++) {
			game.simulateCell(i);
		}
	}

	void run() {
		
		auto wrapper = std::mem_fn(&application::update_game_of_life);

		std::thread thr1(wrapper(), 0, game.board.size() / 2);
		std::thread thr2(wrapper,game.board.size() / 2, game.board.size());
		thr1.join();
		thr2.join();
	}
};






int main() {
	application app;
	
	int a;
	int x = 0;
		while (x != 100) {
			app.game.printBoard();
			app.run();
			app.game.board = app.game.boardAfterSimulate;
			Sleep(100);
			//std::cout << "next" << std::endl;
			//std::cin >> a;
			system("CLS");
			x++;
		}
	
	return 0;
}
