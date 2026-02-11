receive_info(int id, MesgInfo* message, int who) {
    int ret = msgrcv(id, message, sizeof(int), who, 0);
    if (ret == -1)
        syserr("msgrcv");
    return ret;
}
