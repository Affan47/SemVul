parse_file(FILE *f, struct parse_state *state,
                            char **ret_modspec)
{
#define BUF_SIZE        2048
    char *bptr;
    errcode_t retval;

    bptr = malloc (BUF_SIZE);
    if (!bptr)
        return ENOMEM;

    while (!feof(f)) {
        if (fgets(bptr, BUF_SIZE, f) == NULL)
            break;
#ifndef PROFILE_SUPPORTS_FOREIGN_NEWLINES
        retval = parse_line(bptr, state, ret_modspec);
        if (retval) {
            free (bptr);
            return retval;
        }
#else
        {
            char *p, *end;

            if (strlen(bptr) >= BUF_SIZE - 1) {


                long offset;
                char *c = bptr + strlen (bptr);
                for (offset = 0; offset > -BUF_SIZE; offset--) {
                    if (*c == '\r' || *c == '\n') {
                        *c = '\0';
                        fseek (f, offset, SEEK_CUR);
                        break;
                    }
                    c--;
                }
            }


            for (p = bptr; *p != '\0'; p++) {
                if (*p == '\r')
                    *p = '\n';
            }

            p = bptr;
            end = bptr + strlen (bptr);
            while (p < end) {
                char* newline;
                char* newp;

                newline = strchr (p, '\n');
                if (newline != NULL)
                    *newline = '\0';


                newp = p + strlen (p) + 1;
                retval = parse_line (p, state, ret_modspec);
                if (retval) {
                    free (bptr);
                    return retval;
                }

                p = newp;
            }
        }
#endif
    }

    free (bptr);
    return 0;
}
