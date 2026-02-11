hawki_bkg_frames_buffer_init
(const cpl_frameset * fset)
{
    int i_ima;
    hawki_bkg_frames_buffer * frames_buffer;

    frames_buffer =
          (hawki_bkg_frames_buffer *)cpl_malloc(sizeof(hawki_bkg_frames_buffer));

    frames_buffer->nframes = cpl_frameset_get_size(fset);
    frames_buffer->images  =
           (cpl_image **)cpl_malloc(frames_buffer->nframes *
                                        sizeof(cpl_image *));
    frames_buffer->medians =
            (double *)cpl_malloc(frames_buffer->nframes *
                                        sizeof(double));
    frames_buffer->frames  = cpl_frameset_duplicate(fset);

    for(i_ima=0; i_ima< frames_buffer->nframes; i_ima++)
        frames_buffer->images[i_ima] = NULL;

    return frames_buffer;
}
