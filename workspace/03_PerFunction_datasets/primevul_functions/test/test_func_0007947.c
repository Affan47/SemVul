ServiceProtoHandleConnection(ServiceConnection *conn,
                             ProtoRequest *req)
{
   VGAuthError err = VGAUTH_E_OK;
   VGAuthError err2;
   gchar *packet;
   char *event = NULL;

#ifdef _WIN32
   err = ServiceStartVerifyPid(conn, req->reqData.connect.pid, &event);
#endif

   if (err != VGAUTH_E_OK) {


      packet = Proto_MakeErrorReply(conn, req, err, "connect failed");
   } else {


      packet = g_markup_printf_escaped(VGAUTH_CONNECT_REPLY_FORMAT,
                                       req->sequenceNumber,
                                       event ? event : "");
   }

   err2 = ServiceNetworkWriteData(conn, strlen(packet), packet);
   if (err2 != VGAUTH_E_OK) {
      Warning("%s: failed to send Connect reply\n", __FUNCTION__);
      if (err == VGAUTH_E_OK) {
         err = err2;
      }
   }
   g_free(packet);
   g_free(event);

   return err;
}
