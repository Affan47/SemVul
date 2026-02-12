ConnStateData::sendControlMsg(HttpControlMsg msg)
{
    if (!isOpen()) {
        debugs(33, 3, HERE << "ignoring 1xx due to earlier closure");
        return;
    }


    if (!pipeline.empty()) {
        HttpReply::Pointer rep(msg.reply);
        Must(rep);

        cbControlMsgSent = msg.cbSuccess;

        typedef CommCbMemFunT<HttpControlMsgSink, CommIoCbParams> Dialer;
        AsyncCall::Pointer call = JobCallback(33, 5, Dialer, this, HttpControlMsgSink::wroteControlMsg);

        if (!writeControlMsgAndCall(rep.getRaw(), call)) {

            doneWithControlMsg();
        }
        return;
    }

    debugs(33, 3, HERE << " closing due to missing context for 1xx");
    clientConnection->close();
}
