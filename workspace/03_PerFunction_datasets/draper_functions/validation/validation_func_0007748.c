mode(ModeType type)
{
	u16 ret = false;
	switch (type) {
	case AutoRepeatKey:
		ret = mode_flags.autorepeat_key;
		break;
	case ApplicKeypad:
		ret = mode_flags.applic_keypad;
		break;
	case MouseReport:
		ret = mode_flags.mouse_report;
		break;
	case CursorShape:
		ret = mode_flags.cursor_shape;
		break;
	case CursorKeyEscO:
		ret = mode_flags.cursorkey_esco;
		break;
	case CRWithLF:
		ret = mode_flags.crlf;
		break;
	case CursorVisible:
		ret = mode_flags.cursor_visible && (visual_start_line == total_history_lines());
		break;
	default:
		break;
	}

	return ret;
}
