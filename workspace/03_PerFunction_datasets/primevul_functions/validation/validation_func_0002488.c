bool CClient::OnPingMessage(CMessage& Message) {


    if (!Message.GetParams().empty())
        PutClient(":irc.znc.in PONG irc.znc.in " + Message.GetParamsColon(0));
    else
        PutClient(":irc.znc.in PONG irc.znc.in");
    return false;
}
