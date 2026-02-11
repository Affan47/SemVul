test_readable_symbol(symbol_t *symbol)
{

	if ((symbol->info.rinfo->modes & (0x1 << src_mode)) == 0) {
		snprintf(errbuf, sizeof(errbuf),
			"Register %s unavailable in source reg mode %d",
			symbol->name, src_mode);
		stop(errbuf, EX_DATAERR);
	}

	if (symbol->info.rinfo->mode == WO) {
		stop("Write Only register specified as source",
		     EX_DATAERR);

	}
}
