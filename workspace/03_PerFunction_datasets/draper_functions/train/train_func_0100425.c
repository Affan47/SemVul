dumpall(struct filenode *node, int lastoff, FILE *f)
{
	struct romfh ri;
	struct filenode *p;

	ri.nextfh = htonl(0x2d726f6d);
	ri.spec = htonl(0x3166732d);
	ri.size = htonl(lastoff);
	ri.checksum = htonl(0x55555555);
	dumpri(&ri, node, f);
	p = node->dirlist.head;
	while (p->next) {
		dumpnode(p, f);
		p = p->next;
	}

	if (lastoff&1023)
		dumpzero(1024-(lastoff&1023), f);
}
