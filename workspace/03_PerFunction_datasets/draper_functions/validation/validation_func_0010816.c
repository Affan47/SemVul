backgroundSaveDoneHandler(int exitcode, int bysignal) {
    switch(server.rdb_child_type) {
    case REDIS_RDB_CHILD_TYPE_DISK:
        backgroundSaveDoneHandlerDisk(exitcode,bysignal);
        break;
    case REDIS_RDB_CHILD_TYPE_SOCKET:
        backgroundSaveDoneHandlerSocket(exitcode,bysignal);
        break;
    default:
        redisPanic("Unknown RDB child type.");
        break;
    }
}
