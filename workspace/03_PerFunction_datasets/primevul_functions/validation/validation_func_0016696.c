static void
php_mysqlnd_rowp_free_mem(void * _packet, zend_bool stack_allocation TSRMLS_DC)
{
	MYSQLND_PACKET_ROW *p;

	DBG_ENTER("php_mysqlnd_rowp_free_mem");
	p = (MYSQLND_PACKET_ROW *) _packet;
	if (p->row_buffer) {
		p->row_buffer->free_chunk(p->row_buffer TSRMLS_CC);
		p->row_buffer = NULL;
	}
	DBG_INF_FMT("stack_allocation=%u persistent=%u", (int)stack_allocation, (int)p->header.persistent);


	if (!stack_allocation) {
		mnd_pefree(p, p->header.persistent);
	}
	DBG_VOID_RETURN;
}
