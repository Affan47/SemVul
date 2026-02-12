static int get_key3(request_st * const r, char *buf, uint32_t bytes) {


    chunkqueue *cq = &r->reqbody_queue;


    return chunkqueue_read_data(cq, buf, bytes, r->conf.errh);
}
