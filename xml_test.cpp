#include "stdafx.h"
#include "lib/tinyxml.h"
#include <string>
#include <iostream>

using namespace std;

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
		printf("Menu Principal");
		printf("\n1 - ");
		printf("\n2 - ");
		printf("\n3 - ");
		scanf("\nc", &option);
		switch (option)
		{
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			default:
				option = '0';
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