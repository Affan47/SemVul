byte_offset(Volume_t *V, DWORD Cluster, DWORD Offset) {
	off64_t clus = Cluster;
	off64_t off	 = Offset;

	if (Cluster == 1)
		if (V->FatType != FAT32) return (V->rootdir16off + off);


	return  ( ((clus - 2) * V->bpc64) + V->fdb64 + off );
}
