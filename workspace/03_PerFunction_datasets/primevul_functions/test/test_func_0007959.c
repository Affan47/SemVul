ServiceProtoCleanupParseState(ServiceConnection *conn)
{

   if (NULL != conn->parseContext) {
      g_markup_parse_context_free(conn->parseContext);
      conn->parseContext = NULL;
   }

   Proto_FreeRequest(conn->curRequest);
   conn->curRequest = NULL;
}
