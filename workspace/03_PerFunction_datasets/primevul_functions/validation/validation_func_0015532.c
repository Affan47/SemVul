HttpStateData::handle1xx(HttpReply *reply)
{
    HttpReply::Pointer msg(reply);


    Must(!flags.handling1xx);
    flags.handling1xx = true;

    if (!request->canHandle1xx() || request->forcedBodyContinuation) {
        debugs(11, 2, "ignoring 1xx because it is " << (request->forcedBodyContinuation ? "already sent" : "not supported by client"));
        proceedAfter1xx();
        return;
    }

#if USE_HTTP_VIOLATIONS

    if (Config.accessList.reply) {
        ACLFilledChecklist ch(Config.accessList.reply, originalRequest(), NULL);
        ch.al = fwd->al;
        ch.reply = reply;
        ch.syncAle(originalRequest(), nullptr);
        HTTPMSGLOCK(ch.reply);
        if (!ch.fastCheck().allowed()) {
            debugs(11, 3, HERE << "ignoring denied 1xx");
            proceedAfter1xx();
            return;
        }
    }
#endif

    debugs(11, 2, HERE << "forwarding 1xx to client");


    typedef NullaryMemFunT<HttpStateData> CbDialer;
    const AsyncCall::Pointer cb = JobCallback(11, 3, CbDialer, this,
                                  HttpStateData::proceedAfter1xx);
    CallJobHere1(11, 4, request->clientConnectionManager, ConnStateData,
                 ConnStateData::sendControlMsg, HttpControlMsg(msg, cb));


}
