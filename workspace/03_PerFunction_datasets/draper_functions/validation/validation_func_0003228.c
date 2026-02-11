do_glock(struct gfs2_quota_data *qd, int force_refresh,
		    struct gfs2_holder *q_gh)
{
	struct gfs2_sbd *sdp = qd->qd_gl->gl_name.ln_sbd;
	struct gfs2_inode *ip = GFS2_I(sdp->sd_quota_inode);
	struct gfs2_holder i_gh;
	int error;

restart:
	error = gfs2_glock_nq_init(qd->qd_gl, LM_ST_SHARED, 0, q_gh);
	if (error)
		return error;

	if (test_and_clear_bit(QDF_REFRESH, &qd->qd_flags))
		force_refresh = FORCE;

	qd->qd_qb = *(struct gfs2_quota_lvb *)qd->qd_gl->gl_lksb.sb_lvbptr;

	if (force_refresh || qd->qd_qb.qb_magic != cpu_to_be32(GFS2_MAGIC)) {
		gfs2_glock_dq_uninit(q_gh);
		error = gfs2_glock_nq_init(qd->qd_gl, LM_ST_EXCLUSIVE,
					   GL_NOCACHE, q_gh);
		if (error)
			return error;

		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, 0, &i_gh);
		if (error)
			goto fail;

		error = update_qd(sdp, qd);
		if (error)
			goto fail_gunlock;

		gfs2_glock_dq_uninit(&i_gh);
		gfs2_glock_dq_uninit(q_gh);
		force_refresh = 0;
		goto restart;
	}

	return 0;

fail_gunlock:
	gfs2_glock_dq_uninit(&i_gh);
fail:
	gfs2_glock_dq_uninit(q_gh);
	return error;
}
