#include "My_exception.h"

namespace Life {

	my_exception::my_exception() : message("") {}

	my_exception::my_exception(const std::string &msg) : message(msg) {}

	void my_exception::get_message() {
		system("cls");
		printf("%s", message.c_str());
		printf("________________________\n\n");
		printf(" Input the next command: ");
	}

	my_constructor_error::my_constructor_error(const std::string class_name) {
		message = "\n Error: not enough memory or wrong arguments. " + get_info(class_name);
	}

	std::string my_constructor_error::get_info(const std::string class_name) {
		std::string res = "";
		if (class_name == "Game") {
			res = "Expected two positive integer numbers (less then 257): the length and the heigth of the game field. "
				"Recommended from 3 to 26, if more - you can see strange symbols in length indices\n\n";
		}
		return res;
	}

	my_command_error::my_command_error() {
		message = "\n Error: void command\n\n";
	}

	my_command_error::my_command_error(const std::string& command) : command(command) {
		message = "\n Error: the command '" + command + "' is unknown or incorrect. Print 'help' to see the list of"
			" allowed commands\n\n";
	}

	my_invalid_argument::my_invalid_argument(const std::string& com) {
		command = com;
		message = "\n Error in command '" + command + "' - invalid argument.\n " + get_info(command);
	}

	std::string my_invalid_argument::get_info(const std::string command) {
		std::string res = "";
		if (command == "step") {
			res = "Expected one positive integer number. For example: 'step 7'\n\n";
		}
		else if (command == "set") {
			res = "Expected one latin letter (which number <= length of the field) and one positive integer number ("
				"<= height of the field) without a space between. For example: set A3\n\n";
		}
		else if (command == "clear") {
			res = "Expected one latin letter (which number <= length of the field) and one positive integer number ("
				"<= height of the field) without a space between. For example: clear A3\n\n";
		}
		else if (command == "random_set") {
			res = "Expected one positive integer number (<= length * height). For example: 'random_set 50'\n\n";
		}
		else if (command == "save") {
			res = "Can not save file with this name\n\n";
		}
		else if (command == "load") {
			res = "Can not load file with this name\n\n";
		}
		else if (command == "start" || command == "back" || command == "reset") {
			res = "This command shouldn't have arguments\n\n";
		}
		return res;
	}

}