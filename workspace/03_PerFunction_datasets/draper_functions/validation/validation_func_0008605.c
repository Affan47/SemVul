mygethostbyname(char * name, struct in_addr * addr)
{
        struct hostent * h;

        h = gethostbyname(name);
        if (!h) {
                l1(OUTPUT_TYPE_DEBUG, "Unknown host %s", name);
                return -1;

        } else if (h->h_addr_list && (h->h_addr_list)[0]) {
                memcpy(addr, (h->h_addr_list)[0], sizeof(*addr));
                l2(OUTPUT_TYPE_DEBUG, "%s is at %s", name, inet_ntoa(*addr));
                return 0;
        }
        return -1;
}
