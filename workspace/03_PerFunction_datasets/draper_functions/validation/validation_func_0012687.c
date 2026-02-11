scanQueueDirectory()
{
    DIR* dir = Sys::opendir(sendDir);
    if (dir == NULL) {
	logError("Could not scan %s directory for outbound jobs",
		(const char*)sendDir);
	return;
    }
    for (dirent* dp = readdir(dir); dp; dp = readdir(dir)) {
	if (dp->d_name[0] == 'q')
	    submitJob(&dp->d_name[1], true);
    }
    closedir(dir);
}
