/*
This code provides a simulation of a book database system. 
Databases can be saved in a file and loaded from a file as well.
In addition to this, all major functions that are applicable to a database are also 
implemented in this programme.
*/
#include <iostream>
#include <iomanip> //for setw
#include <fstream> //file
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;


void inputCheck(int &flag)	//function to stop program from running into infinite loop if char input is given instead of int 
{
	int count = 0;
	while(!(cin>>flag) && count<1)		//essentially means while the inputted datatype is not int, keep going
	{
		cout << "\nIncorrect input. Please try again.\n";
		cin.clear();		//clears error flag to allow other operations to work corectly
		cin.ignore('\n');		//ignores any input in buffer
		count++;
	}
}

bool isSubstr(string s1, string s2, const int& start)	//using this function to allow users to search for a record using partial author or title name
{
	if(s1.length() - start <s2.length())
		return false;
	else
	{
		string temp = s1.substr(start, s2.length());
		if(s2 == temp)
			return true;
		else
			return isSubstr(s1, s2, start+1);
	}
}

void standardize(string& s) //function to convert all string to lowercase for easy comparison 
{
	for(int i = 0; i<s.size(); i++)
	{
		if(s[i]>=65 && s[i]<=90)
			s[i] += 32;
	}
}

//book represented as a class

class Book
{
private:
	string title;
	string author;
	int dateOfPublication;
	string bookType;
	int numberOfPages;
	int ID;
	static int count;

public:
	Book();
	Book(string& title, string& author, const int& dop, const int& type, const int& num);
	Book(const Book &b);

	//setters
	void setTitle(const string& t);
	void setAuthor(const string& a);
	void setDateOfPublication(const int& dop);
	void setBookType(const int& type);
	void setBookType(const string& type);
	void setNumberOfPages(const int& num);
	
	//getters
	string getTitle() const;
	string getAuthor()const;
	int getDateOfPublication()const;
	string getBookType()const;
	int getNumberOfPages()const;
	int getID() const;

	//operators
	Book& operator=(const Book &b);

	//friend functions
	friend istream& operator>>(istream&in, Book &b);
	friend ostream& operator<<(ostream&out, const Book &b);
};

int Book::count = 0;

Book::Book()
{
	title = "";
	author = "";
	dateOfPublication = 0;
	bookType = "";
	numberOfPages = 0;
	count++;
	ID = 100 + count;
}

Book::Book(string& title, string& author, const int& dop, const int& type, const int& num)
{
	standardize(title);
	standardize(author);
	setTitle(title);
	setAuthor(author);
	setDateOfPublication(dop);
	setBookType(type);
	setNumberOfPages(num);
	count++;
	ID = 100 + count;
}

Book::Book(const Book &b)
{
	setTitle(b.getTitle());
	setAuthor(b.getAuthor());
	setDateOfPublication(b.getDateOfPublication());
	setBookType(b.getBookType());
	setNumberOfPages(b.getNumberOfPages());
	ID = b.getID();
}

void Book::setTitle(const string& t)
{
	title = t;
}
	
void Book::setAuthor(const string& a)
{
	author = a;
}
	
void Book::setDateOfPublication(const int& dop)
{
	dateOfPublication = dop;
}
	
void Book::setBookType(const int& type)
{
	switch(type)
	{
	case 1: bookType = "hard_cover";
			break;
			
	case 2: bookType = "soft_cover";
			break;

	case 3: bookType = "digital";
			break;
	}
}

void Book::setBookType(const string& type)
{
	bookType = type;
}
	
void Book::setNumberOfPages(const int& num)
{
	numberOfPages = num;
}

string Book::getTitle() const
{
	return title;
}
	
string Book::getAuthor()const
{
	return author;
}
	
int Book::getDateOfPublication()const
{
	return dateOfPublication;
}

string Book::getBookType()const
{
	return bookType;
}
	
int Book::getNumberOfPages()const
{
	return numberOfPages;
}

int Book::getID()const
{
	return ID;
}

Book& Book::operator=(const Book &b)
{
	if(this == &b)
		return *this;
	this->setTitle(b.getTitle());
	this->setAuthor(b.getAuthor());
	this->setDateOfPublication(b.getDateOfPublication());
	this->setBookType(b.getBookType());
	this->setNumberOfPages(b.getNumberOfPages());
	this->ID = b.getID();
	return *this;
}

