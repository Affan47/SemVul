ConnStateData::swanSong()
{
    debugs(33, 2, HERE << clientConnection);
    checkLogging();

    flags.readMore = false;
    clientdbEstablished(clientConnection->remote, -1);
    pipeline.terminateAll(0);


    unpinConnection(true);

    Server::swanSong();

#if USE_AUTH

    setAuth(NULL, "ConnStateData::SwanSong cleanup");
#endif

    flags.swanSang = true;
}
