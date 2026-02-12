aucmd_prepbuf(
    aco_save_T	*aco,
    buf_T	*buf)
{
    aco->save_curbuf = curbuf;
    --curbuf->b_nwindows;
    curbuf = buf;
    curwin->w_buffer = buf;
    ++curbuf->b_nwindows;
}
