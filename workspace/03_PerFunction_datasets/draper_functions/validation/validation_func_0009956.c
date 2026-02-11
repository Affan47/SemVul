_get_ip_from_xff(const char *xffheader)
{
    char *xff = strdup(xffheader);
    char *xff_ip, *break_ptr;
    uint32_t ipnum;
    if (xff) {
        for (xff_ip = strtok_r(xff, " \t,", &break_ptr); xff_ip;
             xff_ip = strtok_r(NULL, " \t,", &break_ptr)) {
            if (1 != inet_pton(AF_INET, xff_ip, &ipnum))
                continue;
            ipnum = htonl(ipnum);
            if (!_is_private(ipnum)) {
                char *found = strdup(xff_ip);
                free(xff);
                return found;
            }
        }
        free(xff);
    }
    return NULL;
}
