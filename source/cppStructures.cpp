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
		this->id = atoi(data);
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
		this->postal = atoi(data);
	} else {
		throw CPPKONTAKTE_ILLEGAL_DATA_REQUEST;
	}
}

bool cppContact::matchData(std::string field, std::string soughtData) {
	if (field == "id") {
		return (this->id == atoi(soughtData.c_str()));
	} else if (field == "firstname") {
		return maskTest(this->firstName.c_str(), soughtData.c_str());
	} else if (field == "lastname") {
		return maskTest(this->lastName.c_str(), soughtData.c_str());
	} else if (field == "phone") {
		return maskTest(this->tel.c_str(), soughtData.c_str());
	} else if (field == "email") {
		return maskTest(this->email.c_str(), soughtData.c_str());
	} else if (field == "comments") {
		return maskTest(this->comments.c_str(), soughtData.c_str());
	} else if (field == "street") {
		return maskTest(this->addrStreet.c_str(), soughtData.c_str());
	} else if (field == "number") {
		return maskTest(this->addrNum.c_str(), soughtData.c_str());
	} else if (field == "town") {
		return maskTest(this->town.c_str(), soughtData.c_str());
	} else if (field == "state") {
		return maskTest(this->state.c_str(), soughtData.c_str());
	} else if (field == "country") {
		return maskTest(this->country.c_str(), soughtData.c_str());
	} else if (field == "postal") {
		return (this->postal == atoi(soughtData.c_str()));
	} else {
		throw CPPKONTAKTE_ILLEGAL_DATA_REQUEST;
	}
}
/*	
*	Function cppContact::maskTest is based on 7zip's
*	EnhancedMaskTest function copyright 2020 Igor Pavlov.
*	Part of the 7zip source code (/CPP/Common/Wildcard.cpp)
*	Original software released under GNU LGPL. Please see
*	https://www.gnu.org/licenses/lgpl-3.0.html.
*	cppKontakte realeased under GPLv2.
*/
bool cppContact::maskTest(const char* mask, const char* name) {
	for (;;)
	{
		char m = *mask;
		char c = *name;
		if (m == 0)
			return (c == 0);
		if (m == '*')
		{
			if (cppContact::maskTest(mask + 1, name))
				return true;
			if (c == 0)
				return false;
		}
		else
		{
			if (m == '?')
			{
			if (c == 0)
				return false;
			}
			else if (m != c)
				return false;
			mask++;
		}
		name++;
	}
}

void contactStore::addContact(cppContact& contact) {
	try {
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
	} catch (std::bad_alloc) {
		throw CPPKONTAKTE_MEMORY_ALLOC_ERROR;
	}
}
void contactStore::delContact(std::string str) {
	int id = atoi(str.c_str());
	bool found = false;
	size_t index;
	for (size_t i = 0; i < this->quantity; i++) {
		if (this->store[i].getId() == id) {
			found = true;
			index = i;
		}
	}
	if (!found) {
		throw CPPKONTAKTE_ID_NOT_FOUND;
	}
	try {
		size_t j = 0;
		cppContact* temp = new cppContact[this->quantity - 1];
		for (size_t i = 0; i < quantity; i++) {
			if (i != index) {
				temp[j++] = this->store[i];
			}
		}
		delete[] this->store;
		this->store = temp;
		quantity--;
	} catch (std::bad_alloc) {
		throw CPPKONTAKTE_MEMORY_ALLOC_ERROR;
	}
}
cppContact& contactStore::operator[](size_t index) {
	if (index > (quantity - 1) || index < 0) {
		throw CPPKONTAKTE_ILLEGAL_DATA_REQUEST;
	}
	return this->store[index];
}
const cppContact& contactStore::operator[](size_t index) const {
	if (index > (quantity - 1) || index < 0) {
		throw CPPKONTAKTE_ILLEGAL_DATA_REQUEST;
	}
	return (const cppContact&)this->store[index];
}

cppContact& contactStore::getElementById(std::string str) {
	int soughtId = atoi(str.c_str());
	int foundIndex = 0;
	bool found = false;
	for (size_t i = 0; i < quantity; i++) {
		if (soughtId == this->store[i].getId()) {
			foundIndex = i;
			found = true;
			break;
		}
	}
	if (!found) {
		throw CPPKONTAKTE_ID_NOT_FOUND;
	}
	return this->store[foundIndex];
}
int contactStore::getLastId() {
	if (quantity > 0) {
		return store[quantity -1].getId();
	} else {
		return 0;
	}
}
cppContact* contactStore::search(std::string str, std::string pattern, size_t& resultno) {
	cppContact* matchingContacts = NULL;
	size_t mcSize = 0;
	cppContact* temp;
	for (size_t i = 0; i < this->quantity; i++) {
		if (store[i].matchData(str, pattern)) {
			try {
				temp = new cppContact[mcSize + 1];
				size_t j = 0;
				for (j = 0; j < mcSize; j++) {
					temp[j] = matchingContacts[j];
				}
				temp[j] = this->store[i];
				if (mcSize != 0)
					delete[] matchingContacts;
				mcSize++;
				matchingContacts = new cppContact[mcSize];
				for (j = 0; j < mcSize; j++) {
					matchingContacts[j] = temp[j];
				}
				delete[] temp;
			} catch (std::bad_alloc) {
				throw CPPKONTAKTE_MEMORY_ALLOC_ERROR;
			}
			
		}
	}
	resultno = mcSize;
	return matchingContacts;
}