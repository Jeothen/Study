#include "tinyxml.h"
#include <iostream>
using namespace std;

int main()
{
	//xml 선언
	TiXmlDocument doc;
	TiXmlDeclaration* pDec1 = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(pDec1);

	//루트 노드 추가
	TiXmlElement* pRoot = new TiXmlElement("DB");
	doc.LinkEndChild(pRoot);

	//주석 문장 추가
	TiXmlComment* pComment = new TiXmlComment();
	pComment->SetValue("This is score DB");
	pRoot->LinkEndChild(pComment);

	// 하위노드 및 데이터 추가
	TiXmlElement* pElem = new TiXmlElement("class1");
	pRoot->LinkEndChild(pElem);
	TiXmlElement* pElem0 = new TiXmlElement("Teacher");
	pElem0->LinkEndChild(new TiXmlElement("JJJ"));
	pElem->LinkEndChild(pElem0);

	//하위노드 및 속성 추가
	TiXmlElement* pSubElem = new TiXmlElement("English");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("aa", 100);
	pSubElem->SetAttribute("bb", 50);
	pSubElem->SetAttribute("cc", 90);

	pSubElem = new TiXmlElement("Math");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("aa", 90);
	pSubElem->SetAttribute("bb", 70);
	pSubElem->SetAttribute("cc", 95);

	pElem = new TiXmlElement("class2");
	pRoot->LinkEndChild(pElem);
	pElem0 = new TiXmlElement("Teacher");
	pElem0->LinkEndChild(new TiXmlElement("SSS1"));
	pElem->LinkEndChild(pElem0);

	pSubElem = new TiXmlElement("English");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("ab", 70);
	pSubElem->SetAttribute("vc", 90);
	pSubElem->SetAttribute("ds", 30);

	pSubElem = new TiXmlElement("Math");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("ab", 60);
	pSubElem->SetAttribute("vc", 70);
	pSubElem->SetAttribute("ds", 25);
	pSubElem->SetAttribute("dsz", 25);

	pElem = new TiXmlElement("class3");
	pRoot->LinkEndChild(pElem);
	pElem0 = new TiXmlElement("Teacher");
	pElem0->LinkEndChild(new TiXmlElement("SSS2"));
	pElem->LinkEndChild(pElem0);

	pSubElem = new TiXmlElement("English");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("ab", 70);
	pSubElem->SetAttribute("vc", 90);
	pSubElem->SetAttribute("ds", 30);

	pSubElem = new TiXmlElement("Math");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("ab", 60);
	pSubElem->SetAttribute("vc", 70);
	pSubElem->SetAttribute("ds", 25);
	pSubElem->SetAttribute("dsz", 25);

	pElem = new TiXmlElement("class4");
	pRoot->LinkEndChild(pElem);
	pElem0 = new TiXmlElement("Teacher");
	pElem0->LinkEndChild(new TiXmlElement("SSS3"));
	pElem->LinkEndChild(pElem0);

	pSubElem = new TiXmlElement("English");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("ab", 70);
	pSubElem->SetAttribute("vc", 90);
	pSubElem->SetAttribute("ds", 30);

	pSubElem = new TiXmlElement("Math");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("ab", 60);
	pSubElem->SetAttribute("vc", 70);
	pSubElem->SetAttribute("ds", 25);
	pSubElem->SetAttribute("dsz", 25);

	for (int i = 0; i < 4; i++) {
		TiXmlNode* tmp = pRoot->Parent();
		pElem->RemoveChild(pElem->FirstChild());
		pElem = tmp->FirstChildElement();
	}
	
	doc.SaveFile("Test.xml");
}