sq_getclass(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr *o = NULL;
	_GETSAFE_OBJ(v, idx, OT_INSTANCE,o);
	v->Push(SQObjectPtr(_instance(*o)->_class));
	return SQ_OK;
}
