ConnStateData::whenClientIpKnown()
{
    if (Config.onoff.log_fqdn)
        fqdncache_gethostbyaddr(clientConnection->remote, FQDN_LOOKUP_IF_MISS);

#if USE_IDENT
    if (Ident::TheConfig.identLookup) {
        ACLFilledChecklist identChecklist(Ident::TheConfig.identLookup, NULL, NULL);
        identChecklist.src_addr = clientConnection->remote;
        identChecklist.my_addr = clientConnection->local;
        if (identChecklist.fastCheck().allowed())
            Ident::Start(clientConnection, clientIdentDone, this);
    }
#endif

    clientdbEstablished(clientConnection->remote, 1);

#if USE_DELAY_POOLS
    fd_table[clientConnection->fd].clientInfo = NULL;

    if (!Config.onoff.client_db)
        return;

    ClientDelayPools& pools(Config.ClientDelay.pools);
    if (pools.size()) {
        ACLFilledChecklist ch(NULL, NULL, NULL);


        ch.src_addr = clientConnection->remote;
        ch.my_addr = clientConnection->local;

        for (unsigned int pool = 0; pool < pools.size(); ++pool) {


            if (pools[pool].access) {
                ch.changeAcl(pools[pool].access);
                allow_t answer = ch.fastCheck();
                if (answer.allowed()) {


                    ClientInfo * cli = clientdbGetInfo(clientConnection->remote);
                    assert(cli);


                    fd_table[clientConnection->fd].clientInfo = cli;


                    const double burst = floor(0.5 +
                                               (pools[pool].highwatermark * Config.ClientDelay.initial)/100.0);
                    cli->setWriteLimiter(pools[pool].rate, burst, pools[pool].highwatermark);
                    break;
                } else {
                    debugs(83, 4, HERE << "Delay pool " << pool << " skipped because ACL " << answer);
                }
            }
        }
    }
#endif


}
