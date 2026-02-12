static void multipart_byteranges(struct transaction_t *txn,
                                 const char *msg_base)
{

    struct range *range = txn->resp_body.range;
    const char *type = txn->resp_body.type;


    txn->resp_body.range = NULL;
    txn->resp_body.type = "multipart/byteranges";
    write_multipart_body(HTTP_PARTIAL, txn, NULL, 0, NULL);

    txn->resp_body.type = type;
    while (range) {
        unsigned long offset = range->first;
        unsigned long datalen = range->last - range->first + 1;
        struct range *next = range->next;


        txn->resp_body.range = range;
        write_multipart_body(0, txn, msg_base + offset, datalen, NULL);


        free(range);
        range = next;
    }


    write_multipart_body(0, txn, NULL, 0, NULL);
}
