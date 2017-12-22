#include <iostream>
#include <cstdlib>
#include <string>

namespace Life {
	class my_exception {
	public:
		std::string message;
		my_exception();
		my_exception(const std::string& msg);
		void get_message();
	};

	class my_constructor_error : public my_exception {
	private:
		std::string get_info(const std::string class_name);
	public:
		my_constructor_error(const std::string class_name);
	};

	class my_command_error : public my_exception {
	public:
		std::string command;
		my_command_error();
		my_command_error(const std::string& command);
	};

	class my_invalid_argument : public my_command_error {
	private:
		std::string get_info(const std::string command);
	public:
		my_invalid_argument(const std::string& com);
	};
}