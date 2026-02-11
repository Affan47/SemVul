qfits_query_column(
        const qfits_table   *   th,
        int                     colnum,
        const int           *   selection)
{
    char            *    start;
    qfits_col       *   col;
    int                    field_size;
    unsigned char   *   array;
    unsigned char   *   r;
    unsigned char   *   inbuf;
    int                 table_width;
    int                 nb_rows;
    size_t              size;
    int                 i;

    if (th->tab_w == -1) {

        if ((table_width = qfits_compute_table_width(th)) == -1) {
            qfits_error("cannot compute the table width");
            return NULL;
        }
    } else table_width = th->tab_w;


    nb_rows = 0;
    if (selection == NULL) {
        nb_rows = th->nr;
    } else {
        for (i=0; i<th->nr; i++) if (selection[i] == 1) nb_rows++;
    }


    col = th->col + colnum;


    if (nb_rows * col->atom_size * col->atom_nb == 0) col->readable = 0;


    if (col->readable == 0)  return NULL;


    if ((field_size=qfits_table_get_field_size(th->tab_t,col))==-1) return NULL;


    if ((start=qfits_falloc((char *)(th->filename), 0, &size))==NULL) {
        qfits_error("cannot open table for query [%s]", th->filename);
        return NULL;
    }


    array = qfits_malloc(nb_rows * field_size * sizeof(char));


    r = array;
    inbuf = (unsigned char*)start + col->off_beg;


    if (selection == NULL) {

        for (i=0; i<th->nr; i++) {

            memcpy(r, inbuf, field_size);
            r += field_size;

            inbuf += table_width;
        }
    } else {

        for (i=0; i<th->nr; i++) {
            if (selection[i] == 1) {

                memcpy(r, inbuf, field_size);
                r += field_size;
            }

            inbuf += table_width;
        }
    }
    qfits_fdealloc(start, 0, size);


#ifndef WORDS_BIGENDIAN
    if ((th->tab_t == QFITS_BINTABLE) && (col->atom_size > 1)) {
        r = array;
        for (i=0; i<nb_rows * col->atom_nb; i++) {
            qfits_swap_bytes(r, col->atom_size);
            r += col->atom_size;
        }
    }
#endif


    return array;
}
