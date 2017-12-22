#include "Game_Process.h"

//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include <conio.h>

int main(int argc, char* argv[]){
	std::string str;
	Life::Game game(10, 10);
	while(1) {
	std::getline(std::cin, str);
	try { game.exec_command(str); } 
	catch (Life::my_constructor_error& ex) { ex.get_message();} 
	catch (Life::my_invalid_argument& ex) {ex.get_message();} 
	catch (Life::my_command_error& ex) {ex.get_message();} 
	catch (int){ std::cout << "It was a good game! Goodbye!" << std::endl; break; }
	catch (Life::my_exception& ex) {ex.get_message();}
	catch (...){ std::cout << "Something happened" << std::endl; }
	    }
	/*::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();*/
	_getch();
	return 0;
}