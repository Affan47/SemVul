x2sys_strerror (int err)
{


	switch (err) {
		case X2SYS_FCLOSE_ERR:
			return "Error from fclose";
		case X2SYS_BAD_DEF:
			return "Cannot find format definition file in either current or X2SYS_HOME directories";
		case X2SYS_BAD_COL:
			return "Unrecognized string";
		case X2SYS_TAG_NOT_SET:
			return "TAG has not been set";
		case X2SYS_BAD_ARG:
			return "Unrecognized argument";
		case X2SYS_CONFLICTING_ARGS:
			return "Conflicting arguments";
		case X2SYS_BIX_BAD_J:
			return "Bad j index";
		case X2SYS_BIX_BAD_I:
			return "Bad i index";
		case X2SYS_BIX_BAD_IJ:
			return "Bad ij index";
		default:
			return GMT_strerror(err);
	}
}
