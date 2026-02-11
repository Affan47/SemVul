set_isolation_level(ISOLATION_LEVEL level) {
    const char* level_str;
    char query[256];

    switch(level) {
    case READ_UNCOMMITTED:
        level_str = "READ UNCOMMITTED";
        break;
    case READ_COMMITTED:
        level_str = "READ COMMITTED";
        break;
    case REPEATABLE_READ:
        level_str = "REPEATABLE READ";
        break;
    case SERIALIZABLE:
        level_str = "SERIALIZABLE";
        break;
    default:
        return -1;
    }
    sprintf(query, "SET SESSION TRANSACTION ISOLATION LEVEL %s", level_str);
    return do_query(query);
}
