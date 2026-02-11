synth_buffer_free(void)
{
	int bytes_free;

	if (buff_in >= buff_out)
		bytes_free = SYNTH_BUF_SIZE - (buff_in - buff_out);
	else
		bytes_free = buff_out - buff_in;
	return bytes_free;
}
