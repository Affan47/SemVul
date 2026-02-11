synth_buffer_add(char ch)
{
	if (!synth->alive) {


		return;
	}
	if (synth_buffer_free() <= 100) {
		synth_start();
		speakup_stop_ttys();
	}
	if (synth_buffer_free() <= 1)
		return;
	*buff_in++ = ch;
	if (buff_in > buffer_end)
		buff_in = synth_buffer;
}