istream& operator>>(istream&in, Book &b)
{
	string s_temp;
	int i_temp;
	
	cout<<"\nEnter Book Details: \n\t Instead of spaces, please use underscores (_): \n\nTitle:  ";
	in>>s_temp;
	standardize(s_temp);
	b.setTitle(s_temp);
	
	cout<<"\nAuthor's Name:  ";
	in>>s_temp;
	standardize(s_temp);
	b.setAuthor(s_temp);

	cin.clear();
	cin.ignore();

	cout<<"\nDate Of Publication: ";
	inputCheck(i_temp);
	if(i_temp<0)
	{
		cin.clear();
		cin.ignore(256, '\n');
		inputCheck(i_temp);
	}
	b.setDateOfPublication(i_temp);
	
	cout<<"\nBook Type: \n\t1.Hard Cover \n\t2.Soft Cover \n\t3.Digital \nEnter corresponding number: ";
	inputCheck(i_temp);
	if(i_temp<0 || i_temp>3)
	{
		cin.clear();
		cin.ignore(256, '\n');
		inputCheck(i_temp);
	}
	b.setBookType(i_temp);
	
	cout<<"\nNumber of pages: ";
	inputCheck(i_temp);
	if(i_temp<0)
	{
		cin.clear();
		cin.ignore(256, '\n');
		inputCheck(i_temp);
	}
	b.setNumberOfPages(i_temp);
	return in;
}

ostream& operator<<(ostream& out, const Book &b) 
{
	out<<"\nBook Details: ";
	out<<"\n\nID: "<<setw(15)<<" "<<b.getID();
	out<<"\nTitle: "<<setw(12)<<" "<<b.getTitle();
	out<<"\nAuthor: "<<setw(11)<<" "<<b.getAuthor();
	out<<"\nPublication Date:  "<<b.getDateOfPublication();
	out<<"\nType: "<<setw(13)<<" "<<b.getBookType();
	out<<"\nNumber Of Pages: "<<setw(2)<<" "<<b.getNumberOfPages()<<endl;
	return out;
}

// following boolean comparison functions are used in sort algorithm to sort the vector by a specific attribute 

bool compareTitle(Book b1, Book b2)
{
	return (b1.getTitle() <b2.getTitle());
}

bool compareAuthor(Book b1, Book b2)
{
	return (b1.getAuthor() < b2.getAuthor());
}

bool compareDOP(Book b1, Book b2)
{
	return (b1.getDateOfPublication() < b2.getDateOfPublication());
}

bool compareType(Book b1, Book b2)
{
	return (b1.getBookType() < b2.getBookType());
}

bool compareNOP(Book b1, Book b2)
{
	return (b1.getNumberOfPages() < b2.getNumberOfPages());
}

void sort(vector <Book> &b)		//to display sort menu and sort accordingly
{
	char ch = 'y';
	do
	{
		system("cls");
		int choice;
		cout<<"\nYou can sort by following attributes in ascending order: \n\t1.Title \n\t2.Author \n\t3.Date Of Publication";
		cout<<"\n\t4.Book Type \n\t5.Number of Pages \nEnter choice: ";
		inputCheck(choice);
		if(choice<1 || choice>5)
		{
			cin.clear();
			cin.ignore(256, '\n');
			inputCheck(choice);
		}
		switch(choice)
		{
			case 1: sort(b.begin(), b.end(), compareTitle);
					break;

			case 2: sort(b.begin(), b.end(), compareAuthor);
					break;

			case 3: sort(b.begin(), b.end(), compareDOP);
					break;

			case 4: sort(b.begin(), b.end(), compareType);
					break;

			case 5: sort(b.begin(), b.end(), compareNOP);
					break;
		}
		int size = b.size();
		for(int i = 0; i <size ; i++)
		{
			cout<<b[i];
		}

		cout<<"\n\nDo you want to sort by another attribute? (Press y for yes, any other character for no): ";
		cin>>ch;
	}while(ch == 'y' || ch  == 'Y');
	system("cls");
}

//dataBase represented as a class

class Database
{
private:
	vector <Book> book;
	
public:

	void create(const Book &b);	//create a new entry
	void display() const;		//display the entire database
	int getSize() const;

