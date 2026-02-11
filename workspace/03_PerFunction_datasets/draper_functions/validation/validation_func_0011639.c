printcode(buff)
    STR buff; {
    if (strlen(result) + strlen(buff) + 2 > resultsize - 1) {
        resultsize += 1024;
        result = realloc(result, resultsize);
        currbuffer->size = resultsize;
        currbuffer->buffer = result;
    }
    strcat(result, buff);
    currbuffer->lines += countlines(buff);
}
