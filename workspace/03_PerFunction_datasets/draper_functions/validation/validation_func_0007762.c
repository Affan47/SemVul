ss_get_signature(void)
{
	ss_module *m;
	unsigned int size = 0, pos = 0;
	char *info;
	UINT32 signature;


	for(m = ss_registry; m; m=m->next) {
		int i;
		size += strlen(m->name) + 1;
		for(i=0; i<MAX_INSTANCES; i++) {
			ss_entry *e;
			size++;
			for(e = m->instances[i]; e; e=e->next)
				size += strlen(e->name) + 1 + 1 + 4;
		}
	}

	info = malloc(size);


	for(m = ss_registry; m; m=m->next) {
		int i;
		strcpy(info+pos, m->name);
		pos += strlen(m->name) + 1;
		for(i=0; i<MAX_INSTANCES; i++) {
			ss_entry *e;
			info[pos++] = i;
			for(e = m->instances[i]; e; e=e->next) {
				strcpy(info+pos, e->name);
				pos += strlen(e->name) + 1;
				info[pos++] = e->type;
				info[pos++] = e->size;
				info[pos++] = e->size >> 8;
				info[pos++] = e->size >> 16;
				info[pos++] = e->size >> 24;
			}
		}
	}


	signature = crc32(0, (unsigned char *)info, size);

	free(info);
	return signature;
}
