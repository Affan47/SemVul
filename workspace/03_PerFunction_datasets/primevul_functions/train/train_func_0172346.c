static void get_random_vector(unsigned char *vector)
{
#ifdef linux
	int fd = open("/dev/urandom",O_RDONLY);
	int total = 0;
	if (fd >= 0) {
		while (total < AUTH_VECTOR_LEN) {
			int bytes = read(fd, vector + total, AUTH_VECTOR_LEN - total);
			if (bytes <= 0)
				break;
			total += bytes;
		}
		close(fd);
	}

	if (total != AUTH_VECTOR_LEN)
#endif
	{
		MD5_CTX my_md5;
		struct timeval tv;
		struct timezone tz;
		static unsigned int session = 0;


		gettimeofday(&tv,&tz);

		if (session == 0) {
			session = getppid();
		}

		tv.tv_sec ^= getpid() * session++;


		MD5Init(&my_md5);
		MD5Update(&my_md5, (unsigned char *) &tv, sizeof(tv));
		MD5Update(&my_md5, (unsigned char *) &tz, sizeof(tz));
		MD5Final(vector, &my_md5);
	}
}