	void searchTitle();			//search by title
	void searchAuthor();		//search by author
	void searchDOP();			//search by date of publication
	void searchType();			//search by book type
	void searchNumOfPages();	//search by number of pages
	int searchID();				//search by ID
	
	void compoundSearch(vector<int> &result);
	void and(vector<int> &result, vector<int> &new_result);
	void or(vector<int> &result, vector<int> &new_result);
	void not(vector<int> &result, vector<int> &new_result);
	void range(vector<int> &result, vector<int> &new_result);
	
	void update(const int& index);		//modify entries 
	void remove(const int&index);		//delete an entry
	void append();						//appends data from a file to dataBase
	void save();						//saves data from dataBase to file
	void clean();						//clears the data from dataBase
	bool empty() const;					//checks if database is empty

	Book& operator[] (int &index); 

}dataBase;		//one global database object we will be working with

int dbm = 0;		//keeping a count of how many databases we go through in one programme run

void Database::create(const Book &b)
{
	book.push_back(b);
}

void Database::display() const
{
	vector<Book>::const_iterator it;
	for(it = book.begin(); it< book.end(); it++)
		cout << *it <<endl;
}		

int Database::getSize() const
{
	return book.size();
}

void Database::update(const int& index) 
{
	char ch = 'y';
	do
	{
		int choice, i_value;
		string value;
		cout<<"\nSelect the attribute you want to modify \n\t1.Title \n\t2.Author \n\t3.Date Of Publication \n\t4.Book Type \n\t5.Number Of Pages \nEnter choice: ";
		inputCheck(choice);
		if(choice<1 || choice>5)
		{
			cin.clear();
			cin.ignore(256, '\n');
			inputCheck(choice);
		}
		switch(choice)
		{
			case 1: cout<<"\nEnter new Title : \n\t Instead of spaces, please use underscores (_):";
					cin>>value;
					standardize(value);
					book[index].setTitle(value);
					cout<<book[index]<<endl;
					break;
	
			case 2: cout<<"\nEnter new Author : \n\t Instead of spaces, please use underscores (_):";
					cin>>value;
					standardize(value);
					book[index].setAuthor(value);
					cout<<book[index]<<endl;
					break;

			case 3: cout<<"\nEnter new Date Of Publication : ";
					inputCheck(i_value);
					if(i_value<0)
					{
						cin.clear();
						cin.ignore(256, '\n');
						inputCheck(i_value);
					}
					book[index].setDateOfPublication(i_value);
					cout<<book[index]<<endl;
					break;

			case 4: cout<<"\nEnter new Type : ";
					cout<<"Book Type: \n\t1.Hard Cover \n\t2.Soft Cover \n\t3.Digital \nEnter corresponding number: ";
					inputCheck(i_value);
					if(i_value<1 || i_value>3)
					{
						cin.clear();
						cin.ignore(256, '\n');
						inputCheck(i_value);
					}
					book[index].setBookType(i_value);
					cout<<book[index]<<endl;
					break;

			case 5: cout<<"\nEnter new Number Of Pages : ";
					inputCheck(i_value);
					if(i_value<0)
					{
						cin.clear();
						cin.ignore(256, '\n');
						inputCheck(i_value);
					}
					book[index].setNumberOfPages(i_value);
					cout<<book[index]<<endl;
					break;
		}

		cout<<"\n\nDo you want to perform modification for THE SAME entry? (Press y for yes, any other character for no): ";
		cin>>ch;
		system("cls");

	}while(ch == 'y' || ch  == 'Y');
	system("cls");
}

void Database::remove(const int&index)
{
	vector<Book> temp;
	int i, j;
	for(i = 0, j = 0; i<book.size(); i++)
	{
		if(i == index)
			continue;
		else
		{
			temp.push_back(book[i]);
			j++;
		}
	}

	clean();
	for(i = 0; i<temp.size(); i++)
		book.push_back(temp[i]);
	
	cout<<"\nNEW DATABASE: "<<endl;
	display();
}

