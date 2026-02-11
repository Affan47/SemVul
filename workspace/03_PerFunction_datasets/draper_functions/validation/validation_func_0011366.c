singleTableHelp(FILE * f, const struct poptOption * table,
			    int left) {
    const struct poptOption * opt;

    opt = table;
    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->longName || opt->shortName) &&
	    !(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN))
	    singleOptionHelp(f, left, opt);
	opt++;
    }

    opt = table;
    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    if (opt->descrip)
		fprintf(f, "\n%s\n", _(opt->descrip));
	    singleTableHelp(f, opt->arg, left);
	}
	opt++;
    }
}
