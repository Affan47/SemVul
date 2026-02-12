void php_request_shutdown_for_exec(void *dummy)
{


	shutdown_memory_manager(1, 1);
	zend_interned_strings_restore();
}
