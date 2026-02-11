nfs4_get_device_info(struct nfs_server *server,
		const struct nfs4_deviceid *dev_id,
		struct rpc_cred *cred, gfp_t gfp_flags)
{
	struct nfs4_deviceid_node *d = NULL;
	struct pnfs_device *pdev = NULL;
	struct page **pages = NULL;
	u32 max_resp_sz;
	int max_pages;
	int rc, i;


	max_resp_sz = server->nfs_client->cl_session->fc_attrs.max_resp_sz;
	if (server->pnfs_curr_ld->max_deviceinfo_size &&
	    server->pnfs_curr_ld->max_deviceinfo_size < max_resp_sz)
		max_resp_sz = server->pnfs_curr_ld->max_deviceinfo_size;
	max_pages = nfs_page_array_len(0, max_resp_sz);
	dprintk("%s: server %p max_resp_sz %u max_pages %d\n",
		__func__, server, max_resp_sz, max_pages);

	pdev = kzalloc(sizeof(*pdev), gfp_flags);
	if (!pdev)
		return NULL;

	pages = kcalloc(max_pages, sizeof(struct page *), gfp_flags);
	if (!pages)
		goto out_free_pdev;

	for (i = 0; i < max_pages; i++) {
		pages[i] = alloc_page(gfp_flags);
		if (!pages[i])
			goto out_free_pages;
	}

	memcpy(&pdev->dev_id, dev_id, sizeof(*dev_id));
	pdev->layout_type = server->pnfs_curr_ld->id;
	pdev->pages = pages;
	pdev->pgbase = 0;
	pdev->pglen = max_resp_sz;
	pdev->mincount = 0;
	pdev->maxcount = max_resp_sz - nfs41_maxgetdevinfo_overhead;

	rc = nfs4_proc_getdeviceinfo(server, pdev, cred);
	dprintk("%s getdevice info returns %d\n", __func__, rc);
	if (rc)
		goto out_free_pages;


	d = server->pnfs_curr_ld->alloc_deviceid_node(server, pdev,
			gfp_flags);
	if (d && pdev->nocache)
		set_bit(NFS_DEVICEID_NOCACHE, &d->flags);

out_free_pages:
	for (i = 0; i < max_pages; i++)
		__free_page(pages[i]);
	kfree(pages);
out_free_pdev:
	kfree(pdev);
	dprintk("<-- %s d %p\n", __func__, d);
	return d;
}
