DRI2Authenticate(Display * dpy, XID window, drm_magic_t magic)
{
   XExtDisplayInfo *info = DRI2FindDisplay(dpy);
   xDRI2AuthenticateReq *req;
   xDRI2AuthenticateReply rep;

   XextCheckExtension(dpy, info, dri2ExtensionName, False);

   LockDisplay(dpy);
   GetReq(DRI2Authenticate, req);
   req->reqType = info->codes->major_opcode;
   req->dri2ReqType = X_DRI2Authenticate;
   req->window = window;
   req->magic = magic;

   if (!_XReply(dpy, (xReply *) & rep, 0, xFalse)) {
      UnlockDisplay(dpy);
      SyncHandle();
      return False;
   }

   UnlockDisplay(dpy);
   SyncHandle();

   return rep.authenticated;
}
