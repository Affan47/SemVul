free_ogg_codecs (ogg_state_t *ogg_info)
{
    ogg_codec_t *codec;

    if (ogg_info == NULL)
        return;

    format_ogg_free_headers (ogg_info);


    codec = ogg_info->codecs;
    DEBUG0 ("freeing codecs");
    while (codec)
    {
        ogg_codec_t *next = codec->next;
        if (codec->possible_start)
            refbuf_release (codec->possible_start);
        codec->codec_free (ogg_info, codec);
        codec = next;
    }
    ogg_info->codecs = NULL;
    ogg_info->current = NULL;
    ogg_info->bos_completed = 0;
    ogg_info->codec_count = 0;
}
