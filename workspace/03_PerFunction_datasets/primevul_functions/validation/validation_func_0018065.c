static void nfs_state_set_open_stateid(struct nfs4_state *state,
		const nfs4_stateid *open_stateid,
		fmode_t fmode,
		nfs4_stateid *freeme)
{


	write_seqlock(&state->seqlock);
	nfs_set_open_stateid_locked(state, open_stateid, freeme);
	switch (fmode) {
	case FMODE_READ:
		set_bit(NFS_O_RDONLY_STATE, &state->flags);
		break;
	case FMODE_WRITE:
		set_bit(NFS_O_WRONLY_STATE, &state->flags);
		break;
	case FMODE_READ|FMODE_WRITE:
		set_bit(NFS_O_RDWR_STATE, &state->flags);
	}
	set_bit(NFS_OPEN_STATE, &state->flags);
	write_sequnlock(&state->seqlock);
}
