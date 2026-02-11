sq_getweakrefval(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &o = stack_get(v,idx);
	if(type(o) != OT_WEAKREF) {
		return sq_throwerror(v,_SC("the object must be a weakref"));
	}
	v->Push(_weakref(o)->_obj);
	return SQ_OK;
}
