copy_to_output(xlnk_script *s, xlnk_script_command *c, void *arg)
{
    const char *file;
    FILE **fpp;
    FILE *cf;
    unsigned char k;

    fpp = (FILE **)arg;
    if (*fpp == NULL) {
        scripterr(s, c, "no output open");
    }
    else {
        require_arg(s, c, "file", file);
        cf = fopen(file, "rb");
        if (cf == NULL) {
            scripterr(s, c, "could not open `%s' for reading", file);
        }
        else {
            verbose(1, "  copying `%s' to output at position %ld...", file, ftell(*fpp) );
            for (k = fgetc(cf); !feof(cf); k = fgetc(cf) ) {
                fputc(k, *fpp);
            }
            bank_offset += ftell(cf);
            pc += ftell(cf);
            fclose(cf);
            if (bank_offset > bank_size) {
                scripterr(s, c, "bank size (%d) exceeded by %d bytes", bank_size, bank_offset - bank_size);
            }
        }
    }
}
