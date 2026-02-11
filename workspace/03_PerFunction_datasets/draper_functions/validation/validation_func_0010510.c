strio_s_open(int argc, VALUE *argv, VALUE klass)
{
    VALUE obj = rb_class_new_instance(argc, argv, klass);
    if (!rb_block_given_p()) return obj;
    return rb_ensure(rb_yield, obj, strio_finalize, obj);
}
