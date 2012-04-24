# include "EmptyElement.hpp"
# include <functional>
# include <algorithm>
using namespace std;

namespace xml
{

struct AttributName: public std::binary_function< Attribut, string, bool > {
	// Adaptable binary predicate to find an attribute using its name :
	bool operator () ( const Attribut &att, const string &name ) const {
		return att.first == name;
	}
};

string EmptyElement::endCharacter()
{
	return "/>";
}

string EmptyElement::beginCharacter()
{
	return "<";
}

string EmptyElement::GetAttributeValue(string attributeName)
{
	string value;
	list<Attribut>::iterator attr = attributes.begin();
	attr = find_if( attr, attributes.end(), bind2nd( AttributName(), attributeName ) );
	if (attr != attributes.end()) { value = attr->second; }
	return value;
}

ostream& EmptyElement::toString(ostream& stream, int depth)
{
	printTabs(stream, depth);
	stream << beginCharacter(); 
	if (!name.first.empty())
	{
		stream << name.first << ":";
	}

	stream << name.second;
	for(AttList::iterator it = attributes.begin();
		it != attributes.end();
		++it)
	{
		stream << " " << it->first << "=\"" << it->second << "\"";
	}
	stream << endCharacter(); 
	return stream;
}

}