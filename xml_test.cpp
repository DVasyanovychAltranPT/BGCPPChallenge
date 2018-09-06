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
vector<X_int> find_me(string this_thing, int from_this_line, int to_this_line)
{
	vector<X_int> found_in_this_lines;

	return found_in_this_lines;
}
int searcher() 
{
	string i_start			= "";
	string i_schema			= "schema";
	string i_complexType	= "<xsd:complexType";
	string i_element		= "<xsd:element";
	string i_sequence		= "<xsd:sequence";
	string i_name			= "name=";
	string i_type			= "type=";	
	string i_end			= "</xsd:";

	string i_this			= " ";
	string long_name		= " ";

	int i				= 0;
	std::size_t found	= 0;
	std::size_t found_2 = 0;
	std::size_t found_3 = 0;
	int n_file_lines = file_content.size();
	while(n_file_lines > i)
	{
		found = 0;
		found_2 = 0;
		found_3 = 0;
		found = file_content[i].Line.find(i_complexType);
		cout << "searching in " << file_content[i].Line << endl;
		if (found != std::string::npos)
		{//this line contains complexType, lets find its name
			found_2 = file_content[i].Line.find(i_name);
			if (found_2 != std::string::npos)
			{
				long_name = file_content[i].Line.substr(found_2+ i_name.size());
				found_3 = long_name.find("\"");
				if (found_3 != std::string::npos)
				{
					i_this = long_name.substr(0, found_3); 
					add_to_containers(i_this);
					//cout << my_containers[containers_n].Line << endl;
				}
			}
		}
		i++;
	}
	return 0;
}


int xmlgenerater()
{
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
