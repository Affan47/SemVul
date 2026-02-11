ReadOSMInfo(GByte* pabyData, GByte* pabyDataLimit,
             OSMInfo* psInfo, OSMContext* psContext)
{

    while(pabyData < pabyDataLimit)
    {
        int nKey;
        READ_FIELD_KEY(nKey);

        if (nKey == MAKE_KEY(INFO_IDX_VERSION, WT_VARINT))
        {
            READ_VARINT32(pabyData, pabyDataLimit, psInfo->nVersion);
        }
        else if (nKey == MAKE_KEY(INFO_IDX_TIMESTAMP, WT_VARINT))
        {
            READ_VARINT64(pabyData, pabyDataLimit, psInfo->ts.nTimeStamp);
        }
        else if (nKey == MAKE_KEY(INFO_IDX_CHANGESET, WT_VARINT))
        {
            READ_VARINT64(pabyData, pabyDataLimit, psInfo->nChangeset);
        }
        else if (nKey == MAKE_KEY(INFO_IDX_UID, WT_VARINT))
        {
            READ_VARINT32(pabyData, pabyDataLimit, psInfo->nUID);
        }
        else if (nKey == MAKE_KEY(INFO_IDX_USER_SID, WT_VARINT))
        {
            unsigned int nUserSID;
            READ_VARUINT32(pabyData, pabyDataLimit, nUserSID);
            if( nUserSID < psContext->nStrCount)
                psInfo->pszUserSID = psContext->pszStrBuf +
                                     psContext->panStrOff[nUserSID];
        }
        else if (nKey == MAKE_KEY(INFO_IDX_VISIBLE, WT_VARINT))
        {
            int nVisible;
            READ_VARINT32(pabyData, pabyDataLimit, nVisible);
        }
        else
        {
            SKIP_UNKNOWN_FIELD(pabyData, pabyDataLimit, TRUE);
        }
    }


    return pabyData == pabyDataLimit;

end_error:


    return FALSE;
}
