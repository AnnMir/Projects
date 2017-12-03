#include "Game_Process.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	/*int width, height;
	std::cin >> width;
	std::cin >> height;
	struct point_world[width][height];
	initWorld(world);
	_getch();*/
	return 0;
}