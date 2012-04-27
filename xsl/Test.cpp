

/**
 * @file Test.hpp
 * @brief Tests - XSL
 * 
 * Contains the test functions for the XSL processor and HTML generator.
 * 
 * @author Benjamin PLANCHE
 */

# include <iostream>

using namespace std;

#include "XSLProcessor.hpp"
#include "../xml/xml_processor.h"
#include "../dtd/dtd.h"

# include "../tests/TestFramework.hpp"

struct XSLProcessTest_NoXSLDTD : public TestCase
{
	XSLProcessTest_NoXSLDTD() : TestCase("<fr> Vérifier que le traitement s'arrête en l'absence de DTD XSL") {}
	bool operator()()
	{
		try{
			xml::Document* document = NULL;
			document = parseXML("testSimple.xsl");
			xsl::XSLProcessor xslProcessor = xsl::XSLProcessor();
			xslProcessor.processXslFile(document);
		}catch(string s){
			if( s == xsl::XSLProcessor::ERROR_NO_DTD){
				return true;
			}else{
				return false;
			}
		}
		
		return false;
	}
};

struct XSLProcessTest_NoHTMLDTD : public TestCase
{
	XSLProcessTest_NoHTMLDTD() : TestCase("<fr> Vérifier que le traitement s'arrête en l'absence de DTD HTML") {}
	bool operator()()
	{
		try{
			xml::Document* document = NULL;
			document = parseXML("rapportNoHTMLDTD.xsl");
			xsl::XSLProcessor xslProcessor = xsl::XSLProcessor();
			xslProcessor.processXslFile(document);
		}catch(string s){
			if( s == xsl::XSLProcessor::ERROR_NO_STYLESHEET){
				return true;
			}else{
				return false;
			}
		}
		
		return false;
	}
};

struct XSLProcessTest_InvalidHTMLDTD : public TestCase
{
	XSLProcessTest_InvalidHTMLDTD () : TestCase("<fr> Vérifier que le traitement s'arrête si la DTD HTML est invalide") {}
	bool operator()()
	{
		xml::Document* docXml;
		dtd::Document* docDtd;
		xsl::XSLProcessor proc = xsl::XSLProcessor();
		
		docXml = parseXML("tests/rapport.xsl");
		docDtd = parseDTD("tests/invalid_html.dtd");
		
		try {
			proc.setXslDTD(docDtd);
			proc.processXslFile(docXml);
		} catch(std::string s) {
			if(s == xsl::XSLProcessor::ERROR_INVALID_HTML_DTD)
				return true;
		}
		
		return false;
	}
};

struct XSLProcessTest_InvalidXSL : public TestCase
{
	XSLProcessTest_InvalidXSL() : TestCase("<fr> Vérifier que le traitement s'arrête si le XSL est invalide") {}
	bool operator()()
	{
		try{
			xml::Document* documentXSL = NULL;
			document = parseXML("rapportInvalidXSL.xsl");
			xml::Document* documentDTD = NULL;
			document = parseXML("xsl.dtd");
			xml::XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(documentDTD);
			xslProcessor.processXslFile(documentXSL);
			xslProcessor = ~xml::XSLProcessor();
		}catch(string s){
			if( s == XSLProcessor::ERROR_INVALID_HTML_DTD ){
				return true;
			}
		}
		return false;
	}
};



struct XSLProcessTest_InvalidSemanticXSL : public TestCase
{
	XSLProcessTest_InvalidSemanticXSL() : TestCase("<fr> Vérifier que le traitement s'arrête si le XSL est invalide") {}
	bool operator()()
	{
		try{
			xml::Document* documentXSL = NULL;
			document = parseXML("rapportSemanticXSL.xsl");
			xml::Document* documentDTD = NULL;
			document = parseXML("xsl.dtd");
			xml::XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(documentDTD);
			xslProcessor.processXslFile(documentXSL);
			xslProcessor = ~xml::XSLProcessor();
		}catch(string s){
			if( s == XSLProcessor::ERROR_INVALID_XSL ){
				return true;
			}
		}
		return false;
	}
};

struct XSLProcessTest_InvalidHTML : public TestCase
{
	XSLProcessTest_InvalidHTML() : TestCase("<fr> Vérifier que le traitement s'arrête si le HTML est invalide") {}
	bool operator()()
	{
		try{
			xml::Document* documentXSL = NULL;
			document = parseXML("rapportSemanticHTML.xsl");
			xml::Document* documentDTD = NULL;
			document = parseXML("xsl.dtd");
			xml::XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(documentDTD);
			xslProcessor.processXslFile(documentXSL);
			xslProcessor = ~xml::XSLProcessor();
		}catch(string s){
			if( s == XSLProcessor::ERROR_INVALID_XSL_SEMANTIC ){
				return true;
			}
		}
		return false;
	}
};

struct XSLProcessTest_OK : public TestCase
{
	XSLProcessTest_OK() : TestCase("<fr> Vérifier que la structure XSL générée correspond au document donné") {}
	bool operator()()
	{
		xml::Document* docXml;
		dtd::Document* docDtd;
		xsl::XSLProcessor proc;
		
		docXml = parseXML("tests/rapport.xsl");
		docDtd = parseDTD("tests/html.dtd");
		
		try {
			proc.setXslDTD(docDtd);
			proc.processXslFile(docXml);
		} catch(string s) {
			return false
		}
		
		delete docXml;
		delete docDtd;
		
		return true;
	}
};

