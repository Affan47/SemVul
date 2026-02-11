clear_buffer(CUDPSOCKET *_object)
{
	if (THIS->buffer)
	{
		GB.Free(POINTER(&THIS->buffer));
		THIS->buffer_pos = 0;
		THIS->buffer_len = 0;
	}
}
