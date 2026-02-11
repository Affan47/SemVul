remote_read(apacket *p, atransport *t)
{
    if(readx(t->sfd, &p->msg, sizeof(amessage))){
        D("remote local: read terminated (message)\n");
        return -1;
    }

    fix_endians(p);

#if 0 && defined HAVE_BIG_ENDIAN
    D("read remote packet: %04x arg0=%0x arg1=%0x data_length=%0x data_check=%0x magic=%0x\n",
      p->msg.command, p->msg.arg0, p->msg.arg1, p->msg.data_length, p->msg.data_check, p->msg.magic);
#endif
    if(check_header(p)) {
        D("bad header: terminated (data)\n");
        return -1;
    }

    if(readx(t->sfd, p->data, p->msg.data_length)){
        D("remote local: terminated (data)\n");
        return -1;
    }

    if(check_data(p)) {
        D("bad data: terminated (data)\n");
        return -1;
    }

    return 0;
}
