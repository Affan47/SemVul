int udp_output(struct socket *so, struct mbuf *m, struct sockaddr_in *saddr,
               struct sockaddr_in *daddr, int iptos)
{
    Slirp *slirp = m->slirp;
    M_DUP_DEBUG(slirp, m, 0, sizeof(struct udpiphdr));

    register struct udpiphdr *ui;
    int error = 0;

    DEBUG_CALL("udp_output");
    DEBUG_ARG("so = %p", so);
    DEBUG_ARG("m = %p", m);
    DEBUG_ARG("saddr = %s", inet_ntoa(saddr->sin_addr));
    DEBUG_ARG("daddr = %s", inet_ntoa(daddr->sin_addr));


    m->m_data -= sizeof(struct udpiphdr);
    m->m_len += sizeof(struct udpiphdr);


    ui = mtod(m, struct udpiphdr *);
    memset(&ui->ui_i.ih_mbuf, 0, sizeof(struct mbuf_ptr));
    ui->ui_x1 = 0;
    ui->ui_pr = IPPROTO_UDP;
    ui->ui_len = htons(m->m_len - sizeof(struct ip));


    ui->ui_src = saddr->sin_addr;
    ui->ui_dst = daddr->sin_addr;
    ui->ui_sport = saddr->sin_port;
    ui->ui_dport = daddr->sin_port;
    ui->ui_ulen = ui->ui_len;


    ui->ui_sum = 0;
    if ((ui->ui_sum = cksum(m, m->m_len)) == 0)
        ui->ui_sum = 0xffff;
    ((struct ip *)ui)->ip_len = m->m_len;

    ((struct ip *)ui)->ip_ttl = IPDEFTTL;
    ((struct ip *)ui)->ip_tos = iptos;

    error = ip_output(so, m);

    return (error);
}
