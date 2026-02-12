change_inv_order(op)
char *op;
{
    int oc_sym, num;
    char *sp, buf[BUFSZ];

    num = 0;
#ifndef GOLDOBJ
    if (!index(op, GOLD_SYM))
	buf[num++] = COIN_CLASS;
#else

#endif

    for (sp = op; *sp; sp++) {
	oc_sym = def_char_to_objclass(*sp);

	if (oc_sym == MAXOCLASSES ||
		oc_sym == RANDOM_CLASS || oc_sym == ILLOBJ_CLASS ||
		!index(flags.inv_order, oc_sym) || index(sp+1, *sp))
	    return 0;

	buf[num++] = (char) oc_sym;
    }
    buf[num] = '\0';


    for (sp = flags.inv_order; *sp; sp++)
	if (!index(buf, *sp)) {
	    buf[num++] = *sp;
	    buf[num] = '\0';
	}

    Strcpy(flags.inv_order, buf);
    return 1;
}
