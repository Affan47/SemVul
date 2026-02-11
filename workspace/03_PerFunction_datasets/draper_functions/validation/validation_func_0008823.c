nr_port_ptr(char *name)
{
	NR_Port *p = nr_ports;

	if (name == NULL)
		return p;

	while (p != NULL) {
		if (p->Name != NULL && strcasecmp(name, p->Name) == 0)
			return p;
		p = p->Next;
	}

	return NULL;
}
