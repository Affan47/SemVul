TTL74153_update(int which)
{
	int sel;
	int section;


	sel = (chips[which].b << 1) | chips[which].a;


	for (section = 0; section < 2; section++)
	{
		if (chips[which].enable[section])
			chips[which].output[section] = 0;
		else
			chips[which].output[section] = chips[which].input_lines[section][sel];
	}


	if (  chips[which].output_cb &&
		((chips[which].output[0] != chips[which].last_output[0]) ||
		 (chips[which].output[1] != chips[which].last_output[1])))
	{
		chips[which].last_output[0] = chips[which].output[0];
		chips[which].last_output[1] = chips[which].output[1];

		chips[which].output_cb();
	}
}
