fop_writev_stub (call_frame_t *frame,
                 fop_writev_t fn,
                 fd_t *fd,
                 struct iovec *vector,
                 int32_t count,
                 off_t off, uint32_t flags,
                 struct iobref *iobref, dict_t *xdata)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);
        GF_VALIDATE_OR_GOTO ("call-stub", vector, out);

        stub = stub_new (frame, 1, GF_FOP_WRITE);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->args.writev.fn = fn;
        if (fd)
                stub->args.writev.fd = fd_ref (fd);
        stub->args.writev.vector = iov_dup (vector, count);
        stub->args.writev.count  = count;
        stub->args.writev.off    = off;
        stub->args.writev.flags  = flags;
        stub->args.writev.iobref = iobref_ref (iobref);
        if (xdata)
                stub->xdata = dict_ref (xdata);

out:
        return stub;
}
