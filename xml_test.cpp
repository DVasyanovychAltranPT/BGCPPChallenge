// XSD_parser.cpp : Defines the entry point for the console application.
//

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#pragma region Declarations

string GIVENNAME;

struct X_string {
	string Line;
};
struct X_int {
	int inter;
};
struct X_bool {
	bool Booler;
};
struct X_float {
	float floater;
};
struct X_char {
	char character;
};

vector<X_string> file_content;
vector<X_string> my_containers;

string i_complexType = "<xsd:complexType";
string i_complexType_end = "</xsd:complexType";
string i_sequence = "<xsd:sequence";
string i_sequence_end = "</xsd:sequence";
string i_element = "<xsd:element";
string i_name = "name=";
string i_type = "type=";
string delimiter = "\"";
bool complexType_flag;
bool sequence_flag;
#pragma endregion


int reader()
{
	const char* readfile = GIVENNAME.c_str();
	string line;
	ifstream infile;
	infile.open(readfile);
	int i = 0;
	while (!infile.eof()) // To get all the lines from file one by one.
	{
		getline(infile, line); // Saves the line from file.
		//cout << line << endl; 
		file_content.push_back(X_string());
		file_content[i].Line = line;
		//cout << file_content[i].XSD_LINE << endl; 
		i++;
	}
	infile.close();
	return 0;
}


void add_to_containers(string container_name)
{
	size_t size = my_containers.size();
	my_containers.push_back(X_string());
	my_containers[size].Line = container_name;
}

string find_my_name(string in_here, string this_thing)
{
	vector<X_int> found_in_this_lines;
	int size = i_name.size();
	std::size_t f_contentType = 0;
	std::size_t f_name = 0;
	std::size_t the_name = 0;
	string long_name = " ";
	string name_is = " ";
	f_contentType = in_here.find(this_thing);
	if (f_contentType != std::string::npos)
	{//this line contains this_thing, lets find the NAME
		f_name = in_here.find(i_name);
		if (f_name != std::string::npos)
		{
			long_name = in_here.substr(f_name + size + 1);
			the_name = long_name.find(delimiter);
			if (the_name != std::string::npos)
			{
				name_is = long_name.substr(0, the_name);
				cout << "name:" << name_is << endl;
			}
		}
	}
	return name_is;
}

string find_my_type(string in_here, string this_thing)
{
	vector<X_int> found_in_this_lines;
	int size = i_name.size();
	std::size_t f_contentType = 0;
	std::size_t f_type = 0;
	std::size_t the_type = 0;
	string long_type = " ";
	string type_is = " ";
	f_contentType = in_here.find(this_thing);
	if (f_contentType != std::string::npos)
	{//this line contains this_thing, lets find the type
		f_type = in_here.find(i_type);
		if (f_type != std::string::npos)
		{
			long_type = in_here.substr(f_type + size + 1);
			the_type = long_type.find(delimiter);
			if (the_type != std::string::npos)
			{
				type_is = long_type.substr(0, the_type);
				cout << "type:" << type_is << endl;
			}
		}
	}
	return type_is;
}

bool find_complex(string in_here)
{
	std::size_t f_contentType = 0;
	string name_is = " ";
	f_contentType = in_here.find(i_complexType);
	if (f_contentType != std::string::npos)
	{
		complexType_flag = true;
		name_is = find_my_name(in_here, i_complexType);//find its name
		add_to_containers(name_is);

	}
	f_contentType = in_here.find(i_complexType_end);
	if (f_contentType != std::string::npos)
	{
		complexType_flag = false;
	}

	//cout << "sequence:" << complexType_flag << endl;
	return complexType_flag;
}

bool find_sequence(string in_here)
{
	std::size_t f_contentType = 0;
	std::size_t f_name = 0;
	std::size_t f_result = 0;
	string long_name = " ";
	string name_is = " ";
	f_contentType = in_here.find(i_sequence);
	if (f_contentType != std::string::npos)
	{
		sequence_flag = true; 
	}
	f_contentType = in_here.find(i_sequence_end);
	if (f_contentType != std::string::npos)
	{
		sequence_flag = false;
	}

	//cout << "sequence:" << sequence_flag << endl;
	return sequence_flag;
}

int searcher() 
{
	int i = 0;
	int n_file_lines = file_content.size();
	complexType_flag = false;
	while(n_file_lines > i)
	{
		if (complexType_flag)
		{
			if (sequence_flag)
			{
				//search elements
				cout << find_my_name(file_content[i].Line, i_element);
				cout << find_my_type(file_content[i].Line, i_element);
				find_sequence(file_content[i].Line);// find sequence
			}
			else
			{
				find_sequence(file_content[i].Line);// find sequence
			}
			find_complex(file_content[i].Line);// find if complextype
		}
		else
		{
			find_complex(file_content[i].Line);// find if complextype
			cout << find_my_name(file_content[i].Line, i_complexType);//find its name
		}
		//cout << "searching in " << file_content[i].Line << endl;
		i++;
	}
	return 0;
}


int xmlgenerater()
{
	complexType_flag = false;
	sequence_flag = false;
	reader();
	searcher();
	printf("\n\n\t generating xml file, wait\n\n");

	
	/*
	< ? xml version = "1.0" encoding = "utf-8" ? >
	<a xmlns = "http://example.org/types" xsi : schemaLocation = "http://example.org/types schema.xsd" xmlns : xsi = "http://www.w3.org/2001/XMLSchema-instance">
	<stringMember>string< / stringMember>
	<intMember>5348< / intMember>
	< / a>
	*/
	return 1;
}
int jsonexporter()
{
	printf("\n\n\t exporting Json file, wait\n\n");

	return 1;
}

int menu_for_file_selection() 
{
	char yes_no;
	printf("\nIS XSD xsd.xsd ?\n");

	cin >> yes_no;
	switch (yes_no)
	{
	case 'n':
		printf("\nINSERT NAME OF XSD \n");
		cin >> GIVENNAME;
		break;
	default:
		GIVENNAME = "xsd.xsd";
		break;
	}
	return 0;
}

int main(int argc, char* argv[])
{
#pragma region  entrance arguments
	if (argc == 2) {
		printf("The argument supplied is %s\n", argv[1]);
		GIVENNAME = argv[1];
	}
	else if (argc > 2) {
		printf("Too many arguments supplied.\n");
	}
	else {
		printf("One argument expected.\n");
		menu_for_file_selection();
	}
#pragma endregion

#pragma region MENU
	char option = '1';
	while (option != '0')
	{
		printf("\nMenu Principal");
		printf("\n1 - XML generation");
		printf("\n2 - JSON export");
		printf("\n0 -  to exit \n");
		//cin >> option;
		string s;
		getline (cin, s);
		option = s.at(0);
		switch (option)
		{
		case '1':
			xmlgenerater();
			break;
		case '2':
			jsonexporter();
			break;
		case '0':
			cout << "exiting!";
			option = '0';
			break;
		default:
			break;
		}
	}
#pragma endregion
	return 0;
}
