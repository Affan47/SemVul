__ceph_lookup_mds_session(struct ceph_mds_client *mdsc,
						   int mds)
{
	struct ceph_mds_session *session;

	if (mds >= mdsc->max_sessions || mdsc->sessions[mds] == NULL)
		return NULL;
	session = mdsc->sessions[mds];
	dout("lookup_mds_session %p %d\n", session,
	     atomic_read(&session->s_ref));
	get_session(session);
	return session;
}
