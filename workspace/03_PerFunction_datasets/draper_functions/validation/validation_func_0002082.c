CLASS_free(void *object)
{
	CLASS *class = OBJECT_class(object);
	EXEC_GLOBAL save = EXEC;

	void *save_object = _CLASS_free_object;
	void *save_exec = _CLASS_free_exec;

	_CLASS_free_object = object;
	_CLASS_free_exec = &save;

	ON_ERROR(error_CLASS_free)
	{
		((OBJECT *)object)->ref = 1;
		EXEC_special_inheritance(SPEC_FREE, class, object, 0, TRUE);
		((OBJECT *)object)->ref = 0;
		EXEC = save;
		OBJECT_release(class, object);
	}
	END_ERROR

	_CLASS_free_object = save_object;
	_CLASS_free_exec = save_exec;
}
