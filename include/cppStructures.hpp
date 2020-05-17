#ifndef CSTRUCTURES_H
#define CSTRUCTURES_H

#include <iostream>
#include <cppStatus.hpp>

class cppContact {
    int				id;
    std::string		firstName;
    std::string		lastName;
    std::string		tel;
    std::string		email;
    std::string		comments;
    std::string		addrStreet;
    std::string		addrNum;
    std::string		town;
    std::string		state;
    std::string		country;
    int				postal;
	bool			stringMatch(std::string, std::string);
	bool			maskTest(const char*, const char*);

 public:
    /*cppContact(std::string stn = "", std::string lan = "", std::string tel = "", std::string em = "", std::string comm = "", std::string as = "", std::string an = "",
    std::string to = "", std::string sta = "", std::string co = "", int po = 0) : firstName(stn), lastName(lan), tel(tel), email(em), comments(comm), addrStreet(as),
    addrNum(an), town(to), state(sta), country(co), postal(po) { }*/
	cppContact() { }
	cppContact(const cppContact&);
    void setData(const char*, int);
	int getId() const						{ return id; }
	std::string getFirstName() const		{ return firstName; }
	std::string getLastName() const			{ return lastName; }
	std::string getTel() const				{ return tel; }
	std::string	getEmail() const			{ return email; }
	std::string getComments() const			{ return comments; }
	std::string getAddrStreet() const		{ return addrStreet; }
	std::string getAddrNum() const			{ return addrNum; }
	std::string getTown() const				{ return town; }
	std::string getState() const			{ return state; }
	std::string getCountry() const			{ return country; }
	int getPostal() const					{ return postal; }
    bool matchData(std::string, std::string);
	~cppContact() { }
};

class contactStore {
    cppContact*		store;
    size_t			quantity;

 public:
    contactStore() :quantity(0) { };
	cppContact& operator[](size_t);
	const cppContact& operator[](size_t) const;
	size_t getQuantity() { return quantity; }
    void addContact(cppContact&);
    void delContact(std::string);
	int getLastId() { return store[quantity - 1].getId(); }
	cppContact& getElementById(std::string);
    void search();
    ~contactStore() { if(quantity > 0) delete[] store; };
};

#endif
