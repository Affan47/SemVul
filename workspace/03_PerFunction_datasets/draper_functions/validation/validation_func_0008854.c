match_file_string(char *filename, char *string, char *buffer)
{
	int found;
	char command[BUFSIZE];
	FILE *pipe;


	sprintf(command, "/usr/bin/strings %s", filename);
        if ((pipe = popen(command, "r")) == NULL) {
                error(INFO, "%s: %s\n", filename, strerror(errno));
                return FALSE;
        }

        found = FALSE;
        while (fgets(buffer, BUFSIZE-1, pipe)) {
                if (strstr(buffer, string)) {
                        found = TRUE;
                        break;
                }
        }
        pclose(pipe);

	return found;
}
