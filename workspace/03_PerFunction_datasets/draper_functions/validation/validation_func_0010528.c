CommunicateLog(MsgPara *msgpara, const char *fmt, ...)
{
        gchar *log, *msg, *ptr;
        va_list ap;

        if (!FLAG_ISSET(progdt.flags, 2))
                return;

        PalInfo *pal = msgpara->pal;

        if (msgpara->stype == MESSAGE_SOURCE_TYPE_PAL)
                ptr = getformattime(TRUE, _("Recevied-From: Nickname:%s User:%s Host:%s"),
                                    pal->name,pal->user, pal->host);
        else if (msgpara->stype == MESSAGE_SOURCE_TYPE_SELF) {
                if (msgpara->pal)
                        ptr = getformattime(TRUE, _("Send-To: Nickname:%s User:%s Host:%s"),
                                            pal->name, pal->user, pal->host);
                else
                        ptr = getformattime(TRUE, _("Send-Broadcast"));
        } else
                return;

        va_start(ap, fmt);
        msg = g_strdup_vprintf(fmt, ap);
        va_end(ap);
        log = g_strdup_printf("%s\n%s\n%s\n%s\n\n", LOG_START_HEADER,
                                         ptr, msg, LOG_END_HEADER);
        write(fdc, log, strlen(log));
        g_free(log);
        g_free(ptr);
        g_free(msg);
}
