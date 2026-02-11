path_each_entry(VALUE self)
{
    VALUE args[1];

    args[0] = get_strpath(self);
    return rb_block_call(rb_cDir, rb_intern("foreach"), 1, args, each_entry_i, rb_obj_class(self));
}
