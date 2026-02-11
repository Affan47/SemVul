main(int argc, char *argv[])
{
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, stdin)) != -1) {
        char* mystr = (char*)calloc(read + 1,sizeof(char));
        decode_html_entities_utf8(mystr, line);
        cout << mystr;
    }
    if (line)
        free(line);
    return EXIT_SUCCESS;
}
