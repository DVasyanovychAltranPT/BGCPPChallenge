// XSD_parser.cpp : Defines the entry point for the console application.
//

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
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

string i_prefix = "fake";
string i_prefix_e = "fake";
string i_prefix_link = "http://fake.fake/types";
string i_end = "</";
string i_start = "<";
string i_complexType = "complexType";
string i_complexType_start = "complexType";
string i_complexType_end = "complexType";
string i_schema = "schema";
string i_schema_start = "schema";
string i_sequence = "sequence";
string i_sequence_start = "sequence";
string i_sequence_end = "sequence";
string i_element = "element";
string i_element_start = "element";
string i_name = "name=";
string i_xmlns = "xmlns:";
string i_type = "type=";
string delimiter = "\"";
bool complexType_flag;
bool sequence_flag;
ofstream myFile;
static const char alphanum[] = "0123456789" "!@#$%^&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
int stringLength;
#pragma endregion


void add_to_containers(string line)
{
	File_Size = file_content.size();
	file_content.push_back(X_string());
	file_content[static_cast<int>(File_Size)].Line = line;
}

int reader()
{
	const char* readfile = GIVENNAME.c_str();
	string line;
	ifstream infile;
	infile.open(readfile);
	if (!infile.is_open())
	{
		printf("please provide XSD file");
		return -1;
	}
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
	std::ostringstream sss;
	std::string random_string = "";
	long num = clock();
	int sizi = num % 9;
	if (sizi <2)
	{
		sizi = 2;
	}
	sss << num;
	string value = " ";
	if (type == "xsd:string")
	{
		for (int i = 0; i < sizi; i++)
		{
			random_string.push_back((alphanum[(num*i) % stringLength]));
		}
		value = random_string;
	}
	if (type == "xsd:int")
	{
		value = sss.str();
	}
	if (type == "xsd:bool")
	{
		sss << static_cast<bool>((num % 4) / 2);
		value = sss.str();
	}
	if (type == "xsd:float")
	{
		sss << static_cast <float> (num) / static_cast <float> (RAND_MAX);
		value = sss.str();
	}
	if (type == "xsd:double")
	{
		sss << static_cast <double> (num) / static_cast <double> (RAND_MAX);
		value = sss.str();
	}
	return value;
}

