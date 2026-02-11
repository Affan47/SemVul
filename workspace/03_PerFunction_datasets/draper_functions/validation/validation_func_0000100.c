AddProperties(const xmlpp::SaxParser::AttributeList& attrs)
{
	for (xmlpp::SaxParser::AttributeList::const_iterator iter = attrs.begin(); iter != attrs.end(); ++iter) {
		std::string attribut(iter->name);
		std::string value(iter->value);

		AddProperties(attribut, value);
	}
}
