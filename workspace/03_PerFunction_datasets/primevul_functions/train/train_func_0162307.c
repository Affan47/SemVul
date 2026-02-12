static void partitions_free_data(blkid_probe pr __attribute__((__unused__)),
				 void *data)
{
	blkid_partlist ls = (blkid_partlist) data;

	if (!ls)
		return;

	free_parttables(ls);


	free(ls->parts);
	free(ls);
}
