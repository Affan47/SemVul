mini_is_gsharedvt_gparam (MonoType *t)
{

	return (t->type == MONO_TYPE_VAR || t->type == MONO_TYPE_MVAR) && t->data.generic_param->gshared_constraint && t->data.generic_param->gshared_constraint->type == MONO_TYPE_VALUETYPE;
}
