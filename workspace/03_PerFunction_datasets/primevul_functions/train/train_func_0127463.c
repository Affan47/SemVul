static void
php_mysqlnd_rowp_free_mem(void * _packet)
{
	MYSQLND_PACKET_ROW *p;

	DBG_ENTER("php_mysqlnd_rowp_free_mem");
	p = (MYSQLND_PACKET_ROW *) _packet;
	if (p->row_buffer.ptr) {
		p->result_set_memory_pool->free_chunk(p->result_set_memory_pool, p->row_buffer.ptr);
		p->row_buffer.ptr = NULL;
	}


	DBG_VOID_RETURN;
}
