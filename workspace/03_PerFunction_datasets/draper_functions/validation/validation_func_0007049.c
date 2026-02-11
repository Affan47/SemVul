umrtn(MENU *m)
{
	dostaupd = 1;
	if (m->func)
		return m->func(m, m->cursor, m->object, 0);
	else
		return -1;
}
