static int MP4_ReadBox_drms( stream_t *p_stream, MP4_Box_t *p_box )
{
    VLC_UNUSED(p_box);


    msg_Warn( p_stream, "DRM protected streams are not supported." );
    return 1;
}
