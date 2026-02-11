locked_read()
{
	message m=locked_peek();
	if (locked_has_message())
		messages->queue.pop();
	return m;
}
