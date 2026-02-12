HttpStateData::peerSupportsConnectionPinning() const
{
    if (!_peer)
        return true;


    if (!_peer->connection_auth)
        return false;

    const HttpReply *rep = entry->mem_obj->getReply();


    if (rep->sline.status() != Http::scUnauthorized)
        return true;


    if (_peer->connection_auth == 1)
        return true;


    if (_peer->options.originserver)
        return true;


    if (request->flags.pinned)
        return true;


    if (rep->header.hasListMember(Http::HdrType::PROXY_SUPPORT, "Session-Based-Authentication", ','))
        return true;

    return false;
}
