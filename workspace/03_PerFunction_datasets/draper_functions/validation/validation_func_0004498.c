binding_dup(VALUE self)
{
    VALUE bindval = binding_alloc(rb_cBinding);
    rb_binding_t *src, *dst;
    GetBindingPtr(self, src);
    GetBindingPtr(bindval, dst);
    dst->env = src->env;
    dst->filename = src->filename;
    dst->line_no = src->line_no;
    return bindval;
}
