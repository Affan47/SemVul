rfbBool PermitServerInput(rfbClient* client, int enabled)
{
    rfbSetServerInputMsg msg;

    if (!SupportsClient2Server(client, rfbSetServerInput)) return TRUE;

    msg.type = rfbSetServerInput;
    msg.status = (enabled ? 1 : 0);
    msg.pad = 0;
    return  (WriteToRFBServer(client, (char *)&msg, sz_rfbSetServerInputMsg) ? TRUE : FALSE);
}