void Database::append()
{
	string file;
	cout<<"\nEnter file name with extension: ";
	file = "Database.txt";
	ifstream fin(file);
	while(fin.fail())
	{
		cout<<"\nEnter valid file name/path: ";
		cin>>file;
		fin.open(file);
	}
	while(!fin.eof())
	{
		Book temp;
		int i_temp;
		string s_temp;
		fin>>i_temp;	//this is the old Book ID of the entry and hence will be discarded
		fin>>s_temp;
		temp.setTitle(s_temp);
		fin>>s_temp;
		temp.setAuthor(s_temp);
		fin>>i_temp;
		temp.setDateOfPublication(i_temp);
		fin>>s_temp;
		temp.setBookType(s_temp);
		fin>>i_temp;
		temp.setNumberOfPages(i_temp);
		create(temp);
	}
	fin.close();
	cout<<"\nNew Database: "<<endl;
	display();
}

void Database::save()
{
	ofstream fout("MyDatabase.txt", ios::app);
	
	if(dbm == 1)
		fout<<"DATABASE "<<dbm<<endl;
	else
		fout<<"\n\n\nDATABASE "<<dbm<<endl;
	int i;
	for(i = 0; i<book.size(); i++)
	{
		fout<<endl<<book[i].getID()<<"   "<<left<<setw(50)<<setfill(' ')<<book[i].getTitle()<<left<<setw(30)<<setfill(' ')<<book[i].getAuthor()
			<<left<<setw(10)<<setfill(' ')<<book[i].getDateOfPublication()<<left<<setw(10)<<setfill(' ')<<book[i].getBookType()<<"\t"<<book[i].getNumberOfPages();
	}
	fout.close();
}

void Database::clean()
{
	book.clear();
}

bool Database::empty() const
{
	if(book.empty())
		return true;
	else
		return false;
}

Book& Database::operator[] (int &index)
{
	return book[index];
}

//for searching, possible results are pushed back into a temp vector and then users are given a choice to sort the results or not

void Database::searchTitle()
{
	system("cls");
	char ch;
	string stemp, btemp;
	cout<<"\nEnter title (or part of title) to search for: \n\t Instead of spaces, please use underscores (_): ";
	cin>>stemp;
	standardize(stemp);
	vector<Book> temp;
	for(int i = 0; i < book.size(); i++)
	{
		btemp = book[i].getTitle();
		if(isSubstr(btemp, stemp, 0))
			temp.push_back(book[i]);
	}

	cout<<"\nWould you like to see results sorted by a parameter? (press y for yes, any other character for no): ";
	cin>>ch;
	if(ch == 'y' || ch == 'Y')
		sort(temp);
	else
	{
		for(int i = 0; i < temp.size(); i++)
			cout<<temp[i];
	}
}

void Database::searchAuthor()
{
	system("cls");
	char ch;
	string stemp, btemp;
	cout<<"\nEnter author (or part of author) to search for: \n\t Instead of spaces, please use underscores (_):";
	cin>>stemp;
	standardize(stemp);
	vector<Book> temp;
	for(int i = 0; i<book.size(); i++)
	{
		btemp = book[i].getAuthor();
		if(isSubstr(btemp, stemp, 0))
			temp.push_back(book[i]);
	}

	cout<<"\nWould you like to see results sorted by a parameter? (press y for yes, any other character for no): ";
	cin>>ch;
	if(ch == 'y' || ch == 'Y')
		sort(temp);
	else
	{
		for(int i = 0; i < temp.size(); i++)
			cout<<temp[i];
	}

}

void Database::searchDOP() 
{
	system("cls");
	char ch;
	int itemp;
	cout<<"\nEnter date of publication to search for: ";
	inputCheck(itemp);
	if(itemp<0)
	{
		cin.clear();
		cin.ignore(256, '\n');
		inputCheck(itemp);
	}
	vector<Book> temp;
	int size = book.size();

	for(int i = 0; i < size; i++)
	{
		if(book[i].getDateOfPublication() == itemp)
			temp.push_back(book[i]);
	}

	cout<<"\nWould you like to see results sorted by a parameter? (press y for yes, any other character for no): ";
	cin>>ch;
	if(ch == 'y' || ch == 'Y')
		sort(temp);
	else
	{
		for(int i = 0; i < temp.size(); i++)
			cout<<temp[i];
	}
}

