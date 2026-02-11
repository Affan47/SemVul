ipop(void)
{
	struct input *in, *me;

	assert("pop input list", inputs != 0);
	if(inputs->next == 0){
		me = inputs;
		inputs = 0;
	} else {
		for(in = inputs; in->next->next; )
			in = in->next;
		me = in->next;
		in->next = 0;
	}
	infile = me->file;
	mkinline = me->line;
	free((char *)me);
}