struct HTMLGenerationTest_NoXSL : public TestCase
{
	HTMLGenerationTest_NoXSL() : TestCase("<fr> Vérifier que la génération HTML s'arrête en l'absence de XSL") {}
	bool operator()()
	{
		try{
			xml::Document* documentXML = NULL;
			document = parseXML("undefined.xml");
			xsl::XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			if( s == XSLProcessor::ERROR_NO_XSL ){
				delete document;
				return true;
			}
		}
		delete document;
		return false;
	}
};

struct HTMLGenerationTest_Simple : public TestCase
{
	HTMLGenerationTest_Simple() : TestCase("<fr> Vérifier le HTML généré, avec des documents XSL et XML simples") {}
	bool operator()()
	{
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		try{
			documentXSL = parseXSL("testSimple.xsl");
			documentXML = parseXML("testSimple.xml");
			xsl::XSLProcessor xslProcessor = XSLProcessor();
			xml::Document* documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << documentHTML << endl;
		delete documentXSL;
		delete documentXML;
		delete documentHTML;
		return true;
	}
};

struct HTMLGenerationTest_ApplyTemplates : public TestCase
{
	HTMLGenerationTest_ApplyTemplates() : TestCase("<fr> Vérifier le HTML généré, avec un XSL contenant des noeuds apply-templates") {}
	bool operator()()
	{
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		try{
			documentXSL = parseXSL("testApplyTemplates.xsl");
			documentXML = parseXML("testSimple.xml");
			xsl::XSLProcessor xslProcessor = XSLProcessor();
			xml::Document* documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << documentHTML << endl;
		delete documentXSL;
		delete documentXML;
		delete documentHTML;
		return true;
	}
};

struct HTMLGenerationTest_Attribute : public TestCase
{
	HTMLGenerationTest_Attribute() : TestCase("<fr> Vérifier le HTML généré, avec un XSL contenant des noeuds attributes") {}
	bool operator()()
	{
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		try{
			documentXSL = parseXSL("testAttribute.xsl");
			documentXML = parseXML("testSimple.xml");
			xsl::XSLProcessor xslProcessor = XSLProcessor();
			xml::Document* documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << documentHTML << endl;
		delete documentXSL;
		delete documentXML;
		delete documentHTML;
		return true;
	}
};

struct HTMLGenerationTest_Complex : public TestCase
{
	HTMLGenerationTest_Complex() : TestCase("<fr> Vérifier le HTML généré, avec des documents XSL et XML plus complexes") {}
	bool operator()()
	{
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		try{
			documentXSL = parseXSL("testComplex.xsl");
			documentXML = parseXML("testComplex.xml");
			XSLProcessor xslProcessor = XSLProcessor();
			xml::Document* documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << documentHTML << endl;
		delete documentXSL;
		delete documentXML;
		delete documentHTML;
		return true;
	}
};


struct HTMLGenerationTest_NoRoot : public TestCase
{
	HTMLGenerationTest_NoRoot() : TestCase("<fr> Vérifier le HTML généré, avec un XSL n'ayant pas de template pour la racine XML") {}
	bool operator()()
	{
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		try{
			
			documentXSL = parseXSL("testNoRoot.xsl");
			documentXML = parseXML("testComplex.xml");
			XSLProcessor xslProcessor = XSLProcessor();
			xml::Document* documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// On test si root == "null"
		if( !(dynamic_cast<xml::Element*>(documentHTML->getRoot()) == "null") ){
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << documentHTML << endl;
		delete documentXSL;
		delete documentXML;
		delete documentHTML;
		return true;
	}
};

int main(int argc, char** argv)
{
	//~ TestSuite suite;
	
	//~ suite.add(new XSLProcessTest_NoXSLDTD);

	//~ suite.add(new XSLProcessTest_NoHTMLDTD);

	//~ suite.add(new XSLProcessTest_InvalidHTMLDTD);

	//~ suite.add(new XSLProcessTest_InvalidXSL);

	//~ suite.add(new XSLProcessTest_InvalidHTML);

	//~ suite.add(new XSLProcessTest_OK);

	//~ suite.add(new HTMLGenerationTest_NoXSL);

	//~ suite.add(new HTMLGenerationTest_Simple);

	//~ suite.add(new HTMLGenerationTest_Complex);

	//~ suite.add(new HTMLGenerationTest_ApplyTemplates);

	//~ suite.add(new HTMLGenerationTest_Attribute);

	//~ suite.add(new HTMLGenerationTest_NoRoot);
	
	//~ suite.launch();
	
	xsl::XSLProcessor proc = xsl::XSLProcessor();
	dtd::Document* dtdXSL = parseDTD("./tests/xsl.dtd");
	proc.setXslDTD(dtdXSL);
	xml::Document* document = parseXML("rapportNoHTMLDTD.xsl");
	proc.processXslFile(document);
	
}



