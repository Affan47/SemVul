init(void* args)
{

	if (!readStandardLists()) {
		return DGCS_ERROR;
	}


	udspath = cv["clamdudsfile"];
	if (udspath.length() < 3) {
		if (!is_daemonised)
			std::cerr << "Error reading clamdudsfile option." << std::endl;
		syslog(LOG_ERR, "Error reading clamdudsfile option.");
		return DGCS_ERROR;


	}


	pathprefix = cv["pathprefix"];

	archivewarn = cv["archivewarn"] == "on";

	return DGCS_OK;
}
