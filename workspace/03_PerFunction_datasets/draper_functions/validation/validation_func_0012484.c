error_where(path, line, text)
char   *path;
int     line;
char   *text;
{
    errcount++;


    if (line && path[0])
	fprintf(stderr, "%s, line %d: ", path, line);

    fprintf(stderr, "%s\n", text);
}
