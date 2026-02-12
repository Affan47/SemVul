EXPORTED int annotatemore_msg_lookupmask(const char *mboxname, uint32_t uid, const char *entry,
                                         const char *userid, struct buf *value)
{
    int r = 0;
    value->len = 0;

    init_internal();


    if (!mboxname_userownsmailbox(userid, mboxname))
        r = annotatemore_msg_lookup(mboxname, uid, entry, userid, value);

    if (value->len == 0)
        r = annotatemore_msg_lookup(mboxname, uid, entry, "", value);

    if (value->len == 0)
        r = annotatemore_msg_lookup(mboxname, uid, entry, NULL, value);
    return r;
}
