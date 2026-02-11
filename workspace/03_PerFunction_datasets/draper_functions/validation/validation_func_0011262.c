get_random_bytes(void *buf, int nbytes)
{
        int i, fd = get_random_fd();
        int lose_counter = 0;
        char *cp = (char *) buf;

        if (fd >= 0) {
                while (nbytes > 0) {
                        i = read(fd, cp, nbytes);
                        if (i <= 0) {
                                if (lose_counter++ > 16)
                                        break;
                                continue;
                        }
                        nbytes -= i;
                        cp += i;
                        lose_counter = 0;
                }
        }


        for (i = 0; i < nbytes; i++)
                *cp++ = rand() & 0xFF;
        return;
}