void Database::searchType() 
{
	system("cls");
	char ch;
	int choice;
	string stemp;
	cout<<"\nBook Types: \n\t1.Hard Cover \n\t2.Soft Cover \n\t3.Digital \nEnter book type to search for: ";
	inputCheck(choice);
	if(choice<1 || choice>3)
	{
		cin.clear();
		cin.ignore(256, '\n');
		inputCheck(choice);
	}
	switch(choice)
	{
		case 1: stemp = "hard_cover";
				break;
		case 2: stemp = "soft_cover";
				break;
		case 3: stemp = "digital";
				break;
	}
	vector<Book> temp;
	int size = book.size();
	for(int i = 0; i < size; i++)
	{
		if(book[i].getBookType() == stemp)
			temp.push_back(book[i]);
	}

	cout<<"\nWould you like to see results sorted by a parameter? (press y for yes, any other character for no): ";
	cin>>ch;
	if(ch == 'y' || ch == 'Y')
		sort(temp);
	else
	{
		for(int i = 0; i < temp.size(); i++)
			cout<<temp[i];
	}
}

void Database::searchNumOfPages() 
{
	system("cls");
	char ch;
	int itemp;
	cout<<"\nEnter number of pages to search for: ";
	inputCheck(itemp);
	if(itemp<0)
	{
		cin.clear();
		cin.ignore(256, '\n');
		inputCheck(itemp);
	}
	vector<Book> temp;
	for(int i = 0; i < book.size(); i++)
	{
		if(book[i].getNumberOfPages() == itemp)
			temp.push_back(book[i]);
	}

	cout<<"\nWould you like to see results sorted by a parameter? (press y for yes, any other character for no): ";
	cin>>ch;
	if(ch == 'y' || ch == 'Y')
		sort(temp);
	else
	{
		for(int i = 0; i < temp.size(); i++)
			cout<<temp[i];
	}
}

int Database::searchID()
{
	system("cls");
	int itemp, i;
	cout<<"\nEnter Book ID: ";
	inputCheck(itemp);
	if(itemp<0)
	{
		cin.clear();
		cin.ignore(256, '\n');
		inputCheck(itemp);
	}
	Book temp;

	for(i = 0; i < book.size(); i++)
	{
		if(book[i].getID() == itemp)
		{
			temp = book[i];
			break;
		}
	}

	if(i == book.size())
	{
		cout<<"\nRecord Not Found. "<<endl;
		return -1;
	}
	cout<<"\nBook record with ID "<<itemp<<" :"<<temp<<endl;
	return i;
}

bool Title_or_Author()
{
	int temp;
	cout<<"\nDo you want to search with: \n\t1. Title \n\t2. Author \nEnter Option: ";
	inputCheck(temp);
	if(temp<1 || temp>2)
	{
		cin.clear();
		cin.ignore(256, '\n');
		inputCheck(temp);
	}
	switch(temp)	
	{
		case 1:	return 1;
		case 2: return 0;
	}
	return 0;
}

bool year_or_pages() 
{
	int temp;
	cout<<"\nDo you want to search with: \n\t1. Year \n\t2. Pages  \nEnter Option: ";
	inputCheck(temp);
	if(temp<1 || temp>2)
	{
		cin.clear();
		cin.ignore(256, '\n');
		inputCheck(temp);
	}
	switch(temp)	
	{
		case 1: return 1;
		case 2: return 0;
	}
	return 0;
}

void Database::and(vector<int> &result, vector<int> &new_result)
{
	string str1, str2;
	cout<<"\nInstead of spaces enter underscores (_)";
	cout<<"\n\tEnter title or part of title: ";
	cin>>str1;
	standardize(str1);
	cout<<"\n\tEnter author or part of author: ";
	cin>>str2;
	standardize(str2);
	
	for(int i=0;i<result.size();i++) 
		if(isSubstr(book[result[i]].getTitle(), str1, 0) &&isSubstr(book[result[i]].getAuthor(), str2, 0))
		{
			cout<<book[result[i]]<<endl;
			new_result.push_back(result[i]);
		}
}

void Database::or(vector<int> &result, vector<int> &new_result)
{
	string str1, str2;
	
	cout<<"\nThe database will ask for string inputs first and then your choice if it is Title or Author. Please give inputs carefully. ";
	cout<<"\n\tInstead of spaces enter underscores (_)";
	cout<<"\n\tEnter 1st string to search: ";
	cin>>str1;
	standardize(str1);
	cout<<"\n\tEnter 2nd string for search: ";
	cin>>str2;
	standardize(str2);
	if(str2 == "_")
		str2 = "";

	if(Title_or_Author() == 1)
		for(int i=0;i<result.size();i++) 
		{
			if(isSubstr(book[result[i]].getTitle(), str1, 0) || isSubstr(book[result[i]].getTitle(), str2, 0)) 
			{
				cout<<book[result[i]]<<endl;
				new_result.push_back(result[i]);
			}
		}
	else
		for(int i=0;i<result.size();i++) 
		{
			if(isSubstr(book[result[i]].getAuthor(), str1, 0) || isSubstr(book[result[i]].getAuthor(), str2, 0)) 
			{
				cout<<book[result[i]]<<endl;
				new_result.push_back(result[i]);
			}
		}
}

