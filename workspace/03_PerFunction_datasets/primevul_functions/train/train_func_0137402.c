static deliver_data_t *setup_special_delivery(deliver_data_t *mydata)
{
    static deliver_data_t dd;
    static message_data_t md;
    static struct message_content mc;

    memcpy(&dd, mydata, sizeof(deliver_data_t));
    dd.m = memcpy(&md, mydata->m, sizeof(message_data_t));
    dd.content = &mc;
    memset(&mc, 0, sizeof(struct message_content));


    const mbname_t *origmbname = msg_getrcpt(mydata->m, mydata->cur_rcpt);


    mbname_t *mbname = mbname_dup(origmbname);
    if (mbname_userid(mbname)) {
        mbname_truncate_boxes(mbname, 0);
    }

    const char *intname = mbname_intname(mbname);
    md.f = append_newstage(intname, time(0),
                           strhash(intname) ,
                           &dd.stage);
    if (md.f) {
        char buf[4096];


        spool_enum_hdrcache(mydata->m->hdrcache, &dump_header, md.f);


        md.body_offset = ftell(md.f);


        fseek(mydata->m->f, mydata->m->body_offset, SEEK_SET);
        while (fgets(buf, sizeof(buf), mydata->m->f)) fputs(buf, md.f);
        fflush(md.f);


        md.size = ftell(md.f);
        md.data = prot_new(fileno(md.f), 0);

        mydata = &dd;
    }
    else mydata = NULL;

    mbname_free(&mbname);

    return mydata;
}
