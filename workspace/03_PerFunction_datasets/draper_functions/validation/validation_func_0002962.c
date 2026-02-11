_getPrefsPathname(void) const
{

	static UT_String buf;

	if(!buf.empty())
	  return buf.c_str();

	const char * szDirectory = XAP_App::getApp()->getUserPrivateDirectory();
	const char * szFile = "profile";

	buf = szDirectory;
	if (!buf.size() || szDirectory[buf.size()-1] != '/')
	  buf += "/";
	buf += szFile;


	XAP_App::getApp()->migrate("/AbiWord.Profile", szFile, buf.c_str());

	return buf.c_str();
}
