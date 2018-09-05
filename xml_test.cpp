#include "lib/tinyxml.h"
#include <string>
#include <cstdlib>
#include <iostream>


using namespace std;

int xmlgenerater()
{
	printf("\n\n\t generating xml file, wait\n\n");

	return 1;
}
int jsonexporter()
{
	printf("\n\n\t exporting Json file, wait\n\n");

	return 1;
}

int main()
{
	TiXmlDocument doc("test.xml");

	if (doc.LoadFile())
	{
		TiXmlElement* element = doc.FirstChildElement("Hello");
		std::string text = element->GetText();
	} 
	TiXmlDocument newfile;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "utf-8", "");
	newfile.LinkEndChild(decl);

	TiXmlElement * root;
	root = new TiXmlElement("MyApp");
	root->SetAttribute("value", "5");
	root->SetAttribute("name", "me");
	newfile.LinkEndChild(root);

	newfile.SaveFile("new.xml");
	char option = '1';
	while (option != '0')
	{
		printf("\nMenu Principal");
		printf("\n1 - XML generation");
		printf("\n2 - JSON export");
		printf("\n0 -  to exit \n");
		cin >> option;
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

	/*<xsd:schema xmlns : xsd = "http://www.w3.org/2001/XMLSchema" xmlns :
		bit = "http://example.org/types" targetNamespace = "http://example.org/types" >
		<xsd:complexType name = "XType">
		<xsd:sequence>
		<xsd:element name = "stringMember" type = "xsd:string" / >
		<xsd:element name = "intMember" type = "xsd:int" / >
		< / xsd:sequence>
		< / xsd:complexType>
		<xsd:element name = "a" type = "bit:XType" / >
		< / xsd:schema>
*/
	return 0;
}					