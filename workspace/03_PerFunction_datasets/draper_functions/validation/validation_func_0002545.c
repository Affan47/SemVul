getHelp(int columns) const
{
	stringstream str;
	int cols = this->getTermColumns();

	str << "Usage: " << this->projectName << " " << this->argUsage << endl;
	str << this->projectName << " -- " << this->projectDescr << endl << endl;


	for (svutArgpOptionMap::const_iterator it = options.begin() ; it != options.end() ; ++it)
		if (it->first != '?' && it->first != SVUT_USAGE_KEY)
			str << formatArgumentHelp(it->second,cols) << endl;


	str << formatArgumentHelp(options.find('?')->second,cols) << endl;
	str << formatArgumentHelp(options.find(SVUT_USAGE_KEY)->second,cols) << endl;

	str << endl;
	str << "Mandatory or optional arguments to long options are also mandatory or optional" << endl;
	str << "for any corresponding short options." << endl;

	return str.str();
}
