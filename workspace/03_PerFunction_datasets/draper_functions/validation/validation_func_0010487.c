_init_key_scan(uint8_t *data, uint32_t size,
	uint8_t **inputparams_start, uint8_t **inputparams_end)
{
	int err;


	err = GetTag("INPUTPARMS", data, size, *inputparams_start);
	if (err == 0) {

		err = GetTag("/INPUTPARMS", *inputparams_start,
			size - (*inputparams_start - data), *inputparams_end);
	}
	return err;
}
