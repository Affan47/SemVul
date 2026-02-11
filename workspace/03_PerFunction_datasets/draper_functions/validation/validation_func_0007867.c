gather_text_list(struct bt_info *bt)
{
	int cnt;
	struct bt_info btloc;
	char buf[BUFSIZE], *p1;
	struct stack_hook *hooks;
	ulong esp, eip;
	FILE *savedfp;

	BCOPY(bt, &btloc, sizeof(struct bt_info));
	hooks = (struct stack_hook *)GETBUF(sizeof(struct stack_hook)*MAXHOOKS);
	cnt = 0;

	savedfp = fp;
        open_tmpfile2();
	fp = pc->tmpfile2;
        btloc.flags = BT_TEXT_SYMBOLS_PRINT;
        back_trace(&btloc);
        rewind(pc->tmpfile2);
        while (fgets(buf, BUFSIZE, pc->tmpfile2)) {
		if ((p1 = strstr(buf, ":"))) {
			esp = eip = 0;
                	*p1 = NULLCHAR;
			if (((esp = htol(buf, RETURN_ON_ERROR, NULL)) != BADADDR)
			    && INSTACK(esp, bt))
                                eip = GET_STACK_ULONG(esp);
			if (esp && eip) {
				hooks[cnt].esp = esp;
				hooks[cnt].eip = eip;
				if (++cnt == MAXHOOKS)
					break;
			}
		}
	}
	close_tmpfile2();
	fp = savedfp;

	if (cnt)
		return (bt->textlist = hooks);
	else {
		FREEBUF(hooks);
		return (bt->textlist = NULL);
	}
}
