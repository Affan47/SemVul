lame_get_id3v1_tag(lame_global_flags * gfp, unsigned char *buffer, size_t size)
{
    size_t const tag_size = 128;
    lame_internal_flags *gfc;

    if (gfp == 0) {
        return 0;
    }
    if (size < tag_size) {
        return tag_size;
    }
    gfc = gfp->internal_flags;
    if (gfc == 0) {
        return 0;
    }
    if (buffer == 0) {
        return 0;
    }
    if (test_tag_spec_flags(gfc, V2_ONLY_FLAG)) {
        return 0;
    }
    if (test_tag_spec_flags(gfc, CHANGED_FLAG)) {
        unsigned char *p = buffer;
        int     pad = test_tag_spec_flags(gfc, SPACE_V1_FLAG) ? ' ' : 0;
        char    year[5];


        *p++ = 'T';
        *p++ = 'A';
        *p++ = 'G';

        p = set_text_field(p, gfc->tag_spec.title, 30, pad);
        p = set_text_field(p, gfc->tag_spec.artist, 30, pad);
        p = set_text_field(p, gfc->tag_spec.album, 30, pad);
        sprintf(year, "%d", gfc->tag_spec.year);
        p = set_text_field(p, gfc->tag_spec.year ? year : NULL, 4, pad);

        p = set_text_field(p, gfc->tag_spec.comment, gfc->tag_spec.track_id3v1 ? 28 : 30, pad);
        if (gfc->tag_spec.track_id3v1) {

            *p++ = 0;
            *p++ = gfc->tag_spec.track_id3v1;
        }
        *p++ = gfc->tag_spec.genre_id3v1;
        return tag_size;
    }
    return 0;
}
