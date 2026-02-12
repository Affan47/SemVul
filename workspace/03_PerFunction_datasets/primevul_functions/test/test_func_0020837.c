EXPORTED int annotatemore_lookup(const char *mboxname, const char *entry,
                                 const char *userid, struct buf *value)
{
    return annotatemore_msg_lookup(mboxname, 0, entry, userid, value);
}
