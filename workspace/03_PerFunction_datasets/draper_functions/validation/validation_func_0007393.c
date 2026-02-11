M_Quit_Key (menuframework_s *self, int key)
{
	switch (key)
	{
	case K_ESCAPE:
	case K_MOUSE2:
	case 'n':
	case 'N':
		M_PopMenu ();
		break;

	case 'Y':
	case 'y':
		cls.key_dest = key_console;
		CL_Quit_f ();
		break;

	default:
		break;
	}

	return NULL;

}
