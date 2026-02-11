make_purge(int so, struct request *rq)
{
    struct mem_obj *obj;
    struct output_object *output;
    char *res, *result = "<body>Unknown status</body>";
    char *succ = "200 Purged Successfully";
    char *fail = "404 Not Found";
    int newobj;

    if (!rq->url.path || !rq->url.host)
        return;
    obj = locate_in_mem(&rq->url, AND_USE | AND_PUT, &newobj, rq);
    if (obj) {
        if (!newobj) {
            my_xlog(OOPS_LOG_HTTP | OOPS_LOG_DBG, "make_purge(): Document destroyed.\n");
            res = succ;
            result = "<body>Successfully removed</body>\n";
            IF_STRDUP(rq->tag, "TCP_HIT");
        } else {
            my_xlog(OOPS_LOG_HTTP | OOPS_LOG_DBG, "make_purge(): Document not found.\n");
            res = fail;
            result = "<body>Document not found\n</body>";
            IF_STRDUP(rq->tag, "TCP_MISS");
        }
        SET(obj->flags, FLAG_DEAD);
        leave_obj(obj);
    } else {

        res = fail;
        my_xlog(OOPS_LOG_HTTP | OOPS_LOG_DBG, "make_purge(): Document not found.\n");
        IF_STRDUP(rq->tag, "TCP_MISS");
    }
    output = malloc(sizeof(*output));
    if (output) {
        bzero(output, sizeof(*output));
        output->body = alloc_buff(128);
        put_av_pair(&output->headers, "HTTP/1.0", res);
        put_av_pair(&output->headers, "Expires:", "Thu, 01 Jan 1970 00:00:01 GMT");
        put_av_pair(&output->headers, "Content-Type:", "text/html");

        if (output->body) {
            attach_data(result, strlen(result), output->body);
        }

        process_output_object(so, output, rq);
        free_output_obj(output);
    }
    log_access(0, rq, NULL);
}
