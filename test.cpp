#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game_Process.h"

TEST(test_Game_of_Life, start)
{
	Life::Game Game(10, 10);
	Game.exec_command("start");
	ASSERT_EQ(0, 0);
}

TEST(test_Game_of_Life, save)
{
	Life::Game game(10, 10);
	game.exec_command("save save_test.txt");
	std::string s;
	bool flag = 1;
	std::ifstream fin;
	fin.open("save_test.txt");
	getline(fin, s);
	if (atoi(s.c_str()) != 10) { flag = 0; }
	getline(fin, s);
	if (atoi(s.c_str()) != 10) { flag = 0; }
	for (int i = 0; i < 10; i++) {
		getline(fin, s);
		for (int j = 0; j < 10; j++) {
			if (s[j] != '.') { flag = 0; }
		}
	}
	ASSERT_EQ(flag, TRUE);
	fin.close();
}

TEST(test_Game_of_Life, load)
{
	Life::Game game(10, 10);
	game.exec_command("load save_test.txt");
}

TEST(test_Game_of_Life, set)
{
	Life::Game game(10, 10);
	game.exec_command("set A1");
	game.exec_command("set H7");
	game.exec_command("set C9");
	game.exec_command("save save_test.txt");
	std::string s;
	int flag = 0;
	std::ifstream fin;
	fin.open("save_test.txt");
	getline(fin, s);
	getline(fin, s);
	for (int i = 0; i < 10; i++) {
		getline(fin, s);
		for (int j = 0; j < 10; j++) {
			if (s[j] == 'o' && i == 1 && j == 0) { flag++; }
			if (s[j] == 'o' && i == 7 && j == 7) { flag++; }
			if (s[j] == 'o' && i == 9 && j == 2) { flag++; }
		}
	}
	ASSERT_EQ(flag, 3);
	fin.close();

}

TEST(test_Game_of_Life, clear)
{
	Life::Game game(10, 10);
	game.exec_command("load save_test.txt");
	game.exec_command("clear A1");
	game.exec_command("clear H7");
	game.exec_command("clear C9");
	game.exec_command("save save_test.txt");
	std::string s;
	int flag = 0;
	std::ifstream fin;
	fin.open("save_test.txt");
	getline(fin, s);
	getline(fin, s);
	for (int i = 0; i < 10; i++) {
		getline(fin, s);
		for (int j = 0; j < 10; j++) {
			if (s[j] == '.' && i == 1 && j == 0) { flag++; }
			if (s[j] == '.' && i == 7 && j == 7) { flag++; }
			if (s[j] == '.' && i == 9 && j == 2) { flag++; }
		}
	}
	ASSERT_EQ(flag, 3);
	fin.close();
}

TEST(test_Game_of_Life, step)
{
	Life::Game game(10, 10);
	game.exec_command("set A0");
	game.exec_command("set A1");
	game.exec_command("set B0");
	game.exec_command("step");
	game.exec_command("save save_test.txt");
	std::string s;
	int flag = 0;
	std::ifstream fin;
	fin.open("save_test.txt");
	getline(fin, s);
	getline(fin, s);
	for (int i = 0; i < 10; i++) {
		getline(fin, s);
		for (int j = 0; j < 10; j++) {
			if (s[j] == 'o' && i == 0 && j == 0) { flag++; }
			else if (s[j] == 'o' && i == 0 && j == 1) { flag++; }
			else if (s[j] == 'o' && i == 1 && j == 0) { flag++; }
			else if (s[j] == 'o' && i == 1 && j == 1) { flag++; }
			else if (s[j] == 'o') { flag--; }
		}
	}
	ASSERT_EQ(flag, 4);
	fin.close();
}

/*TEST(test_Game_of_Life, step_N)
{
	Life::Game game(10, 10);
	game.exec_command("set A0");
	game.exec_command("set A1");
	game.exec_command("set A2");
	game.exec_command("step 1");
	game.exec_command("save save_test.txt");
	std::string s;
	int flag = 0;
	std::ifstream fin;
	fin.open("save_test.txt");
	getline(fin, s);
	getline(fin, s);
	for (int i = 0; i < 10; i++) {
		getline(fin, s);
		for (int j = 0; j < 10; j++) {
			if (s[j] == 'o' && i == 1 && j == 0) { flag++; }
			else if (s[j] == 'o' && i == 1 && j == 1) { flag++; }
			else if (s[j] == 'o' && i == 1 && j == 9) { flag++; }
			else if (s[j] == 'o') { flag--; }
		}
	}
	ASSERT_EQ(flag, 3);
	fin.close();
	flag = 0;
	game.exec_command("step 10");
	game.exec_command("save save_test.txt");
	fin.open("save_test.txt");
	getline(fin, s);
	getline(fin, s);
	for (int i = 0; i < 10; i++) {
		getline(fin, s);
		for (int j = 0; j < 10; j++) {
			if (s[j] == 'o' && i == 1 && j == 0) { flag++; }
			else if (s[j] == 'o' && i == 1 && j == 1) { flag++; }
			else if (s[j] == 'o' && i == 1 && j == 9) { flag++; }
			else if (s[j] == 'o') { flag--; }
		}
	}
	ASSERT_EQ(flag, 3);
	fin.close();
}
*/
TEST(test_Game_of_Life, reset)
{
	Life::Game game(10, 10);
	game.exec_command("set A0");
	game.exec_command("set A1");
	game.exec_command("set A2");
	game.exec_command("reset");
	game.exec_command("save save_test.txt");
	std::string s;
	int flag = 0;
	std::ifstream fin;
	fin.open("save_test.txt");
	getline(fin, s);
	getline(fin, s);
	for (int i = 0; i < 10; i++) {
		getline(fin, s);
		for (int j = 0; j < 10; j++) {
			if (s[j] == 'o') { flag++; }
		}
	}
	ASSERT_EQ(flag, 0);
	fin.close();
}

TEST(test_Game_of_Life, back)
{

}

TEST(test_Game_of_Life, random_set)
{
	Life::Game game(10, 10);
	game.exec_command("random_set 30");
	game.exec_command("save save_test.txt");
	std::string s;
	int flag = 0;
	std::ifstream fin;
	fin.open("save_test.txt");
	getline(fin, s);
	getline(fin, s);
	for (int i = 0; i < 10; i++) {
		getline(fin, s);
		for (int j = 0; j < 10; j++) {
			if (s[j] == 'o') { flag++; }
		}
	}
	ASSERT_EQ(flag, 30);
	fin.close();
}

/*TEST(test_Game_of_Life, auto_game)
{
	gol::Game game(10, 10);
	game.exec_command("set A0");
	game.exec_command("set A1");
	game.exec_command("set B0");
	game.exec_command("auto_game 10");
	ASSERT_EQ(0, 0);
}*/

/*TEST(test_Game_of_Life, help)
{
	gol::Game game(10, 10);
	game.exec_command("help");
	ASSERT_EQ(0, 0);
}*/