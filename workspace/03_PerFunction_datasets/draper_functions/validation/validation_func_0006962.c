s_DCTE_release(stream_state * st)
{
    stream_DCT_state *const ss = (stream_DCT_state *) st;

    gs_jpeg_destroy(ss);
    if (ss->data.common)
        gs_free_object(ss->data.common->memory, ss->data.compress,
                       "s_DCTE_release");

    st->templat = &s_DCTE_template;
}
