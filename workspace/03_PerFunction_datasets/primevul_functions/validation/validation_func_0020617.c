aucmd_restbuf(
    aco_save_T	*aco)
{
    --curbuf->b_nwindows;
    curbuf = aco->save_curbuf;
    curwin->w_buffer = curbuf;
    ++curbuf->b_nwindows;
}
