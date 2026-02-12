static inline void reply_err(fuse_req_t req, int err)
#endif
{

    fuse_reply_err(req, -err);
}
