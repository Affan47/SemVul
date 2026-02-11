each_value_i(key, value)
    VALUE key, value;
{
    if (key == Qundef) return ST_CONTINUE;
    rb_yield(value);
    return ST_CONTINUE;
}
