#include "algorithms.h"

bool isLetter(char l) {
	return ('a' <= l && l <= 'z') || ('A' <= l && l <= 'Z');
}

bool valid_brackets(const std::string& str)
{
	int count = 0;
	for (char c : str)
	{
		if (c == '(')
			count++;
		else if (c == ')')
			count--;
		if (count < 0)
			return false;
	}
	return count == 0;
}

bool is_char_operation(char c, std::vector<std::string> valid_symbols) {
	return std::find(valid_symbols.begin(), valid_symbols.end(), std::string(1, c)) != valid_symbols.end();
}

bool ArithmeticExp::Check() {
	for (const char i : original_exp) {
		if (!(isLetter(i) || is_char_operation(i, valid_symbols))) {
			return false;
		}
	}
	if (!valid_brackets(original_exp))
		return false;
	if (original_exp == "")
		return false;
	return true;
}

void ArithmeticExp::Parse() {
	std::string name = "";
	for (char c : original_exp) {
		if (!is_char_operation(c, valid_symbols)) {
			name += c;
		}
		else {
			if (name != "") {
				lexemes.push_back(name);
			}
			name = "";
			lexemes.push_back(std::string(1, c));
		}
	}

	if (name != "") {
		lexemes.push_back(name);
	}
}

ArithmeticExp::ArithmeticExp(const std::string& exp) : original_exp(exp) {
	original_exp.erase(std::remove_if(original_exp.begin(), original_exp.end(), isspace), original_exp.end());

	priorities = {
		{"*", 3},
		{"/", 3},
		{"+", 2},
		{"-", 2},
	{"(", 1},
	};

	valid_symbols = {
		")",
	};
	for (std::pair<std::string, int> i : priorities) {
		valid_symbols.push_back(i.first);
	}

	bool check_status = Check();
	if (check_status) {
		ToPostfix();
	}
	else {
		throw std::exception("INVALID EXPRESSION");
	}
}

void ArithmeticExp::ToPostfix() {
	Parse();

	Stack<std::string> operations;
	Stack<std::string> operands;

	for (std::string elem : lexemes) {
		switch (elem[0]) {
		case '(':
			operations.Push(elem);
			break;
		case ')':
			while (operations.Top() != "(") {
				operands.Push(operations.Top());
				operations.Pop();
			}
			operations.Pop(); // deleting '('
			break;
		case '+': case '-': case '*': case '/':
			while (!operations.isEmpty()) {
				if (priorities[elem] <= priorities[operations.Top()]) {
					operands.Push(operations.Top());
					operations.Pop();
				}
				else {
					break;
				}
			}
			operations.Push(elem);
			break;
		default:
			operands.Push(elem);
			operands_values.insert({ elem, 0.0 });
		}
	}
	while (!operations.isEmpty()) {
		operands.Push(operations.Top());
		operations.Pop();
	}

	Stack<std::string> tmp(operands);
	while (!tmp.isEmpty()) {
		vector_postfix_exp.insert(vector_postfix_exp.begin(), tmp.Top());
		tmp.Pop();
	}

	while (!operands.isEmpty()) {
		string_postfix_exp = operands.Top() + " " + string_postfix_exp;
		operands.Pop();
	}
}

std::vector<std::string> ArithmeticExp::GetOperands() const {
	std::vector<std::string> op;
	for (const std::pair<std::string, double> elem : operands_values) {
		op.push_back(elem.first);
	}
	return op;
}

double ArithmeticExp::Calculate(const std::map<std::string, double>& values) {
	for (std::pair<std::string, double> val : values) {
		operands_values.at(val.first) = val.second;
	}

	Stack<double> st;
	double leftOp, rightOp;
	for (std::string lexem : vector_postfix_exp) {
		if (lexem == "+") {
			rightOp = st.Top();
			st.Pop();
			leftOp = st.Top();
			st.Pop();
			st.Push(leftOp + rightOp);
		}
		else if (lexem == "-") {
			rightOp = st.Top();
			st.Pop();
			leftOp = st.Top();
			st.Pop();
			st.Push(leftOp - rightOp);
		}
		else if (lexem == "*") {
			rightOp = st.Top();
			st.Pop();
			leftOp = st.Top();
			st.Pop();
			st.Push(leftOp * rightOp);
		}
		else if (lexem == "/") {
			rightOp = st.Top();
			st.Pop();
			leftOp = st.Top();
			st.Pop();
			if (rightOp == 0.0) {
				throw std::exception("ZERO_DIVISION");
			}
			st.Push(leftOp / rightOp);
		}
		else {
			st.Push(operands_values[lexem]);
		}
	}
	return st.Top();
}