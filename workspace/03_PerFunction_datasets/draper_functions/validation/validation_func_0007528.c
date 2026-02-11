handle_send(char *params)
{

    if(params == NULL) {
        return -1;
    }

    char *message = (char *)malloc((strlen(params) + 2) * sizeof(char));
    strcat(strcpy(message, params), "\n");

    if(fprintf(writePipe, message) < 0 || fflush(writePipe) != 0) {
        return -1;
    }

    free(message);
    return 3;
}
