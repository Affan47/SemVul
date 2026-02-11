eprintf_program_ident(const char *program_name,
                      long revision_number)
{
    if (program_name) {
        epf((revision_number ? "%s " : "%s"), program_name);
        if (revision_number) {
            int fpart = revision_number % 100;

            epf("%d.%02d", (int)(revision_number / 100), fpart);
        }
        epf(": ");
    }
}
