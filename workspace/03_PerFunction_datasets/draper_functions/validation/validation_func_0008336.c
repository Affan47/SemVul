ra_need_atime_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iovec *vector,
                   int32_t count, struct iatt *stbuf, struct iobref *iobref)
{
        GF_ASSERT (frame);
        STACK_DESTROY (frame->root);
        return 0;
}