void Database::not(vector<int> &result, vector<int> &new_result)
{
	string str1, str2;
	cout<<"\nThe database will ask for string input first and then your choice if it is Title or Author. Please give input carefully. ";
	cout<<"\n\tInstead of spaces enter underscores (_)";
	cout<<"\n\tEnter the string 'NOT' to search: ";
	cin>>str1;
	standardize(str1);
	if(Title_or_Author() == 1)
		for(int i=0;i<result.size();i++)
		{
			if(!(isSubstr(book[result[i]].getTitle(), str1, 0)))
			{
				cout<<book[result[i]]<<endl;
				new_result.push_back(result[i]);
			}
		}
		else
			for(int i=0;i<result.size();i++) 
			{
				if(!(isSubstr(book[result[i]].getAuthor(), str1, 0)))
				{
					cout<<book[result[i]]<<endl;
					new_result.push_back(result[i]);
				}
			}

}

void Database::range(vector<int> &result, vector<int> &new_result)
{
	int minima, maxima;
	do 
	{
		cout<<"Enter minimum Range for search : "<<endl;
		inputCheck(minima);
		if(minima<0)
		{
			cin.clear();
			cin.ignore(256, '\n');
			inputCheck(minima);
		}
						
		cout<<"Enter maximum Range for search: "<<endl;
		inputCheck(maxima);
		if(maxima<0)
		{
			cin.clear();
			cin.ignore(256, '\n');
			inputCheck(maxima);
		}
		if(minima>=maxima) 
		{
			cout<<"cannot perform search with maximum less than minimum"<<endl;
			cout<<"Please input again"<<endl;
		}
		
		else
			break;
 	}while(true);

	if(year_or_pages() == 1)
		for(int i = 0;i< result.size(); i++) 
		{
			if(book[result[i]].getDateOfPublication() >= minima && book[result[i]].getDateOfPublication() <= maxima) 
			{
				cout<<book[result[i]]<<endl;
				new_result.push_back(result[i]);
			}
		}
	else
		for(int i = 0;i< result.size(); i++) 
		{
			if(book[result[i]].getNumberOfPages() >= minima && book[result[i]].getNumberOfPages() <= maxima) 
			{
				cout<<book[result[i]]<<endl;
				new_result.push_back(result[i]);
			}
		}
}

void Database::compoundSearch(vector<int> &result)
{
	char ch = 'y';
	do
	{
		//result in the book from previous search;
		system("cls");
		int choice;
		vector<int> new_result;

		cout<<"AND, OR AND NOT SEARCH ARE AVAILABLE FOR AUTHOR AND TITLE. \nIN BETWEEN IS TO SPECIFY A RANGE FOR NUMBER OF PAGES AND DATE OF PUBLICATION.";
		cout<<"\n\nfor and, or and not searches, input strings are substrings to search for. To not enter a string2, just enter _ and press enter. ";
		cout<<"\n\nOptions: \n\t1. AND Search \n\t2. OR Search \n\t3. NOT Search \n\t4. In Between \n\nEnter Choice: ";
		inputCheck(choice);
		if(choice<1 || choice>4)
		{
			cin.clear();
			cin.ignore(256, '\n');
			inputCheck(choice);
		}
		switch(choice)
		{
			case 1: and(result, new_result);
					break;

			case 2:	or(result, new_result);
					break;

			case 3: not(result, new_result);
					break;

			case 4:	range(result, new_result);
					break;
		}

		result.clear();
		result = new_result;		//updating our result to have narrowed down results from one compund search
		new_result.clear(); 
		cout<<"\n\nDo you want to add more filters to the search (Press y for yes, any other character for no): ";
		cin>>ch;
	}while(ch == 'y' || ch  == 'Y');

}

//global functions that are called in main menu

