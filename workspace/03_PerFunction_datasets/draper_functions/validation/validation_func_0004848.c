be_prt(const int sock)
{
    BACKEND be;
    struct  sockaddr_storage    a, h;
    int     n_be;

    n_be = 0;
    while(read(sock, (void *)&be, sizeof(BACKEND)) == sizeof(BACKEND)) {
        if(be.disabled < 0)
            break;
        read(sock, &a, be.addr.ai_addrlen);
        be.addr.ai_addr = (struct sockaddr *)&a;
        if(be.ha_addr.ai_addrlen > 0) {
            read(sock, &h, be.ha_addr.ai_addrlen);
            be.ha_addr.ai_addr = (struct sockaddr *)&h;
        }
        if(xml_out)
            printf("<backend index=\"%d\" address=\"%s\" avg=\"%.3f\" priority=\"%d\" alive=\"%s\" status=\"%s\" />\n",
                n_be++,
                prt_addr(&be.addr), be.t_average / 1000000, be.priority, be.alive? "yes": "DEAD",
                be.disabled? "DISABLED": "active");
        else
            printf("    %3d. Backend %s %s (%d %.3f sec) %s\n", n_be++, prt_addr(&be.addr),
                be.disabled? "DISABLED": "active", be.priority, be.t_average / 1000000, be.alive? "alive": "DEAD");
    }
    return;
}
