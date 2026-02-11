is_meta(KeySym mod)
{

    if (0xFF20 <= mod && mod <= 0xFF3F)
	return TRUE;


    switch (mod) {
	case XK_Multi_key:
	case XK_Shift_L:
	case XK_Shift_R:
	case XK_Control_L:
	case XK_Control_R:
	case XK_Meta_L:
	case XK_Meta_R:
	case XK_Alt_L:
	case XK_Alt_R:
			return TRUE;
	default:
			return FALSE;
    }
}
