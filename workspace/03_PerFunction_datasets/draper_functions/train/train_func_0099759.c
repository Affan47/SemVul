afs_vnode_create(struct afs_vnode *vnode, struct key *key,
		     const char *name, umode_t mode, struct afs_fid *newfid,
		     struct afs_file_status *newstatus,
		     struct afs_callback *newcb, struct afs_server **_server)
{
	struct afs_server *server;
	int ret;

	_enter("%s{%x:%u.%u},%x,%s,,",
	       vnode->volume->vlocation->vldb.name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_serial(key),
	       name);


	spin_lock(&vnode->lock);
	vnode->update_cnt++;
	spin_unlock(&vnode->lock);

	do {

		server = afs_volume_pick_fileserver(vnode);
		if (IS_ERR(server))
			goto no_server;

		_debug("USING SERVER: %08x\n", ntohl(server->addr.s_addr));

		ret = afs_fs_create(server, key, vnode, name, mode, newfid,
				    newstatus, newcb, &afs_sync_call);

	} while (!afs_volume_release_fileserver(vnode, server, ret));


	if (ret == 0) {
		afs_vnode_finalise_status_update(vnode, server);
		*_server = server;
	} else {
		afs_vnode_status_update_failed(vnode, ret);
		*_server = NULL;
	}

	_leave(" = %d [cnt %d]", ret, vnode->update_cnt);
	return ret;

no_server:
	spin_lock(&vnode->lock);
	vnode->update_cnt--;
	ASSERTCMP(vnode->update_cnt, >=, 0);
	spin_unlock(&vnode->lock);
	_leave(" = %ld [cnt %d]", PTR_ERR(server), vnode->update_cnt);
	return PTR_ERR(server);
}
