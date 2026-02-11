iscsit_free_session(struct iscsi_session *sess)
{
	u16 conn_count = atomic_read(&sess->nconn);
	struct iscsi_conn *conn, *conn_tmp = NULL;
	int is_last;

	spin_lock_bh(&sess->conn_lock);
	atomic_set(&sess->sleep_on_sess_wait_comp, 1);

	list_for_each_entry_safe(conn, conn_tmp, &sess->sess_conn_list,
			conn_list) {
		if (conn_count == 0)
			break;

		if (list_is_last(&conn->conn_list, &sess->sess_conn_list)) {
			is_last = 1;
		} else {
			iscsit_inc_conn_usage_count(conn_tmp);
			is_last = 0;
		}
		iscsit_inc_conn_usage_count(conn);

		spin_unlock_bh(&sess->conn_lock);
		iscsit_cause_connection_reinstatement(conn, 1);
		spin_lock_bh(&sess->conn_lock);

		iscsit_dec_conn_usage_count(conn);
		if (is_last == 0)
			iscsit_dec_conn_usage_count(conn_tmp);

		conn_count--;
	}

	if (atomic_read(&sess->nconn)) {
		spin_unlock_bh(&sess->conn_lock);
		wait_for_completion(&sess->session_wait_comp);
	} else
		spin_unlock_bh(&sess->conn_lock);

	target_put_session(sess->se_sess);
	return 0;
}
