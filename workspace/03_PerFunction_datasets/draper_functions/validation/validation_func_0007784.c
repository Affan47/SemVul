hfs_ext_keycmp(const btree_key *key1, const btree_key *key2)
{
	__be32 fnum1, fnum2;
	__be16 block1, block2;

	fnum1 = key1->ext.FNum;
	fnum2 = key2->ext.FNum;
	if (fnum1 != fnum2)
		return be32_to_cpu(fnum1) < be32_to_cpu(fnum2) ? -1 : 1;
	if (key1->ext.FkType != key2->ext.FkType)
		return key1->ext.FkType < key2->ext.FkType ? -1 : 1;

	block1 = key1->ext.FABN;
	block2 = key2->ext.FABN;
	if (block1 == block2)
		return 0;
	return be16_to_cpu(block1) < be16_to_cpu(block2) ? -1 : 1;
}
