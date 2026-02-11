xmlFileWrite (void * context, const char * buffer, int len) {
    int items;

    if ((context == NULL) || (buffer == NULL))
        return(-1);
    items = fwrite(&buffer[0], len, 1, (FILE *) context);
    if ((items == 0) && (ferror((FILE *) context))) {
        xmlIOErr(0, "fwrite()");
        return(-1);
    }
    return(items * len);
}
