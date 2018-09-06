// XSD_parser.cpp : Defines the entry point for the console application.
//

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


string GIVENNAME;

struct XSD_CONTENT {
	string XSD_LINE;

};
vector<XSD_CONTENT> file_content;
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
		file_content.push_back(XSD_CONTENT());
		file_content[i].XSD_LINE = line;
		cout << file_content[i].XSD_LINE;
		cout << endl;
		i++;
	}
	infile.close();
	return 0;
}

int xmlgenerater()
{
	reader();

	printf("\n\n\t generating xml file, wait\n\n");

	string i_start			= "<xsd:";
	string i_schema			= "schema";
	string i_complexType	= "complexType";
	string i_element		= "element";
	string i_sequence		= "sequence";
	string i_name			= "name=\"";
	string i_type			= "type=\"";	
	string i_end			= "</xsd:";

	string i_this			= " ";
	
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