void simpleSearch()	//search menu for searching by one attribute
{	
	char ch = 'y';
	do
	{
		system("cls");
		int choice;
		vector<Book> temp;
		cout<<"Search Options: \n\t1.Search by Title \n\t2.Search by Author \n\t3.Search by Date Of Publication \n\t4.Search by Book Type \n\t5.Search by Number Of Pages \n\t6.Search by unique ID \n\nEnter Choice: ";
		inputCheck(choice);
		if(choice<1 || choice>6)
		{
			cin.clear();
			cin.ignore(256, '\n');
			inputCheck(choice);
		}
		switch(choice)
		{
			case 1: dataBase.searchTitle();
					break;
			case 2: dataBase.searchAuthor();
					break;
			case 3: dataBase.searchDOP();
					break;
			case 4: dataBase.searchType();
					break;
			case 5: dataBase.searchNumOfPages();
					break;
			case 6: dataBase.searchID();
					break;
		}
		cout<<"\n\nDo you want to perform another simple search? (Press y for yes, any other character for no): ";
		cin>>ch;
	}while(ch == 'y' || ch  == 'Y');
	system("cls");
}

void complexSearch()
{
	vector<int> result;
	for(int i = 0; i<dataBase.getSize(); i++)
		result.push_back(i);
	dataBase.compoundSearch(result);
}

void search()		//search main menu displaying different search options
{
	if(dataBase.empty())
	{
		cout<<"\nNo data in database to search from. "<<endl;
		system("pause");
		return;
	}
	char ch = 'y';
	do
	{
		system("cls");
		int choice;
		cout<<"\nSearch Options : \n\t1.Simple Search (using only one parameter) \n\t2.Compound Search (using AND, OR, NOT to search multiple possibilities) \nEnter choice: ";
		inputCheck(choice);
		if(choice <1 || choice>2)
		{
			cin.clear();
			cin.ignore(256, '\n');
			inputCheck(choice);
		}
		switch(choice)
		{
			case 1: simpleSearch();
					break;

			case 2: complexSearch();
					break;
		}
		cout<<"\n\nDo you want to perform another search? (Press y for yes, any other character for no): ";
		cin>>ch;
	}while(ch == 'y' || ch  == 'Y');
	system("cls");
}

void add()		//function to add entries to database
{
	char ch = 'y';
	do
	{
		system("cls");
		Book book;
		cin>>book;
		dataBase.create(book);
		cout<<"\nEntry you added: "<<book;
		cout<<"\n\nDo you want to add more entries? (Press y for yes, any other character for no): ";
		cin>>ch;
	}while(ch == 'y' || ch  == 'Y');
	system("cls");				
}

void delete_rec()	//function to identify the correct entry to be deleted and then call  member function to delete
{
	char ch = 'y';
	do
	{
		if(dataBase.empty())
		{
			cout<<"\nNo data in database to delete from. "<<endl;
			system("pause");
			return;
		}
		
		system("cls");
		int choice;
		cout<<"\nTo delete an entry, you need to know the corresponding ID. \n\t1.If you know the ID, press 1 \n\t2.If you'd like to search for entry via other attributes, press 2 \nEnter choice: ";
		inputCheck(choice);
		if(choice<1 || choice>2)
		{
			cin.clear();
			cin.ignore(256, '\n');
			inputCheck(choice);
		}
		switch(choice)
		{
			case 2: cout<<"\nPlease remember the ID when you complete the search.";
					search();
				
			case 1: int index = dataBase.searchID();
					dataBase.remove(index);
					break;				
		}			
		cout<<"\n\nDo you want to remove more entries? (Press y for yes, any other character for no): ";
		cin>>ch;
	}while(ch == 'y' || ch  == 'Y');
	system("cls");
}

void modify()	//function to identify the correct entry to be modified and then call  member function to update
{
	if(dataBase.empty())
	{
		cout<<"\nNo data in database to modify. "<<endl;
		system("pause");
		return;
	}
	char ch = 'y';
	do
	{
		system("cls");
		int choice;
		cout<<"\nTo modify an entry, you need to know the corresponding ID. \n\t1.If you know the ID, press 1 \n\t2.If you'd like to search for entry via other attributes, press 2 \nEnter choice: ";
		inputCheck(choice);
		if(choice<1 || choice>2)
		{
			cin.clear();
			cin.ignore(256, '\n');
			inputCheck(choice);
		}
		switch(choice)
		{
			case 2: search();
					
			case 1: int index = dataBase.searchID();
					dataBase.update(index);
					break;				
		}
		cout<<"\n\nDo you want to perform modification for a DIFFERENT entry? (Press y for yes, any other character for no): ";
		cin>>ch;
	}while(ch == 'y' || ch  == 'Y');
	system("cls");				
}

