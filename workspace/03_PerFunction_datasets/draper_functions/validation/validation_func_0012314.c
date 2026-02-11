braille_unregister_console(struct console *console)
{
	if (braille_co != console)
		return -EINVAL;
	if (!(console->flags & CON_BRL))
		return 0;
	unregister_keyboard_notifier(&keyboard_notifier_block);
	unregister_vt_notifier(&vt_notifier_block);
	braille_co = NULL;
	return 1;
}
