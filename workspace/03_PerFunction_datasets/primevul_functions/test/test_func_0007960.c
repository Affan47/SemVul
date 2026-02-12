ProtoMakeErrorReplyInt(ServiceConnection *conn,
                       int reqSeqno,
                       VGAuthError err,
                       const char *errMsg)
{
   gchar *packet;
   gchar *escapedErrMsg = g_markup_escape_text(errMsg, -1);


   packet = g_strdup_printf(VGAUTH_ERROR_FORMAT,
                            reqSeqno,
                            err,
                            escapedErrMsg);
   g_free(escapedErrMsg);

   Log("Returning error message '%s'\n", packet);

   return packet;
}
