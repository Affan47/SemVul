alloc_globals_ctor(zend_alloc_globals *alloc_globals TSRMLS_DC)
{
	char *tmp = getenv("USE_ZEND_ALLOC");

	if (tmp && !zend_atoi(tmp, 0)) {
		alloc_globals->mm_heap = malloc(sizeof(struct _zend_mm_heap));
		memset(alloc_globals->mm_heap, 0, sizeof(struct _zend_mm_heap));
		alloc_globals->mm_heap->use_zend_alloc = 0;
		alloc_globals->mm_heap->_malloc = malloc;
		alloc_globals->mm_heap->_free = free;
		alloc_globals->mm_heap->_realloc = realloc;
	} else {
		alloc_globals->mm_heap = zend_mm_startup();
	}
}
