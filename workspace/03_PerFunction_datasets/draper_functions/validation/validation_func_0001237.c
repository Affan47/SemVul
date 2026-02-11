avbin_open_stream(AVbinFile *file, int index)
{
    AVCodecContext *codec_context;
    AVCodec *codec;

    if (index < 0 || index >= file->context->nb_streams)
        return NULL;

    codec_context = file->context->streams[index]->codec;
    codec = avcodec_find_decoder(codec_context->codec_id);
    if (!codec)
        return NULL;

    if (avcodec_open2(codec_context, codec, NULL) < 0)
        return NULL;

    AVbinStream *stream = malloc(sizeof *stream);
    stream->format_context = file->context;
    stream->codec_context = codec_context;
    stream->type = codec_context->codec_type;
    if (stream->type == AVMEDIA_TYPE_VIDEO)
        stream->frame = avcodec_alloc_frame();
    else
        stream->frame = NULL;
    return stream;
}
