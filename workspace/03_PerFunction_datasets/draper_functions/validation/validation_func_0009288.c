tiw_add(TermInfosWriter *tiw,
             const char *term,
             int term_len,
             TermInfo *ti)
{
    off_t tis_pos;


    if (0 == (tiw->tis_writer->counter % tiw->index_interval)) {

        tw_add(tiw->tix_writer,
               tiw->tis_writer->last_term,
               strlen(tiw->tis_writer->last_term),
               &(tiw->tis_writer->last_term_info),
               tiw->skip_interval);
        tis_pos = os_pos(tiw->tis_writer->os);
        os_write_voff_t(tiw->tix_writer->os, tis_pos - tiw->last_index_ptr);
        tiw->last_index_ptr = tis_pos;
    }

    tw_add(tiw->tis_writer, term, term_len, ti, tiw->skip_interval);
}
