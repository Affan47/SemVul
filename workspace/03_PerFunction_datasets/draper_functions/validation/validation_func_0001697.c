getsetCommand(redisClient *c) {
    getCommand(c);
    if (dictAdd(c->db->dict,c->argv[1],c->argv[2]) == DICT_ERR) {
        dictReplace(c->db->dict,c->argv[1],c->argv[2]);
    } else {
        incrRefCount(c->argv[1]);
    }
    incrRefCount(c->argv[2]);
    server.dirty++;
    removeExpire(c->db,c->argv[1]);
}
