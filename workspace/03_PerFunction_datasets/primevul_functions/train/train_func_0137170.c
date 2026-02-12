int bpf_link_settle(struct bpf_link_primer *primer)
{

	spin_lock_bh(&link_idr_lock);
	primer->link->id = primer->id;
	spin_unlock_bh(&link_idr_lock);

	fd_install(primer->fd, primer->file);

	return primer->fd;
}
