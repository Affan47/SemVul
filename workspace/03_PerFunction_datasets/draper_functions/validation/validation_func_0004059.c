env_delete_m(VALUE obj, VALUE name)
{
    VALUE val;

    val = env_delete(obj, name);
    if (NIL_P(val) && rb_block_given_p()) rb_yield(name);
    return val;
}
