get_used_ptr(struct deadcode_state *s, rc_register_file file, unsigned int index)
{
	if (file == RC_FILE_OUTPUT || file == RC_FILE_TEMPORARY) {
		if (index >= RC_REGISTER_MAX_INDEX) {
			rc_error(s->C, "%s: index %i is out of bounds for file %i\n", __FUNCTION__, index, file);
			return 0;
		}

		if (file == RC_FILE_OUTPUT)
			return &s->R.Output[index];
		else
			return &s->R.Temporary[index];
	} else if (file == RC_FILE_ADDRESS) {
		return &s->R.Address;
	} else if (file == RC_FILE_SPECIAL) {
		if (index >= RC_NUM_SPECIAL_REGISTERS) {
			rc_error(s->C, "%s: special file index %i out of bounds\n", __FUNCTION__, index);
			return 0;
		}

		return &s->R.Special[index];
	}

	return 0;
}
