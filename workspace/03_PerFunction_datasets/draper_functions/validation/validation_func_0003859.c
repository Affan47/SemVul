dump_packet(const char* name, const char* func, apacket* p)
{
    unsigned  command = p->msg.command;
    int       len     = p->msg.data_length;
    char      cmd[9];
    char      arg0[12], arg1[12];
    int       n;

    for (n = 0; n < 4; n++) {
        int  b = (command >> (n*8)) & 255;
        if (b < 32 || b >= 127)
            break;
        cmd[n] = (char)b;
    }
    if (n == 4) {
        cmd[4] = 0;
    } else {


        snprintf(cmd, sizeof cmd, "%08x", command);
    }

    if (p->msg.arg0 < 256U)
        snprintf(arg0, sizeof arg0, "%d", p->msg.arg0);
    else
        snprintf(arg0, sizeof arg0, "0x%x", p->msg.arg0);

    if (p->msg.arg1 < 256U)
        snprintf(arg1, sizeof arg1, "%d", p->msg.arg1);
    else
        snprintf(arg1, sizeof arg1, "0x%x", p->msg.arg1);

    D("%s: %s: [%s] arg0=%s arg1=%s (len=%d) ",
        name, func, cmd, arg0, arg1, len);
    dump_hex(p->data, len);
}
