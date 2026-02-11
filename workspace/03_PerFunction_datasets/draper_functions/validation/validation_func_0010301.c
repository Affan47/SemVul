LineInput(char *buf, size_t n)
{
	event_t ev;
	int done = 0;

	glk_request_line_event(Bottom, buf, n - 1, 0);

	while(!done)
	{
		glk_select(&ev);

		if(ev.type == evtype_LineInput)
			done = 1;
		else if(ev.type == evtype_Arrange && split_screen)
			Look();
	}

	buf[ev.val1] = 0;
}
