qla2x00_vp_stop_timer(scsi_qla_host_t *vha)
{
	if (vha->vp_idx && vha->timer_active) {
		del_timer_sync(&vha->timer);
		vha->timer_active = 0;
	}
}
