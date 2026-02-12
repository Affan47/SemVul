static void vidtv_s302m_compute_pts_from_video(struct vidtv_encoder *e)
{
	struct vidtv_access_unit *au = e->access_units;
	struct vidtv_access_unit *sync_au = e->sync->access_units;


	while (au && sync_au) {
		au->pts = sync_au->pts;
		au = au->next;
		sync_au = sync_au->next;
	}
}
