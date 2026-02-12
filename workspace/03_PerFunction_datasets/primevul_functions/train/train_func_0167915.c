static void DoCSI(int c, int intermediate)
{
	int i, a1 = curr->w_args[0], a2 = curr->w_args[1];

	if (curr->w_NumArgs > MAXARGS)
		curr->w_NumArgs = MAXARGS;
	switch (intermediate) {
	case 0:
		switch (c) {
		case 'H':
		case 'f':
			if (a1 < 1)
				a1 = 1;
			if (curr->w_origin)
				a1 += curr->w_top;
			if (a1 > rows)
				a1 = rows;
			if (a2 < 1)
				a2 = 1;
			if (a2 > cols)
				a2 = cols;
			LGotoPos(&curr->w_layer, --a2, --a1);
			curr->w_x = a2;
			curr->w_y = a1;
			if (curr->w_autoaka)
				curr->w_autoaka = a1 + 1;
			break;
		case 'J':
			if (a1 < 0 || a1 > 2)
				a1 = 0;
			switch (a1) {
			case 0:
				ClearToEOS();
				break;
			case 1:
				ClearFromBOS();
				break;
			case 2:
				ClearScreen();
				LGotoPos(&curr->w_layer, curr->w_x, curr->w_y);
				break;
			}
			break;
		case 'K':
			if (a1 < 0 || a1 > 2)
				a1 %= 3;
			switch (a1) {
			case 0:
				ClearLineRegion(curr->w_x, cols - 1);
				break;
			case 1:
				ClearLineRegion(0, curr->w_x);
				break;
			case 2:
				ClearLineRegion(0, cols - 1);
				break;
			}
			break;
		case 'X':
			a1 = curr->w_x + (a1 ? a1 - 1 : 0);
			ClearLineRegion(curr->w_x, a1 < cols ? a1 : cols - 1);
			break;
		case 'A':
			CursorUp(a1 ? a1 : 1);
			break;
		case 'B':
			CursorDown(a1 ? a1 : 1);
			break;
		case 'C':
			CursorRight(a1 ? a1 : 1);
			break;
		case 'D':
			CursorLeft(a1 ? a1 : 1);
			break;
		case 'E':
			curr->w_x = 0;
			CursorDown(a1 ? a1 : 1);
			break;
		case 'F':
			curr->w_x = 0;
			CursorUp(a1 ? a1 : 1);
			break;
		case 'G':
		case '`':
			curr->w_x = a1 ? a1 - 1 : 0;
			if (curr->w_x >= cols)
				curr->w_x = cols - 1;
			LGotoPos(&curr->w_layer, curr->w_x, curr->w_y);
			break;
		case 'd':
			curr->w_y = a1 ? a1 - 1 : 0;
			if (curr->w_y >= rows)
				curr->w_y = rows - 1;
			LGotoPos(&curr->w_layer, curr->w_x, curr->w_y);
			break;
		case 'm':
			SelectRendition();
			break;
		case 'g':
			if (a1 == 0)
				curr->w_tabs[curr->w_x] = 0;
			else if (a1 == 3)
				memset(curr->w_tabs, 0, cols);
			break;
		case 'r':
			if (!a1)
				a1 = 1;
			if (!a2)
				a2 = rows;
			if (a1 < 1 || a2 > rows || a1 >= a2)
				break;
			curr->w_top = a1 - 1;
			curr->w_bot = a2 - 1;

			if (curr->w_origin) {
				curr->w_y = curr->w_top;
				curr->w_x = 0;
			} else
				curr->w_y = curr->w_x = 0;
			LGotoPos(&curr->w_layer, curr->w_x, curr->w_y);
			break;
		case 's':
			SaveCursor(&curr->w_saved);
			break;
		case 't':
			switch (a1) {
			case 11:
				if (curr->w_layer.l_cvlist)
					Report("\033[1t", 0, 0);
				else
					Report("\033[2t", 0, 0);
				break;
			case 7:
				LRefreshAll(&curr->w_layer, 0);
				break;
			case 21:
				a1 = strlen(curr->w_title);
				if ((unsigned)(curr->w_inlen + 5 + a1) <= sizeof(curr->w_inbuf)) {
					memmove(curr->w_inbuf + curr->w_inlen, "\033]l", 3);
					memmove(curr->w_inbuf + curr->w_inlen + 3, curr->w_title, a1);
					memmove(curr->w_inbuf + curr->w_inlen + 3 + a1, "\033\\", 2);
					curr->w_inlen += 5 + a1;
				}
				break;
			case 8:
				a1 = curr->w_args[2];
				if (a1 < 1)
					a1 = curr->w_width;
				if (a2 < 1)
					a2 = curr->w_height;
				if (a1 > 10000 || a2 > 10000)
					break;
				WChangeSize(curr, a1, a2);
				cols = curr->w_width;
				rows = curr->w_height;
				break;
			default:
				break;
			}
			break;
		case 'u':
			RestoreCursor(&curr->w_saved);
			break;
		case 'I':
			if (!a1)
				a1 = 1;
			while (a1--)
				ForwardTab();
			break;
		case 'Z':
			if (!a1)
				a1 = 1;
			while (a1--)
				BackwardTab();
			break;
		case 'L':
			InsertLine(a1 ? a1 : 1);
			break;
		case 'M':
			DeleteLine(a1 ? a1 : 1);
			break;
		case 'P':
			DeleteChar(a1 ? a1 : 1);
			break;
		case '@':
			InsertChar(a1 ? a1 : 1);
			break;
		case 'h':
			ASetMode(1);
			break;
		case 'l':
			ASetMode(0);
			break;
		case 'i':
			if (a1 == 5)
				PrintStart();
			break;
		case 'n':
			if (a1 == 5)
				Report("\033[0n", 0, 0);
			else if (a1 == 6)
				Report("\033[%d;%dR", curr->w_y + 1, curr->w_x + 1);
			break;
		case 'c':
			if (a1 == 0)
				Report("\033[?%d;%dc", 1, 2);
			break;
		case 'x':
			if (a1 == 0 || a1 == 1)
				Report("\033[%d;1;1;112;112;1;0x", a1 + 2, 0);
			break;
		case 'p':
			if (a1 == 6 || a1 == 7) {
				curr->w_curinv = 7 - a1;
				LCursorVisibility(&curr->w_layer, curr->w_curinv ? -1 : curr->w_curvvis);
			}
			break;
		case 'S':
			ScrollRegion(a1 ? a1 : 1);
			break;
		case 'T':
		case '^':
			ScrollRegion(a1 ? -a1 : -1);
			break;
		}
		break;
	case ' ':
		if (c == 'q') {
			curr->w_cursorstyle = a1;
			LCursorStyle(&curr->w_layer, curr->w_cursorstyle);
		}
		break;
	case '?':
		for (a2 = 0; a2 < curr->w_NumArgs; a2++) {
			a1 = curr->w_args[a2];
			if (c != 'h' && c != 'l')
				break;
			i = (c == 'h');
			switch (a1) {
			case 1:
				LCursorkeysMode(&curr->w_layer, curr->w_cursorkeys = i);
#ifndef TIOCPKT
				WNewAutoFlow(curr, !i);
#endif
				break;
			case 2:
				if (i) {
					if (curr->w_encoding)
						break;
					curr->w_charsets[0] = curr->w_charsets[1] =
					    curr->w_charsets[2] = curr->w_charsets[3] =
					    curr->w_FontL = curr->w_FontR = ASCII;
					curr->w_Charset = 0;
					curr->w_CharsetR = 2;
					curr->w_ss = 0;
				}
				break;
			case 3:
				i = (i ? Z0width : Z1width);
				ClearScreen();
				curr->w_x = 0;
				curr->w_y = 0;
				WChangeSize(curr, i, curr->w_height);
				cols = curr->w_width;
				rows = curr->w_height;
				break;

			case 5:
				if (i != curr->w_revvid)
					WReverseVideo(curr, i);
				curr->w_revvid = i;
				break;
			case 6:
				if ((curr->w_origin = i) != 0) {
					curr->w_y = curr->w_top;
					curr->w_x = 0;
				} else
					curr->w_y = curr->w_x = 0;
				LGotoPos(&curr->w_layer, curr->w_x, curr->w_y);
				break;
			case 7:
				curr->w_wrap = i;
				break;


			case 9:
				curr->w_mouse = i ? 9 : 0;
				LMouseMode(&curr->w_layer, curr->w_mouse);
				break;


			case 25:
				curr->w_curinv = !i;
				LCursorVisibility(&curr->w_layer, curr->w_curinv ? -1 : curr->w_curvvis);
				break;


			case 47:
			case 1047:
			case 1049:
				if (use_altscreen) {
					if (i) {
						if (!curr->w_alt.on) {
							SaveCursor(&curr->w_alt.cursor);
							EnterAltScreen(curr);
						}
					} else {
						if (curr->w_alt.on) {
							RestoreCursor(&curr->w_alt.cursor);
							LeaveAltScreen(curr);
						}
					}
					if (a1 == 47 && !i)
						curr->w_saved.on = 0;
					LRefreshAll(&curr->w_layer, 0);
					LGotoPos(&curr->w_layer, curr->w_x, curr->w_y);
				}
				break;
			case 1048:
				if (i)
					SaveCursor(&curr->w_saved);
				else
					RestoreCursor(&curr->w_saved);
				break;


			case 1000:
			case 1001:
			case 1002:
			case 1003:
				curr->w_mouse = i ? a1 : 0;
				LMouseMode(&curr->w_layer, curr->w_mouse);
				break;
			case 2004:
				curr->w_bracketed = i ? 1 : 0;
				LBracketedPasteMode(&curr->w_layer, curr->w_bracketed);
				break;
			}
		}
		break;
	case '>':
		switch (c) {
		case 'c':
			if (a1 == 0)
				Report("\033[>%d;%d;0c", 83, nversion);
			break;
		}
		break;
	}
}
