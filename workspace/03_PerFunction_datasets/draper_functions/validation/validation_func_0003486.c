read_tty_driver_serial(struct stats_serial *st_serial, int nbr)
{
	FILE *fp;
	struct stats_serial *st_serial_i;
	int sl = 0;
	char line[256];
	char *p;

	if ((fp = fopen(SERIAL, "r")) == NULL)
		return;

	while ((fgets(line, 256, fp) != NULL) && (sl < nbr)) {

		if ((p = strstr(line, "tx:")) != NULL) {
			st_serial_i = st_serial + sl;
			sscanf(line, "%u", &st_serial_i->line);


			(st_serial_i->line)++;


			sscanf(p + 3, "%u", &st_serial_i->tx);
			if ((p = strstr(line, "rx:")) != NULL) {
				sscanf(p + 3, "%u", &st_serial_i->rx);
			}
			if ((p = strstr(line, "fe:")) != NULL) {
				sscanf(p + 3, "%u", &st_serial_i->frame);
			}
			if ((p = strstr(line, "pe:")) != NULL) {
				sscanf(p + 3, "%u", &st_serial_i->parity);
			}
			if ((p = strstr(line, "brk:")) != NULL) {
				sscanf(p + 4, "%u", &st_serial_i->brk);
			}
			if ((p = strstr(line, "oe:")) != NULL) {
				sscanf(p + 3, "%u", &st_serial_i->overrun);
			}

			sl++;
		}
	}

	fclose(fp);
}
