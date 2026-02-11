operator<<(std::ostream& out, const UnitTestMockResultFormater& formater)
{
	for (std::list<std::string>::const_iterator it = formater.event.begin() ; it != formater.event.end() ; ++it)
		out << *it << "; ";
	return out;
}
