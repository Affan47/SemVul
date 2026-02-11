set_myname(const char * name)
{
	if (name) {
		myname = name;
	} else {
		myname = PROGNAME + std::string(" ") + VERSION;
	}
}
