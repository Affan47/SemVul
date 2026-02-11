fs_ptable_check_leaks(fs_ptable *pt, FILE *out)
{
    if (!pt->cons_data) {
        fprintf(out, "ERROR: consistency checks haven't been run\n");

        return 1;
    }

    int leaks = 0;
    for (fs_row_id r = 0; r<pt->header->length; r++) {
        if (pt->cons_data[r] == 0) {
            leaks++;
        }
    }

    if (leaks) {
        fprintf(out, "ERROR: %d rows have leaked\n", leaks);
    }

    return leaks;
}
