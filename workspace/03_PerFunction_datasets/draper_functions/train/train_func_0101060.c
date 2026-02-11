sockaddr_in6_hash(void *data)
{
        struct sockaddr_in6 *addr = data;
        unsigned int i;
        unsigned int result = 0;


        for (i=0; i<16; ++i) {
                result = (result << 5) + result + addr->sin6_addr.s6_addr[i];
        }


        return result + addr->sin6_port;
}
