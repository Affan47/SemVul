readConfig(const fxStr& filename)
{
    FILE* fd = Sys::fopen(tildeExpand(filename), "r");
    if (fd) {
	configTrace(NLS::TEXT("Read config file %s"), (const char*) filename);
	char line[1024];
	while (fgets(line, sizeof (line)-1, fd)){
	    line[strlen(line)-1]='\0';
	    (void) readConfigItem(line);
	}
	fclose(fd);
    }
}
