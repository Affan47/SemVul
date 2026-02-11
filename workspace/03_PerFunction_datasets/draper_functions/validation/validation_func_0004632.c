gs_jpeg_read_scanlines(stream_DCT_state * st,
                       JSAMPARRAY scanlines,
                       int max_lines)
{
    if (setjmp(find_jmp_buf(st->data.common->exit_jmpbuf)))
        return_error(gs_jpeg_log_error(st));
    return (int)jpeg_read_scanlines(&st->data.decompress->dinfo,
                                    scanlines, (JDIMENSION) max_lines);
}
