x86_64_debug_dump_page(FILE *ofp, char *page, char *name)
{
	int i;
	ulong *up;

        fprintf(ofp, "%s\n", name);

        up = (ulong *)page;
        for (i = 0; i < 256; i++) {
        	fprintf(ofp, "%016lx: %016lx %016lx\n",
                        (ulong)((i * 2) * sizeof(ulong)),
                        *up, *(up+1));
                up += 2;
        }
}
