GetMfn()
{
	std::string movieFilenamePart;
	extern char curMovieFilename[512];
	if(*curMovieFilename)
		{
		char drv[PATH_MAX], dir[PATH_MAX], name[PATH_MAX], ext[PATH_MAX];
		splitpath(curMovieFilename,drv,dir,name,ext);
		movieFilenamePart = std::string(".") + name;
		}
	return movieFilenamePart;
}
