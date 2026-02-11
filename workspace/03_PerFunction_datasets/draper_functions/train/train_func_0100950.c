rb_dlcfunc_new(void (*func)(), int type, const char *name, ID calltype)
{
    VALUE val;
    struct cfunc_data *data;

    rb_secure(4);
    if( func ){
	val = TypedData_Make_Struct(rb_cDLCFunc, struct cfunc_data, &dlcfunc_data_type, data);
	data->ptr  = (void *)(VALUE)func;
	data->name = name ? strdup(name) : NULL;
	data->type = type;
	data->calltype = calltype;
    }
    else{
	val = Qnil;
    }

    return val;
}
