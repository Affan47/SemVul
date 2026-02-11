ql_loopback_test(struct ql_adapter *qdev, u64 *data)
{
	*data = ql_start_loopback(qdev);
	if (*data)
		goto out;
	*data = ql_run_loopback_test(qdev);
out:
	ql_stop_loopback(qdev);
	return *data;
}
