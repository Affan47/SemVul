unload_dummy_buffer(buf_T *buf, char_u *dirname_start)
{
    if (curbuf != buf)
    {
	close_buffer(NULL, buf, DOBUF_UNLOAD, FALSE, TRUE);


	restore_start_dir(dirname_start);
    }
}
