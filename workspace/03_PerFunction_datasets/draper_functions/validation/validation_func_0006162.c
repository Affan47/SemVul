bl_pg_init_write(struct nfs_pageio_descriptor *pgio, struct nfs_page *req)
{
	u64 wb_size;

	if (!is_aligned_req(pgio, req, PAGE_SIZE)) {
		nfs_pageio_reset_write_mds(pgio);
		return;
	}

	if (pgio->pg_dreq == NULL)
		wb_size = pnfs_num_cont_bytes(pgio->pg_inode,
					      req->wb_index);
	else
		wb_size = nfs_dreq_bytes_left(pgio->pg_dreq);

	pnfs_generic_pg_init_write(pgio, req, wb_size);
}
