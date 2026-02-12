int pdf_is_pdf(FILE *fp)
{
    char *header;
    if (!(header = get_header(fp)))
      return 0;


    const char *c = strstr(header, "%PDF-");
    const int is_pdf = c && ((c - header+strlen("%PDF-M.m")) < 1024);
    free(header);
    return is_pdf;
}
