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
	bool Declaration;
	string Element;
	string Name;
	string VType;
	string Value;
};

vector<X_string> file_content;
size_t File_Size = 0;

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
ofstream myFile;
#pragma endregion


void add_to_containers(string line)
{
	File_Size = file_content.size();
	file_content.push_back(X_string());
	file_content[File_Size].Line = line;
}

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
		add_to_containers(line);
		//cout << file_content[i].XSD_LINE << endl; 
		i++;
	}
	infile.close();
	return 0;
}
 
string random(string type)
{
	string value = " ";
	if (type == "xsd:string")
	{
		value = "I_am_string";
	}
	if (type == "xsd:int")
	{
		value = "I_am_int";
	}
	if (type == "xsd:bool")
	{
		value = "I_am_bool";
	}
	if (type == "xsd:float")
	{
		value = "I_am_float";
	}
	if (type == "xsd:double")
	{
		value = "I_am_double";
	}
	return value;
}


void populate_container(int position, string name, string type, string element)
{ 
	if (position <File_Size)
	{
		file_content[position].Name = name;
		file_content[position].VType = type;
		file_content[position].Element = element;

		file_content[position].Value = random(type);

		if (complexType_flag && sequence_flag)
		{
			file_content[position].Declaration = true;
		}
		else
		{
			file_content[position].Declaration = false;
		}

		cout << position << " " 
			<< file_content[position].Declaration << "-"
			<< file_content[position].Element << "-"
			<< file_content[position].Name  << "-"
			<< file_content[position].VType << "-"
			<< file_content[position].Value << " "<< endl;
	}
	else
	{
		cout << "invalid insert to position:" << position << endl;
	}
}

void clear_history()
{
	file_content.clear();
}

string find_(string in_here, string this_thing)
{
	std::size_t pos = 0;
	string found_this = " ";
	pos = in_here.find(this_thing);
	if (pos != std::string::npos)
		found_this = in_here.substr(pos);
	return found_this;
}
string find_my_name(string in_here, string this_thing)
{
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
				//cout << "name:" << name_is << endl;
			}
		}
	}
	return name_is;
}

string find_my_type(string in_here, string this_thing)
{
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
				//cout << "type:" << type_is << endl;
			}
		}
	}
	return type_is;
}

bool find_complex(string in_here, int this_line)
{
	std::size_t f_contentType = 0;
	string name_is = " ";
	f_contentType = in_here.find(i_complexType);
	if (f_contentType != std::string::npos)
	{
		complexType_flag = true;
		name_is = find_my_name(in_here, i_complexType);//find its name
		//cout << name_is << endl;
		populate_container(this_line, name_is, i_complexType, i_complexType);
	}
	f_contentType = in_here.find(i_complexType_end);
	if (f_contentType != std::string::npos)
	{
		complexType_flag = false;
		populate_container(this_line, i_complexType_end, i_complexType_end, i_complexType_end);
	}

	//cout << "sequence:" << complexType_flag << endl;
	return complexType_flag;
}

bool find_sequence(string in_here, int this_line)
{
	std::size_t f_contentType = 0;
	f_contentType = in_here.find(i_sequence);
	if (f_contentType != std::string::npos)
	{
		sequence_flag = true;
		populate_container(this_line, i_sequence, i_sequence, i_sequence);
	}
	f_contentType = in_here.find(i_sequence_end);
	if (f_contentType != std::string::npos)
	{
		sequence_flag = false;
		populate_container(this_line, i_sequence_end, i_sequence_end, i_sequence_end);
	}

	//cout << "sequence:" << sequence_flag << endl;
	return sequence_flag;
}

bool find_element(string in_here, int this_line)
{
	std::size_t f_contentType = 0;
	string name_is = " ";
	string type_is = " ";
	f_contentType = in_here.find(i_element);
	if (f_contentType != std::string::npos)
	{
		name_is = find_my_name(in_here, i_element);
		type_is = find_my_type(in_here, i_element);
		populate_container(this_line, name_is, type_is, i_element);
	}
	//cout << "sequence:" << sequence_flag << endl;
	return sequence_flag;
}

int searcher() 
{
	int i = 0;
	complexType_flag = false;
	while(File_Size > i)
	{
		find_complex(file_content[i].Line,i);// find if complextype
		find_sequence(file_content[i].Line,i);// find sequence
		find_element(file_content[i].Line,i);// find sequence
		i++;
	}
	return 0;
}

int create_element(string element_type, string element_name)
{

	bool complex_type_flag = false;
	bool sequence_type_flag = false;
	string complex_type_found = " ";
	string sequence_type_found = " ";
	for (int i = 0; i < File_Size; i++)
	{
		if (file_content[i].Element == i_complexType_end)
		{
			complex_type_flag = false;
			myFile << "</" << element_name << ">" << endl;
		}
		else if (file_content[i].Element == i_complexType)
		{
			complex_type_found = find_(element_type, file_content[i].Name);
			if (complex_type_found != " ")
			{
				complex_type_flag = true;
				myFile << "<" << element_name << ">" << endl;

			}
		}
		else if (complex_type_flag)
		{ 
			if (file_content[i].Element == i_sequence_end)
			{
				sequence_type_flag = false;
			}
			else if (file_content[i].Element == i_sequence)
			{
				sequence_type_flag = true;
			}

			else if (sequence_type_flag)
			{
				myFile << "<" << file_content[i].Name << ">"
					<< file_content[i].Value
					<< "</" << file_content[i].Name << ">" << endl;
			}
		} 
	}

	return 0;
}


int generater()
{
	myFile.open("new.xml");
	myFile << "<" << "? xml version = \"1.0\" encoding = \"utf - 8\" ?" << ">" << endl;
	for (int i = 0; i < File_Size; i++)
	{
		if(!file_content[i].Declaration && file_content[i].Element == i_element)
		{
			create_element(file_content[i].VType, file_content[i].Name);
		}

	}
	myFile.close();
	return 0;
}
int xmlgenerater()
{
	clear_history();
	complexType_flag = false;
	sequence_flag = false;
	//printf("\n\n\t reading xsd file, wait");
	reader();
	//printf(".");
	searcher();
	//printf("..\n\n");
	printf("\n\n\t generating xml file, wait\n\n");

	generater();
	
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
