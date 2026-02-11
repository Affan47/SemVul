_is_writable(eio_obj_t *obj)
{
	return (obj->ops->writable && (*obj->ops->writable)(obj));
}
