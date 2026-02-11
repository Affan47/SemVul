openfile(char *filename)
{
    FILE *fp = NULL;
    char *outname;

    outname = NULL;

    fp = _dxfopen_dxfile(filename,NULL,&outname,".cm");
    if (!fp) {
	DXSetError(ERROR_BAD_PARAMETER, "#12240", filename);
	return NULL;
    }
    DXFree(outname);
    return fp;
}
