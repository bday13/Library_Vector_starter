#include "../includes_usr/fileIO.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename) {

	ifstream file(filename);

	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	std::string str;
	&books.clear();

	while (std::getLine(file, str)) {

		stringstream ss(str);
		book bk;
		std::string id, title, author, state, patronid;

		std::getLine(ss, id, ',');
		std::getLine(ss, title, ',');
		std::getLine(ss, author, ',');
		std::getLine(ss, state, ',');
		std::getLine(ss, patronid, ',');

		bk.book_id = std::(id, nullptr, 10);
		bk.title = title;
		bk.author = author;
		bk.state = static_cast<book_checkout_state>(std::stoi(state, nullptr, 10));
		bk.loaned_to_patron_id = std::stoi(patronid, nullptr, 10);

		&books.push_back(bk);
	}

	file.close();

	if (&books.size() < 1) {
		return NO_BOOKS_IN_LIBRARY;
	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename) {

	if (&books.size() == 0) {
		return NO_BOOKS_IN_LIBRARY;
	}

	ofstream file(filename);

	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	} else {
		string str;

		for (int i = 0; i < &books.size(); i++) {
			str = to_string(&books[i].book_id) + "," + &books[i].title + "," + &books[i].author + "," + to_string(&books[i].state) + "," + to_string(&books[i].loaned_to_patron_id);
			file<<str<<std::endl;
		}
	}

	file.close();
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename) {

	ifstream file(filename);

	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	&patrons.clear();

	while (std::getline(file, line)) {

		stringstream str(line);
		patron p;
		string id, name, &books;

		std::getline(str, id, ',');
		std::getline(str, name, ',');
		std::getline(str, &books, ',');

		p.patron_id = std::stoi(id, nullptr, 10);
		p.name = name;
		p.number_books_checked_out = std::stoi(&books, nullptr, 10);

		&patrons.push_back(p);
	}

	if (&patrons.size() < 1) {
		return NO_PATRONS_IN_LIBRARY;
	}
	file.close();

	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename) {

	if(&patrons.size() == 0) {
		return NO_PATRONS_IN_LIBRARY;
	}

	ofstream file(filename);

	if(!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	for(int i = 0; i < &patrons.size(); i++) {
		patron p = &patrons[i];

		file << std::to_string(p.patron_id) << "," << p.name << "," << p.number_books_checked_out << endl;
	}

	file.close();
	return SUCCESS;
}
