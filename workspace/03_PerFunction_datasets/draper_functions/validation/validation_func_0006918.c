parse_port_lid_and_lmc(Port * port, char *line)
{
	char *s;

	if ((s = strstr(line, "lid "))) {
		s += 4;
		port->lid = strtoul(s, NULL, 0);
	}
	if ((s = strstr(line, "lmc "))) {
		s += 4;
		port->lmc = strtoul(s, NULL, 0);
	}

	return 0;
}
