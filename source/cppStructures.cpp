#include <cppStructures.hpp>

void contactStore::addContact(cppContact&) {
	cppContact* temp = new cppContact[this->quantity++];
	for (size_t i = 0; i < quantity; i++) {
		temp[i] = this->store[i];
	}
	delete[] this->store;
	this->store = temp;
}