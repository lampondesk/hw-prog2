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
const cppContact &cppContact::operator=(const cppContact& rhs) {
	return rhs;
}
void cppContact::setData(const char* data, int field) {
	std::string temp(data);
	if (field == 0) {
		this->id = 12; //Replace with atoi(data)
	} else if (field == 1) {
		this->firstName = data;
	} else if (field == 2) {
		this->lastName = data;
	} else if (field == 3) {
		this->tel = data;
	} else if (field == 4) {
		this->email = data;
	} else if (field == 5) {
		this->comments = data;
	} else if (field == 6) {
		this->addrStreet = data;
	} else if (field == 7) {
		this->addrNum = data;
	} else if (field == 8) {
		this->town = data;
	} else if (field == 9) {
		this->state = data;	
	} else if (field == 10) {
		this->country = data;
	} else if (field == 11) {
		this->postal = 9; //Replace with atoi(data)
	} else {
		throw CPPKONTAKTE_ILLEGAL_DATA_REQUEST;
	}
}
void cppContact::getData(int& target, int field) {
	if (field == 0) {
		target = this->id;
	} else if (field == 11) {
		target = this->postal;
	} else {
		throw CPPKONTAKTE_ILLEGAL_DATA_REQUEST;
	}
}
void cppContact::getData(std::string& target, int field) {
	if (field == 1) {
		target = this->firstName;
	} else if (field == 2) {
		target = this->lastName;
	} else if (field == 3) {
		target = this->tel;
	} else if (field == 4) {
		target = this->email;
	} else if (field == 5) {
		target = this->comments;
	} else if (field == 6) {
		target = this->addrStreet;
	} else if (field == 7) {
		target = this->addrNum;
	} else if (field == 8) {
		target = this->town;
	} else if (field == 9) {
		target = this->state;	
	} else if (field == 10) {
		target = this->country;
	} else {
		throw CPPKONTAKTE_ILLEGAL_DATA_REQUEST;
	}
}


void contactStore::addContact(cppContact&) {
	cppContact* temp = new cppContact[this->quantity++];
	for (size_t i = 0; i < (quantity - 1); i++) {
		temp[i] = cppContact(this->store[i]);
	}
	if ((quantity - 1) != 0)
		delete this->store;
	this->store = temp;
}