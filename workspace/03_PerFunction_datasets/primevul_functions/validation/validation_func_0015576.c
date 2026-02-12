HttpStateData::statusIfComplete() const
{
    const HttpReply *rep = virginReply();


    if (httpHeaderHasConnDir(&rep->header, "close"))
        return COMPLETE_NONPERSISTENT_MSG;


    if (!flags.keepalive)
        return COMPLETE_NONPERSISTENT_MSG;


    if (!flags.request_sent) {
        debugs(11, 2, "Request not yet fully sent " << request->method << ' ' << entry->url());
        return COMPLETE_NONPERSISTENT_MSG;
    }


    if (!rep->keep_alive)
        return COMPLETE_NONPERSISTENT_MSG;

    return COMPLETE_PERSISTENT_MSG;
}
