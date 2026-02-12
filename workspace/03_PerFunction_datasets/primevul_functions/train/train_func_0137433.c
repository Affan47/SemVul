static int getbody(void *mc, const char **content_types,
                   sieve_bodypart_t ***parts)
{
    deliver_data_t *mydata = (deliver_data_t *) mc;
    message_data_t *m = mydata->m;
    int r = 0;

    if (!mydata->content->body) {

        r = message_parse_file(m->f, &mydata->content->base,
                               &mydata->content->len, &mydata->content->body);
    }


    if (!r) message_fetch_part(mydata->content, content_types,
                               (struct bodypart ***) parts);
    return (!r ? SIEVE_OK : SIEVE_FAIL);
}
