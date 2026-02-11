PyMarshal_ReadLastObjectFromFile(FILE *fp)
{

#define REASONABLE_FILE_LIMIT (1L << 18)
#ifdef HAVE_FSTAT
    off_t filesize;
    filesize = getfilesize(fp);
    if (filesize > 0 && filesize <= REASONABLE_FILE_LIMIT) {
        char* pBuf = (char *)PyMem_MALLOC(filesize);
        if (pBuf != NULL) {
            PyObject* v;
            size_t n;


            n = fread(pBuf, 1, (int)filesize, fp);
            v = PyMarshal_ReadObjectFromString(pBuf, n);
            PyMem_FREE(pBuf);
            return v;
        }

    }
#endif


    return PyMarshal_ReadObjectFromFile(fp);

#undef REASONABLE_FILE_LIMIT
}
