class2path(VALUE klass)
{
    VALUE path = rb_class_path(klass);
    const char *n;

    n = must_not_be_anonymous((TYPE(klass) == T_CLASS ? "class" : "module"), path);
    if (rb_path_to_class(path) != rb_class_real(klass)) {
	rb_raise(rb_eTypeError, "%s can't be referred to", n);
    }
    return path;
}
