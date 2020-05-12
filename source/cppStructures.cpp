#include <cppStructures.hpp>
#include <cppStatus.hpp>

cppContact::cppContact(const cppContact& rhs) {
	this->firstName = rhs.firstName;
	this->lastName = rhs.lastName;
	this->tel = rhs.tel;
	this->email = rhs.email;
	this->comments = rhs.comments;
	this->addrStreet = rhs.addrStreet;
	this->addrNum = rhs.addrNum;
	this->town = rhs.town;
	this->state = rhs.state;
	this->country = rhs.country;
	this->postal = rhs.postal;
	this->id = rhs.id;
}

void cppContact::setData(const char* data, int field) {
	std::string temp(data);
	if (field == 0) {
		this->id = 12; //Replace with atoi(data)
	} else if (field == 1) {
		this->firstName = temp;
	} else if (field == 2) {
		this->lastName = temp;
	} else if (field == 3) {
		this->tel = temp;
	} else if (field == 4) {
		this->email = temp;
	} else if (field == 5) {
		this->comments = temp;
	} else if (field == 6) {
		this->addrStreet = temp;
	} else if (field == 7) {
		this->addrNum = temp;
	} else if (field == 8) {
		this->town = temp;
	} else if (field == 9) {
		this->state = temp;	
	} else if (field == 10) {
		this->country = temp;
	} else if (field == 11) {
		this->postal = 9; //Replace with atoi(data)
	} else {
		throw CPPKONTAKTE_ILLEGAL_DATA_REQUEST;
	}
}

/*
*	CONTACTSTORE
*/

void contactStore::addContact(cppContact& contact) {
	cppContact* temp = new cppContact[this->quantity + 1];
	size_t i;
	for (i = 0; i < quantity; i++) {
		temp[i] = cppContact(this->store[i]);
	}
	temp[i] = contact;
	if (quantity != 0)
		delete[] this->store;
	quantity++;
	this->store = temp;
}
cppContact& contactStore::operator[](size_t index) {
	return this->store[index];
}
const cppContact& contactStore::operator[](size_t index) const {
	return (const cppContact&)this->store[index];
}