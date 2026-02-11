indirect_release_tex_image(Display * dpy, GLXDrawable drawable, int buffer)
{
   xGLXVendorPrivateReq *req;
   struct glx_context *gc = __glXGetCurrentContext();
   CARD32 *drawable_ptr;
   INT32 *buffer_ptr;
   CARD8 opcode;

   opcode = __glXSetupForCommand(dpy);
   if (!opcode)
      return;

   LockDisplay(dpy);
   GetReqExtra(GLXVendorPrivate, sizeof(CARD32) + sizeof(INT32), req);
   req->reqType = opcode;
   req->glxCode = X_GLXVendorPrivate;
   req->vendorCode = X_GLXvop_ReleaseTexImageEXT;
   req->contextTag = gc->currentContextTag;

   drawable_ptr = (CARD32 *) (req + 1);
   buffer_ptr = (INT32 *) (drawable_ptr + 1);

   *drawable_ptr = drawable;
   *buffer_ptr = buffer;

   UnlockDisplay(dpy);
   SyncHandle();
}
