pnumber(struct part_desc *p, struct disk_desc *z) {
    static char buf[20];
    int this, next;
    struct part_desc *p0 = &(z->partitions[0]);

    this = index_to_linux(p - p0, z);
    next = index_to_linux(p - p0 + 1, z);

    if (next > this)
	sprintf(buf, "%d", this);
    else
	sprintf(buf, "[%d]", this);
    return buf;
}
