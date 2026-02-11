key(int k, int x, int y)
{
	switch (k) {
	case 3: case 27: case 'q':
		exit(0);

	case KEY_F(1): case 'h':
		set_centered_pic(0);

		return;

	case KEY_F(2): case 'r':
		set_centered_pic(0);
		start_again();

		while (auto_move())
			;

		break;

	case 8: case 127: case KEY_DELETE:
		set_centered_pic(0);
		stack_undo();
	}
}
