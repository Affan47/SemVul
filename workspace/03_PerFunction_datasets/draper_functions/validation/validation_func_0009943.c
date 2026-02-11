w_obj_each(ID id, VALUE value, struct dump_call_arg *arg)
{
    if (id == rb_id_encoding()) return ST_CONTINUE;
    if (id == rb_intern("E")) return ST_CONTINUE;
    w_symbol(id, arg->arg);
    w_object(value, arg->arg, arg->limit);
    return ST_CONTINUE;
}
