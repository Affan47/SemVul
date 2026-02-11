outhtml(std::ostream &o, const char *t)
{
	for ( ; *t; t++)
	{
		switch (*t){
		case ' ':
			o << "&nbsp;";
			break;
		case '&':
			o << "&amp;";
			break;
		case '<':
			o << "&lt;";
			break;
		case '>':
			o << "&gt;";
			break;
		default:
			o << (char)*t;
		}
	}
}
