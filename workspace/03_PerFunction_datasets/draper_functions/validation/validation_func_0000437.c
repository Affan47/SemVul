_Xi18nPreeditDoneCallback (XIMS ims, IMProtocol *call_data)
{
    Xi18n i18n_core = ims->protocol;
    FrameMgr fm;
    extern XimFrameRec preedit_done_fr[];
    register int total_size;
    unsigned char *reply = NULL;
    IMPreeditCBStruct *preedit_CB =
        (IMPreeditCBStruct *) &call_data->preedit_callback;
    CARD16 connect_id = call_data->any.connect_id;

    fm = FrameMgrInit (preedit_done_fr,
                       NULL,
                       _Xi18nNeedSwap (i18n_core, connect_id));

    total_size = FrameMgrGetTotalSize (fm);
    reply = (unsigned char *) malloc (total_size);
    if (!reply)
    {
        _Xi18nSendMessage (ims, connect_id, XIM_ERROR, 0, 0, 0);
        return False;
    }

    memset (reply, 0, total_size);
    FrameMgrSetBuffer (fm, reply);

    FrameMgrPutToken (fm, connect_id);
    FrameMgrPutToken (fm, preedit_CB->icid);

    _Xi18nSendMessage (ims,
                       connect_id,
                       XIM_PREEDIT_DONE,
                       0,
                       reply,
                       total_size);
    FrameMgrFree (fm);
    XFree (reply);


    return True;
}
