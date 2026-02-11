is_gsharedvt_type (MonoType *t)
{
	return (t->type == MONO_TYPE_VAR || t->type == MONO_TYPE_MVAR) && t->data.generic_param->serial == 1;
}
