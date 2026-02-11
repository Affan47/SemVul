gen_keys(DArray *keys, int num_keys)
{
    int i = 0;
    FILE *urand = fopen("/dev/urandom", "r");
    check(urand != NULL, "Failed to open /dev/urandom");

    struct bStream *stream = bsopen((bNread)fread, urand);
    check(stream != NULL, "Failed to open /dev/urandom");

    bstring key = bfromcstr("");
    int rc = 0;


    for(i = 0; i < num_keys; i++) {
        rc = bsread(key, stream, BUFFER_LEN);
        check(rc >= 0, "Failed to read from /dev/urandom.");

        DArray_push(keys, bstrcpy(key));
    }

    bsclose(stream);
    fclose(urand);
    return 0;

error:
    return -1;
}
