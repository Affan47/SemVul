dopr_outch(int c, PrintfTarget *target)
{
	if (target->bufend != NULL && target->bufptr >= target->bufend)
	{

		if (target->stream == NULL)
			return;
		flushbuffer(target);
	}
	*(target->bufptr++) = c;
}
