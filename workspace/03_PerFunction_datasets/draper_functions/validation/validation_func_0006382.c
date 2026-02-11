Term_mousepress(int x, int y, char button)
{

	Term->key_queue[Term->key_head].type = EVT_MOUSE;
	Term->key_queue[Term->key_head].mouse.x = x;
	Term->key_queue[Term->key_head].mouse.y = y;


	Term->key_queue[Term->key_head].mouse.button = (button & 0x0F);
	Term->key_queue[Term->key_head].mouse.mods = ((button & 0xF0)>>4);

	Term->key_head++;


	if (Term->key_head == Term->key_size) Term->key_head = 0;


	if (Term->key_head != Term->key_tail) return (0);

#if 0

	if (++Term->key_tail == Term->key_size) Term->key_tail = 0;
#endif


	return (1);
}
