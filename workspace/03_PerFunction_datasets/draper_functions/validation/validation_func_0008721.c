fs_rtp_session_get_codecs_need_resend (FsSession *session,
    GList *old_codecs, GList *new_codecs)
{
  g_return_val_if_fail (FS_IS_RTP_SESSION (session), FALSE);

  return codecs_list_has_codec_config_changed (old_codecs, new_codecs);
}
