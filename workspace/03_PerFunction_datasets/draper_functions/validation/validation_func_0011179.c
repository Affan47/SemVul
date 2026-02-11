psw_endpath(gx_device_vector * vdev, gx_path_type_t type)
{
    stream *s = vdev->strm;
    const char *star = (type & gx_path_type_even_odd ? "*" : "");
    gx_device_pswrite *const pdev = (gx_device_pswrite *)vdev;

    if (pdev->path_state.num_points > 0 && !pdev->path_state.move)
        stream_puts(s, "p ");
    if (type & gx_path_type_fill) {
        if (type & (gx_path_type_stroke | gx_path_type_clip))
            pprints1(s, "q f%s Q ", star);
        else
            pprints1(s, "f%s\n", star);
    }
    if (type & gx_path_type_stroke) {
        if (type & gx_path_type_clip)
            stream_puts(s, "q S Q ");
        else
            stream_puts(s, "S\n");
    }
    if (type & gx_path_type_clip)
        pprints1(s, "Y%s\n", star);
    if (s->end_status == ERRC)
        return_error(gs_error_ioerror);
    return 0;
}
