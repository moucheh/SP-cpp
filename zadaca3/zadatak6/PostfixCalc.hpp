#pragma once

#include "../zadatak1/DoubleLinkedList.hpp"
#include <iostream>
#include <sstream>
#include <string>

class PostfixCalc : public DoubleLinkedList<int> {
public:
	friend std::ostream& operator<<(std::ostream&, const PostfixCalc&);

	PostfixCalc(std::string&& input);
private:
	char op;
};