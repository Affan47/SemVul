IoOggStreamState_clear(IoOggStreamState *self, IoObject *locals, IoMessage *m)
{


	int ret = ogg_stream_clear(DATA(self));
	IOASSERT(ret == 0, "ogg_stream_clear returned non-zero value");

	return self;
}