void populate_container(int position, string name, string type, string element)
{
	if (position < static_cast<int>(File_Size))
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
		/*
		cout << position << " "
		<< file_content[position].Declaration << "-"
		<< file_content[position].Element << "-"
		<< file_content[position].Name  << "-"
		<< file_content[position].VType << "-"
		<< file_content[position].Value << " "<< endl;
		*/
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


int find_prefix(string in_here, int this_line)
{
	std::size_t pos_found = 0;
	std::size_t pos_found1 = 0;
	std::size_t pos_found2 = 0;
	std::size_t pos_found3 = 0;
	string prefix1_is = " ";
	string prefix2_is = " ";
	
	pos_found = in_here.find(i_schema_start);
	if (pos_found != std::string::npos)
	{
		prefix1_is = find_(in_here, i_xmlns);//find 1 xmlns prefix 
		if (prefix1_is != " ")
		{
			pos_found1 = prefix1_is.find(" ");
			if (pos_found1 != std::string::npos)
			{
				prefix2_is = prefix1_is.substr(pos_found1);// ignore first xmls
				prefix1_is = prefix1_is.substr(0, pos_found1);
			}
			i_prefix = prefix1_is.substr(i_xmlns.size());
			pos_found1 = i_prefix.find("=");
			if (pos_found1 != std::string::npos)
			{
				i_prefix = i_prefix.substr(0, pos_found1);
			}
			prefix2_is = find_(prefix2_is, i_xmlns);//find 2 xmlns prefix
			if (prefix2_is != " ")
			{
				pos_found2 = prefix2_is.find(" ");
				if (pos_found2 != std::string::npos)
				{
					prefix2_is = prefix2_is.substr(0, pos_found2);
				}
				i_prefix_e = prefix2_is.substr(i_xmlns.size());
				pos_found2 = i_prefix_e.find("=");
				if (pos_found2 != std::string::npos)
				{
					i_prefix_e = i_prefix_e.substr(0, pos_found2);
				}

				i_prefix_link = prefix2_is.substr(i_xmlns.size());
				pos_found3 = i_prefix_link.find("\"");
				if (pos_found3 != std::string::npos)
				{
					i_prefix_link = i_prefix_link.substr(pos_found3+1);
				}
				pos_found3 = i_prefix_link.find("\"");
				if (pos_found3 != std::string::npos)
				{
					i_prefix_link = i_prefix_link.substr(0, pos_found3);
				}
			}
			populate_container(this_line, prefix1_is, prefix2_is, i_schema_start);
		}
		
	}
	return 0;
}

bool find_complex(string in_here, int this_line)
{
	std::size_t f_contentType = 0;
	string name_is = " ";
	f_contentType = in_here.find(i_complexType_start);
	if (f_contentType != std::string::npos)
	{
		complexType_flag = true;
		name_is = find_my_name(in_here, i_complexType_start);//find its name
													   //cout << name_is << endl;
		populate_container(this_line, name_is, i_complexType, i_complexType_start);
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
	f_contentType = in_here.find(i_sequence_start);
	if (f_contentType != std::string::npos)
	{
		sequence_flag = true;
		populate_container(this_line, i_sequence_start, i_sequence, i_sequence_start);
	}
	f_contentType = in_here.find(i_sequence_end);
	if (f_contentType != std::string::npos)
	{
		sequence_flag = false;
		populate_container(this_line, i_sequence_end, i_sequence, i_sequence_end);
	}

	//cout << "sequence:" << sequence_flag << endl;
	return sequence_flag;
}

bool find_element(string in_here, int this_line)
{
	std::size_t f_contentType = 0;
	string name_is = " ";
	string type_is = " ";
	f_contentType = in_here.find(i_element_start);
	if (f_contentType != std::string::npos)
	{
		name_is = find_my_name(in_here, i_element_start);
		type_is = find_my_type(in_here, i_element_start);
		populate_container(this_line, name_is, type_is, i_element_start);
	}
	//cout << "sequence:" << sequence_flag << endl;
	return sequence_flag;
}

int set_structure_variables()
{
	int i = 0;
	complexType_flag = false;
	while (static_cast<int>(File_Size) > i)
	{
		find_complex(file_content[i].Line, i);// find if complextype
		find_sequence(file_content[i].Line, i);// find sequence
		find_element(file_content[i].Line, i);// find sequence
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
	for (int i = 0; i < static_cast<int>(File_Size); i++)
	{
		if (file_content[i].Element == i_complexType_end)
		{
			complex_type_flag = false;
			myFile << "</" << i_prefix_e << ":" << element_name << ">" << endl;
		}
		else if (file_content[i].Element == i_complexType_start)
		{
			complex_type_found = find_(element_type, file_content[i].Name);
			if (complex_type_found != " ")
			{
				complex_type_flag = true;
				myFile << "<" << i_prefix_e << ":" << element_name << " "
					<< i_xmlns << i_prefix_e <<"=\""<< i_prefix_link << "\">" << endl;
			}
		}
		else if (complex_type_flag)
		{
			if (file_content[i].Element == i_sequence_end)
			{
				sequence_type_flag = false;
			}
			else if (file_content[i].Element == i_sequence_start)
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

int set_starting_types()
{
	int i = 0;
	complexType_flag = false;
	while (static_cast<int>(File_Size) > i)
	{
		find_prefix(file_content[i].Line, i);// find if prefix
		i++;
	}
	i_complexType_start = i_start + i_prefix + ":" + i_complexType;
	i_complexType_end = i_end + i_prefix + ":" + i_complexType;
	i_schema_start = i_start + i_prefix + ":" + i_schema;
	i_sequence_start = i_start + i_prefix + ":" + i_sequence;
	i_sequence_end = i_end + i_prefix + ":"+ i_sequence;
	i_element_start = i_start + i_prefix + ":" + i_element;
	return 0;
}

int generater()
{
	myFile.open("new.xml");
	myFile << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;
	for (int i = 0; i < static_cast<int>(File_Size); i++)
	{
		if (!file_content[i].Declaration && file_content[i].Element == i_element_start)
		{
			create_element(file_content[i].VType, file_content[i].Name);
		}

	}
	myFile.close();
	return 0;
}
int xmlgenerater()
{
	stringLength = sizeof(alphanum) - 1;
	clear_history();
	complexType_flag = false;
	sequence_flag = false;
	//printf("\n\n\t reading xsd file, wait");
	if (reader() == -1)
	{
		return -1;
	}
	set_starting_types();
	printf(".");
	set_structure_variables();
	printf("..\n\n");
	printf("\n\n\t generating xml file, wait\n\n");

	generater();
	return 1;
}

int create_element_json(string element_type, string element_name)
{

	bool complex_type_flag = false;
	bool sequence_type_flag = false;
	string complex_type_found = " ";
	string sequence_type_found = " ";
	bool  first_time = true;
	for (int i = 0; i < static_cast<int>(File_Size); i++)
	{
		if (file_content[i].Element == i_complexType_end)
		{
			complex_type_flag = false;
			myFile << endl << "}" << endl;
		}
		else if (file_content[i].Element == i_complexType_start)
		{
			complex_type_found = find_(element_type, file_content[i].Name);
			if (complex_type_found != " ")
			{
				complex_type_flag = true;
				myFile << "\"" << i_prefix_e << ":" << element_name << "\":{" << endl;
				myFile << "\"-" << i_xmlns << i_prefix_e << "\": \"" << i_prefix_link << "\",";
				first_time = true;
			}
		}
		else if (complex_type_flag)
		{
			if (file_content[i].Element == i_sequence_end)
			{
				sequence_type_flag = false;
			}
			else if (file_content[i].Element == i_sequence_start)
			{
				sequence_type_flag = true;
			}
			else if (sequence_type_flag && !first_time)
			{
				first_time = false;
				myFile << "," << endl << "\"" << file_content[i].Name << "\":"
					<< "\"" << file_content[i].Value << "\"";
			}

			else if (sequence_type_flag && first_time)
			{
				first_time = false;
				myFile << endl << "\"" << file_content[i].Name << "\":"
					<< "\"" << file_content[i].Value << "\"";
			}
		}
	}

	return 0;
}

int generater_json()
{
	myFile.open("new.json");
	myFile << "{" << endl;
	for (int i = 0; i < static_cast<int>(File_Size); i++)
	{
		if (!file_content[i].Declaration && file_content[i].Element == i_element_start)
		{
			create_element_json(file_content[i].VType, file_content[i].Name);
		}

	}

	myFile << "}" << endl;
	myFile.close();
	return 0;
}
int jsonexporter()
{
	printf("\n\n\t exporting Json file, wait\n\n");
	generater_json();
	return 1;
}

int menu_for_file_selection()
{
	char yes_no;
	string s;
	printf("\nIS XSD template.xsd ?\n");

	//cin >> yes_no;
	getline(cin, s);
	yes_no = s.at(0);
	switch (yes_no)
	{
	case 'n':
		printf("\nINSERT NAME OF XSD \n");
		//cin >> GIVENNAME;
		getline(cin, s);
		GIVENNAME = s;
		break;
	default:
		GIVENNAME = "template.xsd";
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
		getline(cin, s);
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
