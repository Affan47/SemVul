Iwconfig_Set_Channel(const char *in_dev, int in_ch, char *in_err) {
    struct iwreq wrq;
    int skfd;
	int ret = 0;

    if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        snprintf(in_err, STATUS_MAX, "Failed to create AF_INET DGRAM socket %d:%s",
                 errno, strerror(errno));
        return -1;
    }

    memset(&wrq, 0, sizeof(struct iwreq));

    strncpy(wrq.ifr_name, in_dev, IFNAMSIZ);
#ifdef HAVE_LINUX_IWFREQFLAG
	wrq.u.freq.flags = IW_FREQ_FIXED;
#endif
	if (in_ch > 1024)
		IwFloat2Freq(in_ch * 1e6, &wrq.u.freq);
	else
		IwFloat2Freq(in_ch, &wrq.u.freq);


    if (ioctl(skfd, SIOCSIWFREQ, &wrq) < 0) {
        struct timeval tm;
        tm.tv_sec = 0;
        tm.tv_usec = 5000;
        select(0, NULL, NULL, NULL, &tm);

        if (ioctl(skfd, SIOCSIWFREQ, &wrq) < 0) {
			if (errno == ENODEV) {
				ret = -2;
			} else {
				ret = -1;
			}

            snprintf(in_err, STATUS_MAX, "%s", strerror(errno));
            close(skfd);
            return ret;
        }
    }

    close(skfd);
    return 0;
}
