#include "Game_Process.h"

namespace Life{

	void Game::start() {
		system("cls");
		printf("\n Current step: %d \n", steps);
		field.print_field();
		printf("________________________\n\n");
		printf(" Input the next command: ");
	};

	void Game::set(int i, int j) {
		field.create_cell(i, j);
		system("cls");
		printf("\n Current step: %d \n", steps);
		field.print_field();
		printf("________________________\n\n");
		printf(" Input the next command: ");
	};

	void Game::random_set(int amount) {
		if (amount > field.count_cells() || amount < 0) {
			printf("");
			return;
		}
		for (int i = 0; i < amount; i++) {
			field.random_creation();
		}
		system("cls");
		printf("\n Current step: %d \n", steps);
		field.print_field();
		printf("________________________\n\n");
		printf(" Input the next command: ");
	}

	void Game::clear(int i, int j) {
		field.delete_cell(i, j);
		system("cls");
		printf("\n Current step: %d \n", steps);
		field.print_field();
		printf("________________________\n\n");
		printf(" Input the next command: ");
	}

	void Game::back() {
		if (steps <= 0) {
			throw my_exception("Can't do step back");
		}
		field.step_back();
		steps--;
		system("cls");
		printf("\n Current step: %d \n", steps);
		field.print_field();
		printf("________________________\n\n");
		printf(" Input the next command: ");
	}

	void Game::step(int N) {
		std::string res;
		for (int i = 0; i < N; i++) {
			steps++;
			res = field.next();
			if (res != "") {
				break;
			}
		}
		if (res == "") {
			system("cls");
			printf("\n Current step: %d \n", steps);
			field.print_field();
			printf("________________________\n\n");
			printf(" Input the next command: ");
		}
		else {
			system("cls");
			printf("\n Game is ended on %d step: %s\n\n", steps, res.c_str());
			printf(" Load saving game or reset field \n\n");
			printf("________________________\n\n");
			printf(" Input the next command: ");
		}
	}

	void Game::reset() {
		field.delete_all_cells();
		steps = 0;
		system("cls");
		printf("\n Current step: %d \n", steps);
		field.print_field();
		printf("________________________\n\n");
		printf(" Input the next command: ");
	}

	void Game::save(std::string filename) {
		std::ofstream fout;
		fout.open(filename);
		if (!fout.is_open()) {
			throw my_invalid_argument("save");
		}
		field.load_to_file(&fout);
		fout.close();
		system("cls");
		printf("\n Game has been saving\n\n");
		printf("________________________\n\n");
		printf(" Input the next command: ");
	}

	void Game::load(std::string filename) {
		std::ifstream fin;
		fin.open(filename);
		if (!fin.is_open()) {
			throw my_invalid_argument("save");
		}
		field.get_from_file(&fin);
		fin.close();
		steps = 0;
		system("cls");
		printf("\n Current step: %d \n", steps);
		field.print_field();
		printf("________________________\n\n");
		printf(" Input the next command: ");
	}

	Game::Game(int width, int height) : field(Field(width, height)), steps(0) {
		system("cls");
		printf("Hello! It's 'The Game of Life'\n\n");
		printf("write 'start' to start \n\n");
		printf("________________________\n\n");
		printf(" Input the next command: ");
	}

	Game::~Game(){};

	void Game::exec_command(std::string command) {
		if (command.empty()) {
			throw my_command_error();
		}
		// Command parsing
		int error_flag = 0;
		std::string args[3];
		for (int i = 0; i < (int)command.size(); i++) {
			if (command[i] == ' ') {
				args[0] = command.substr(0, i);
				if (args[0] == "set" || args[0] == "clear") {
					args[1] = command[i + 1];
					args[2] = command.substr(i + 2, 100);
					if (args[1][0] < 65 || args[1][0] > 90) {
						error_flag = 1;
					}
					for (int i = 0; i < (int)args[2].size(); i++) {
						if (args[2][i] < 48 || args[2][i] > 57 || i > 1) {
							error_flag = 1;
							break;
						}
					}
				}
				else if (args[0] == "step" || args[0] == "random_set") {
					args[1] = command.substr(i + 1, 100);
					for (int i = 0; i < (int)args[1].size(); i++) {
						if (args[1][i] < 48 || args[1][i] > 57 || i > 9) {
							error_flag = 1;
							break;
						}
					}
				}
				else if (args[0] == "save" || args[0] == "load") {
					args[1] = command.substr(i + 1, 100);
				}
				else if (args[0] == "start" || args[0] == "back" || args[0] == "reset"){
					throw my_invalid_argument(args[0]);
				}
				break;
			}
		}
		if (error_flag == 1) {
			throw my_invalid_argument(args[0]);
		}
		// Command choosing
		/*if (command == "step") {
			step();
		}
		else*/ if (command == "start") {
			start();
		}
		else if (command == "back") {
			back();
		}
		else if (command == "reset") {
			reset();
		}
		else if (args[0] == "step") {
			step(atoi(args[1].c_str()));
		}
		else if (args[0] == "random_set") {
			random_set(atoi(args[1].c_str()));
		}
		else if (args[0] == "set") {
			set(args[1][0] - 65, atoi(args[2].c_str()));
		}
		else if (args[0] == "clear") {
			clear(args[1][0] - 65, atoi(args[2].c_str()));
		}
		else if (args[0] == "save") {
			save(args[1]);
		}
		else if (args[0] == "load") {
			load(args[1]);
		}
		else {
			throw my_command_error(command);
		}
	}

}