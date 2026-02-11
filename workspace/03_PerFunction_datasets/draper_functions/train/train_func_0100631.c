wait_status_all(struct dlm_ls *ls, uint32_t wait_status,
			   int save_slots)
{
	struct dlm_rcom *rc = ls->ls_recover_buf;
	struct dlm_member *memb;
	int error = 0, delay;

	list_for_each_entry(memb, &ls->ls_nodes, list) {
		delay = 0;
		for (;;) {
			if (dlm_recovery_stopped(ls)) {
				error = -EINTR;
				goto out;
			}

			error = dlm_rcom_status(ls, memb->nodeid, 0);
			if (error)
				goto out;

			if (save_slots)
				dlm_slot_save(ls, rc, memb);

			if (rc->rc_result & wait_status)
				break;
			if (delay < 1000)
				delay += 20;
			msleep(delay);
		}
	}
 out:
	return error;
}
