mrpc_conn_get_counter(struct mrpc_connection *conn,
			enum mrpc_conn_counter counter, uint64_t *result)
{
	if (conn == NULL || result == NULL || (int)counter < 0 ||
				counter >= MRPC_CONNCTR_NR)
		return EINVAL;
	pthread_mutex_lock(&conn->counters_lock);
	*result=conn->counters[counter];
	pthread_mutex_unlock(&conn->counters_lock);
	return 0;
}
