main(int    argc,
     char **argv)
{
char           *dirin, *substr, *fileout;
l_int32         res;
static char     mainName[] = "convertfilestops";

    if (argc != 5)
	exit(ERROR_INT(" Syntax:  convertfilestops dirin substr res fileout",
                       mainName, 1));

    dirin = argv[1];
    substr = argv[2];
    res = atoi(argv[3]);
    fileout = argv[4];
    if (!strcmp(substr, "allfiles"))
        substr = NULL;
    if (res != 0)
        return convertFilesToPS(dirin, substr, res, fileout);
    else
        return convertFilesFittedToPS(dirin, substr, 0.0, 0.0, fileout);
}
