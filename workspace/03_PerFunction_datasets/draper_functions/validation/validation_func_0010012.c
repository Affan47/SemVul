_HandleRealmList()
{
    DEBUG_LOG("Entering _HandleRealmList");
    if (recv_len() < 5)
        return false;

    recv_skip(5);


    QueryResult *result = LoginDatabase.PQuery("SELECT id,sha_pass_hash FROM account WHERE username = '%s'",_safelogin.c_str());
    if(!result)
    {
        sLog.outError("[ERROR] user %s tried to login and we cannot find him in the database.",_login.c_str());
        close_connection();
        return false;
    }

    uint32 id = (*result)[0].GetUInt32();
    std::string rI = (*result)[1].GetCppString();
    delete result;


    sRealmList.UpdateIfNeed();


    ByteBuffer pkt;
    LoadRealmlist(pkt, id);

    ByteBuffer hdr;
    hdr << (uint8) CMD_REALM_LIST;
    hdr << (uint16)pkt.size();
    hdr.append(pkt);

    send((char const*)hdr.contents(), hdr.size());

    return true;
}
