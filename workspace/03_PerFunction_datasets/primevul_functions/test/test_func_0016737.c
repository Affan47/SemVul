static int disposition_to_open_flags(uint32_t create_disposition)
{
	int ret = 0;


	switch (create_disposition) {
	case FILE_SUPERSEDE:
	case FILE_OVERWRITE_IF:


		ret = O_CREAT|O_TRUNC;
		break;

	case FILE_OPEN:


		ret = 0;
		break;

	case FILE_OVERWRITE:


		ret = O_TRUNC;
		break;

	case FILE_CREATE:


		ret = O_CREAT|O_EXCL;
		break;

	case FILE_OPEN_IF:


		ret = O_CREAT;
		break;
	}
	return ret;
}
