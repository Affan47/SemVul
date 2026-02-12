Proto_SecurityCheckRequest(ServiceConnection *conn,
                           ProtoRequest *req)
{
   VGAuthError err;
   gboolean isSecure = ServiceNetworkIsConnectionPrivateSuperUser(conn);

   if (conn->isPublic && req->reqType != PROTO_REQUEST_SESSION_REQ) {
      return VGAUTH_E_PERMISSION_DENIED;
   }

   switch (req->reqType) {


   case PROTO_REQUEST_SESSION_REQ:
      err = VGAUTH_E_OK;
      break;


   case PROTO_REQUEST_CONN:
   case PROTO_REQUEST_QUERYMAPPEDALIASES:
      err = VGAUTH_E_OK;
      break;


   case PROTO_REQUEST_ADDALIAS:
   case PROTO_REQUEST_REMOVEALIAS:
   case PROTO_REQUEST_QUERYALIASES:
   case PROTO_REQUEST_CREATETICKET:
      if (isSecure) {
         err = VGAUTH_E_OK;
      } else {
         const gchar *connOwner = conn->userName;
         const gchar *reqUser = NULL;

         if (req->reqType == PROTO_REQUEST_ADDALIAS) {
            reqUser = req->reqData.addAlias.userName;
         } else if (req->reqType == PROTO_REQUEST_REMOVEALIAS) {
            reqUser = req->reqData.removeAlias.userName;
         } else if (req->reqType == PROTO_REQUEST_QUERYALIASES) {
            reqUser = req->reqData.queryAliases.userName;
         } else if (req->reqType == PROTO_REQUEST_CREATETICKET) {
            reqUser = req->reqData.createTicket.userName;
         } else {
            ASSERT(0);
         }

         if (Usercheck_CompareByName(connOwner, reqUser)) {
            err = VGAUTH_E_OK;
         } else {
            Audit_Event(FALSE,
                        SU_(proto.attack, "Possible security attack!  Request type %d has a "
                        "userName (%s) which doesn't match the pipe owner (%s)!"),
                        req->reqType, reqUser, connOwner);
            Warning("%s: Possible security attack!  Request type %d has a "
                    "userName (%s) which doesn't match the pipe owner (%s)!\n",
                    __FUNCTION__, req->reqType, reqUser, connOwner);
            err = VGAUTH_E_PERMISSION_DENIED;
         }
      }
      break;


   case PROTO_REQUEST_VALIDATETICKET:
      err = (isSecure) ? VGAUTH_E_OK : VGAUTH_E_PERMISSION_DENIED;
      break;
   case PROTO_REQUEST_VALIDATE_SAML_BEARER_TOKEN:


      err = VGAUTH_E_OK;
      break;
   case PROTO_REQUEST_REVOKETICKET:


      err = VGAUTH_E_OK;
      break;
   default:
      Warning("%s: Unrecognized request type '%d'\n",
              __FUNCTION__, req->reqType);
      err = VGAUTH_E_PERMISSION_DENIED;
      break;
   }

   return err;
}
