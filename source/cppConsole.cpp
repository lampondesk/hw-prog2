#include <iostream>
#include <cppConsole.hpp>
#include <cppStructures.hpp>

void TerminalHandler::getCommand() {
	if (!std::cin.eof()) {
		std::cout << "cppKontakte> " << std::flush;
		std::getline(std::cin, prompt);
	} else {
		prompt = "-exit";
	}
}

bool TerminalHandler::validatePhone(const char* str) {
	char c = str[0];
	int i = 0;
	while (c != '\0') {
		c = str[i];
		if (c != '*' && c != '#' && c != '+' && !isdigit(c) && c != '\0')
			return false;
		i++;
	}
	return true;
}

bool TerminalHandler::validateEmail(const char* str) {
	char c = str[0];
	int i = 0;
	bool hasDot = false;
	bool hasAt = false;
	while (c != '\0') {
		c = str[i];
		if (c == '@' && !hasDot)
			hasAt = true;
		else if (c == '@' && hasDot)
			return true;
		else if (c == '.' && !hasAt)
			hasDot = true;
		else if (c == '.' && hasAt)
			return true;
		i++;
	}
	return false;
}
bool TerminalHandler::validatePostal(const char* str) {
	char c = str[0];
	int i = 0;
	while (c != '\0') {
		c = str[i];
		if (!isdigit(c) && c != '\0')
			return false;
		i++;
	}
	return true;
}

std::string* TerminalHandler::askData(contactStore& cs) {
	std::string* tempsa = new std::string[11];
	bool isvalid = true;
	bool isfilled = true;
	std::cout << "Please insert following data:" << std::endl;
	std::cout << "Fields marked with * are required fields." << std::endl;
	do {
		isfilled = true;
		std::cout << "(*) First name: ";
		std::getline(std::cin, tempsa[0]);
		if (tempsa[0] == "") {
			std::cout << "First name is a required field. Please do not leave it empty.";
			isfilled = false;
		}
	} while (!isfilled);
	do {
		isfilled = true;
		std::cout << "(*) Last name: ";
		std::getline(std::cin, tempsa[1]);
		if (tempsa[1] == "") {
			std::cout << "Last name is a required field. Please do not leave it empty.";
			isfilled = false;
		}
	} while (!isfilled);
	std::cout << "Phone number: ";
	std::getline(std::cin, tempsa[2]);
	do {
		isvalid = validatePhone(tempsa[2].c_str());
		if (!isvalid) {
			std::cout << "The phone number you just entered has an invalid format." << std::endl;
			std::cout << "Please make sure it only contains numbers, and the characters '*' and '#'." << std::endl;
			std::cout << "Phone number: ";
			std::getline(std::cin, tempsa[2]);
		}
	} while(!isvalid);
	std::cout << "E-mail: ";
	std::getline(std::cin, tempsa[3]);
	do {
		isvalid = validateEmail(tempsa[3].c_str());
		if (!isvalid) {
			std::cout << "The e-mail address you just entered has an invalid format." << std::endl;
			std::cout << "Please make sure it contains at least one instance of the following characters: '@'." << std::endl;
			std::cout << "E-mail: ";
			std::getline(std::cin, tempsa[3]);
		}
	} while(!isvalid);
	std::cout << "Comments: ";
	std::getline(std::cin, tempsa[4]);
	std::cout << "Street: ";
	std::getline(std::cin, tempsa[5]);
	std::cout << "Number: ";
	std::getline(std::cin, tempsa[6]);
	std::cout << "Town: ";
	std::getline(std::cin, tempsa[7]);
	std::cout << "State: ";
	std::getline(std::cin, tempsa[8]);
	std::cout << "Country: ";
	std::getline(std::cin, tempsa[9]);
	std::cout << "Postal code: ";
	std::getline(std::cin, tempsa[10]);
	do {
		isvalid = validatePostal(tempsa[10].c_str());
		if (!isvalid) {
			std::cout << "The postal code you just entered has an invalid format." << std::endl;
			std::cout << "Please make sure it contains numbers only." << std::endl;
			isvalid = false;
			std::cout << "Postal code: ";
			std::getline(std::cin, tempsa[10]);
		}
	} while(!isvalid);
	return tempsa;
}

