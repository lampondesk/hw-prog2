#ifndef CSTRUCTURES_H
#define CSTRUCTURES_H

#include <iostream>
#include <cppStatus.hpp>

class cppContact {
    int            sqlId;
    std::string    firstName;
    std::string    lastName;
    std::string    tel;
    std::string    email;
    std::string    comments;
    std::string    addrStreet;
    std::string    addrNum;
    std::string    town;
    std::string    state;
    std::string    country;
    int            postal;

    int sApplyToStorage(int s) { return CPPKONTAKTE_STUB; }
    int cValidateData(int type) { return CPPKONTAKTE_STUB; }

 public:
    cppContact(std::string stn = "", std::string lan = "", std::string tel = "", std::string em = "", std::string comm = "", std::string as = "", std::string an = "",
    std::string to = "", std::string sta = "", std::string co = "", int po = 0) : firstName(stn), lastName(lan), tel(tel), email(em), comments(comm), addrStreet(as),
    addrNum(an), town(to), state(sta), country(co), postal(po) { }

    int setData(std::string stn, std::string l, std::string te, std::string em, std::string comm, std::string as, std::string an,
    std::string to, std::string sta, std::string co, int po) { return CPPKONTAKTE_STUB; }
    void displayData() { }
    bool matchData() { return CPPKONTAKTE_STUB; }
    char* prepareVCard() { return (char*)CPPKONTAKTE_STUB; }
    ~cppContact();
};

class contactStore {
    cppContact*		store;
    size_t			quantity;

 public:
    contactStore();
    int addContact();
    int delContact();
    int setContact();
    void displayAll();
    void search();
    int exportVCard();
    ~contactStore();
};

#endif
