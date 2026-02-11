expand_conf(void)
{
    list_t *ptr;
    list_for_each(ptr, sysfaci_start) {
	list_t * rlist, * safe, * head = &getfaci(ptr)->replace;
	list_for_each_safe(rlist, safe, head) {
	    repl_t * tmp = getrepl(rlist);
	    if (*tmp->r[0].name == '$') {
		int deep = 0;
		tmp->flags |= 0x0001;
		expand_faci(rlist, rlist, &deep);
		tmp->flags &= ~0x0001;
	    }
	}
    }
}