void TerminalHandler::display(cppContact& contact) {
	std::cout << contact.getId() << " " << contact.getFirstName() << " " << contact.getLastName() << " " << contact.getTel()
	<< " " << contact.getEmail() << " " << contact.getComments() << " " << contact.getAddrStreet() << " " << contact.getAddrNum()
	<< " " << contact.getTown() << " " << contact.getState() << " " << contact.getCountry() << " " << contact.getPostal() << std::endl;
}

void TerminalHandler::consoleAdd(contactStore& cs) {
	std::string* data = askData(cs);
	cppContact temp;
	temp.setData(std::to_string(cs.getLastId()+1).c_str(), 0);
	for (size_t i = 0; i < 11; i++) {
		temp.setData(data[i].c_str(), i + 1);
	}
	delete[] data;
	try {
		cs.addContact(temp);
	} catch (int) {
		std::cout << "Memory error. This means that either there is a bug\nin the software, or you are out of memory." << std::endl;
	}
}

void TerminalHandler::consoleEdit(contactStore& cs) {
	std::string* data;
	std::string id;
	bool isfilled = true;
	std::cout << "Please select the ID of the person you want to edit:" << std::endl;
	do {
		isfilled = true;
		std::cout << "(*) ID ";
		std::getline(std::cin, id);
		if (id == "") {
			std::cout << "ID is a required field. Please do not leave it empty.";
			isfilled = false;
		}
	} while (!isfilled);
	try {
		cppContact& actualContact = cs.getElementById(id);
		data = askData(cs);
		for (size_t i = 0; i < 11; i++) {
			actualContact.setData(data[i].c_str(), i + 1);
		}
		delete[] data;
	} catch (int e) {
		if (e == CPPKONTAKTE_ID_NOT_FOUND) {
			std::cout << "A contact with the given ID cannot be found." << std::endl;
		}
	}
}

void TerminalHandler::consoleDelete(contactStore& cs) {
	std::string id;
	bool isfilled = true;
	std::cout << "Please select the ID of the person you want to delete:" << std::endl;
	do {
		isfilled = true;
		std::cout << "(*) ID ";
		std::getline(std::cin, id);
		if (id == "") {
			std::cout << "ID is a required field. Please do not leave it empty.";
			isfilled = false;
		}
	} while (!isfilled);
	try {
		cs.delContact(id);
	} catch (int e) {
		if (e == CPPKONTAKTE_ID_NOT_FOUND) {
			std::cout << "A person with the given ID cannot be found." << std::endl;
		} else if (e == CPPKONTAKTE_MEMORY_ALLOC_ERROR) {
			std::cout << "Memory error. This means that either there is a bug\nin the software, or you are out of memory." << std::endl;
		}
	}
}

void TerminalHandler::consoleSearch(contactStore& cs) {
	std::string field;
	std::string pattern;
	size_t resultno = 0;
	std::cout << "First, enter the data field you want to search in." << std::endl;
	std::cout << "[id|firstname|lastname|phone|email|comments|number|street|town|state|country|postal]" << std::endl;
	std::cout << "Then, enter the search pattern you want to use." << std::endl;
	bool isfilled;
	do {
		isfilled = true;
		std::cout << "Field: ";
		std::getline(std::cin, field);
		if (field == "") {
			std::cout << "You have to enter the data field you want to search in." << std::endl;
			isfilled = false;
		}
	} while (!isfilled);
	do {
		isfilled = true;
		std::cout << "Pattern: ";
		std::getline(std::cin, pattern);
		if (field == "") {
			std::cout << "You have to enter a search pattern." << std::endl;
			isfilled = false;
		}
	} while (!isfilled);
	try {
		cppContact* foundContacts = cs.search(field, pattern, resultno);
		if (resultno == 0) {
			std::cout << "Nothing found." << std::endl;
		} else {
			for (size_t i = 0; i < resultno; i++) {
				display(foundContacts[i]);
			}
		}
		delete[] foundContacts;
	} catch (int e) {
		if (e == CPPKONTAKTE_ILLEGAL_DATA_REQUEST) {
			std::cout << "You have selected a data field that does not exist." << std::endl;
		} else if (e == CPPKONTAKTE_MEMORY_ALLOC_ERROR) {
			std::cout << "Memory error. This means that either there is a bug\nin the software, or you are out of memory." << std::endl;
		}
	}
}

void TerminalHandler::displayAll(contactStore& cs) {
	for (size_t i = 0; i < cs.getQuantity(); i++) {
		display(cs[i]);
	}
}