void view()		//function to view the entire database stored in program
{
	system("cls");
	if(dataBase.empty())
	{
		cout<<"\nNo data in database to display. "<<endl;
		system("pause");
		return;
	}
	cout<<"\nBOOK DATABASE: "<<endl<<endl;
	dataBase.display();
}

void save_db()
{
	system("cls");
	if(dataBase.empty())
	{
		cout<<"\nNo data in database to save. "<<endl;
		system("pause");
		return;	
	}
	cout<<"\nThe current database will be appended to the original file saving databases. Current database will be DATABASE "<<dbm<<". "<<endl;
	dataBase.save();

	cout<<"\nDatabase has been saved!"<<endl;
	dbm++;
}

void load_db()
{
	system("cls");
	int choice;
	cout<<"\nSINCE WE WILL BE ADDING NEW DATA TO THE DATABASE, NEW IDs WILL BE ASSIGNED TO INCOMING BOOKS. ";
	cout<<"\nOptions: \n\t1.Append the loaded database to the current database you're working with. ";
	cout<<"\n\t2.Save your current database in a file and start afresh with the loaded database. ";
	cout<<"\n\t3.Delete the current database without saving and start afresh with the loaded database. \nEnter choice: ";
	inputCheck(choice);
	if(choice<1 || choice>3)
	{
		cin.clear();
		cin.ignore(256, '\n');
		inputCheck(choice);
	}
	switch(choice)
	{
		case 1: dataBase.append();
				break;

		case 2: save_db();
				
		case 3: dataBase.clean();
				dataBase.append();
				break;
	}

	cout<<"\nNew database is ready to be used !"<<endl;
}

void delete_file()		 
{
	ofstream fout("MyDatabase.txt", ios::trunc);		//truncating mode
	fout.close();
}

void marquee()
{
	system("cls");
	system("Color 0F");
	cout<<"\t\t\t\tThank You! Good Night!\n";
	for(int i=0;i<100;i++)
	{	
		cout<<setw(10+i)<<"*";
		for(int j=0;j<9000000;j++);
	}
}

int input = 0;

//MAIN MENU

int main()
{
	system("Color 0A");
	cout<<"\t\t\t\tLoading... Please Wait :)\n\n";
	for(int i=0;i<100;i++)
	{		
		cout<<"=";
		for(int j=0;j<9000000;j++);
	}

	system("cls");
	system("Color 0F");
	delete_file();			//clearing any saved content in the output file before programme run
	do
	{
		system("cls");
		int choice;
		cout<<"\nWelcome to the Book Database. What would you like to do: \n\t1.Add a new entry \n\t2.Delete an entry";
		cout<<"\n\t3.Update an entry \n\t4.Search for an entry \n\t5.Load the database from a file \n\t6.Save the database to a file";
		cout<<"\n\t7.Display the entire database \n\t8.Exit From the Program \n\nEnter choice: ";
		inputCheck(choice);
		if(choice<1 || choice>8)
		{
			cin.clear();
			cin.ignore();
			inputCheck(choice);
		}
		switch(choice)
		{
			case 1: add();
					input++;
					if(dbm == 0)
						dbm = 1;
					break;

			case 2: delete_rec();
					if(dataBase.empty() && input != 0)
					{
						char ch;
						cout<<"\nYour database does not have any more entries. Did you save this database onto file before deleting everything ? (press y for yes, any other character for no) ";
						cin>>ch;
						if(ch=='y' || ch == 'Y')
							cout<<" ";
						else
							dbm--;
					}
					break;

			case 3: modify();
					break;
			
			case 4: search();
					break;

			case 5: if(dbm == 0)
						dbm = 1;
					input++;
					load_db();
					system("pause");
					break;

			case 6: save_db();
					system("pause");
					break;

			case 7: view();
					system("pause");
					break;

			case 8: marquee();
					return 0;
					break;
		
		}
	}while(true);
	return 0;
}


