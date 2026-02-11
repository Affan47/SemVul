vcntl(uint cmd, va_list vargs)
{
	switch (cmd) {
		case FCNTL_GET_RELOC: {
			bool *e = va_arg(vargs, bool*);
			*e = enabled;
			return 0;
		}
		case FCNTL_SET_RELOC: {
			enabled = (bool)(va_arg(vargs, int));
			return 0;
		}
	}
	return FileLayer::vcntl(cmd, vargs);
}
