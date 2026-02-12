JVM_Available(jint descriptor, jlong* bytes)
{
	jlong curr = 0;
	jlong end = 0;


#if defined(J9UNIX) && !defined(J9ZTPF) && !defined(OSX)
	struct stat64 tempStat;
#endif
#if defined(J9ZOS390) || defined(J9ZTPF) || defined(OSX)
	struct stat tempStat;
#endif
#if defined(LINUX)
	loff_t longResult = 0;
#endif

	Trc_SC_Available_Entry(descriptor, bytes);

	if (descriptor == -1) {
		Trc_SC_Available_bad_descriptor();
		*bytes = 0;
		return JNI_FALSE;
	}

#if defined(WIN32) && !defined(__IBMC__)
	curr = _lseeki64(descriptor, 0, SEEK_CUR);
	if (curr==-1L) {
		if (descriptor == 0) {

			DWORD result = 0;
			if (GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE), &result)) {
				*bytes = result;
			} else {
				*bytes = 0;
			}
			Trc_SC_Available_Exit(1, *bytes);
			return 1;
		}
		Trc_SC_Available_lseek_failed(descriptor);
		return 0;
	}
	end = _lseeki64(descriptor, 0, SEEK_END);
	_lseeki64(descriptor, curr, SEEK_SET);
#else
		if (J9FSTAT(descriptor, &tempStat) == -1) {
			Trc_SC_Available_fstat_failed(descriptor, errno);
			*bytes = 0;
			return 0;
		}
		else if (S_ISFIFO(tempStat.st_mode) || S_ISSOCK(tempStat.st_mode) || S_ISCHR(tempStat.st_mode)) {


			int arg3FIONREAD = 0;

#if defined(J9ZOS390)

			if (!S_ISSOCK(tempStat.st_mode)) {

				*bytes = tempStat.st_size;
				Trc_SC_Available_Exit(1, *bytes);
				return 1;
			}
#endif
			if (ioctl(descriptor, FIONREAD, &(arg3FIONREAD)) == -1) {
				if (descriptor == 0) {

					*bytes = tempStat.st_size;
					Trc_SC_Available_Exit(1, *bytes);
					return 1;
				}
#if (defined(LINUX) && !defined(J9ZTPF)) || defined(AIXPPC) || defined(J9ZOS390)
				else {
					struct pollfd pollOne;
					int  ret = 0;
					pollOne.fd = descriptor;
					pollOne.events = POLLRDNORM | POLLRDBAND | POLLPRI;
					pollOne.revents = 0;
					if (-1 != poll(&pollOne, 1, 0)) {

						if(0 != (pollOne.events & pollOne.revents)) {


							*bytes = 1;
							Trc_SC_Available_Exit(1, *bytes);
							return 1;
						} else {

							*bytes = 0;
							Trc_SC_Available_Exit(1, *bytes);
							return 1;
						}
					} else {

						Trc_SC_Available_poll_failed(descriptor, errno);
						*bytes = 0;
						return 0;
					}
				}
#endif
				Trc_SC_Available_ioctl_failed(descriptor, errno);
				*bytes = 0;
				return 0;
			}

			*bytes = (jlong) arg3FIONREAD;
			Trc_SC_Available_Exit(1, *bytes);
			return 1;
		}
#if defined(LINUX) && !defined(J9VM_ENV_DATA64)
#if __GLIBC_PREREQ(2,4)

	curr = lseek64(descriptor, 0, SEEK_CUR);
#else

	curr = _llseek(descriptor, 0, 0, &longResult, SEEK_CUR);
	if (0 == curr) {

		curr = (jlong) longResult;
	}
#endif
#else
	curr = lseek(descriptor, 0, SEEK_CUR);
#endif
	if (curr==-1L) {
		if (descriptor == 0) {

			*bytes = 0;
			Trc_SC_Available_Exit(1, *bytes);
			return 1;
		}
		Trc_SC_Available_lseek_failed(descriptor);
		return 0;
	}

	end = tempStat.st_size;
#endif

	*bytes = (end-curr);

	Trc_SC_Available_Exit(1, *bytes);

	return 1;
}
