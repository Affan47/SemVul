rb_const_set(VALUE klass, ID id, VALUE val)
{
    rb_const_entry_t *ce;
    VALUE visibility = CONST_PUBLIC;

    if (NIL_P(klass)) {
	rb_raise(rb_eTypeError, "no class/module to define constant %s",
		 rb_id2name(id));
    }

    check_before_mod_set(klass, id, val, "constant");
    if (!RCLASS_CONST_TBL(klass)) {
	RCLASS_CONST_TBL(klass) = st_init_numtable();
    }
    else {
	st_data_t value;

	if (st_lookup(RCLASS_CONST_TBL(klass), (st_data_t)id, &value)) {
	    rb_const_entry_t *ce = (rb_const_entry_t*)value;
	    if (ce->value == Qundef)
		autoload_delete(klass, id);
	    else {
		visibility = ce->flag;
		rb_warn("already initialized constant %s", rb_id2name(id));
	    }
	}
    }

    rb_vm_change_state();

    ce = ALLOC(rb_const_entry_t);
    ce->flag = (rb_const_flag_t)visibility;
    ce->value = val;

    st_insert(RCLASS_CONST_TBL(klass), (st_data_t)id, (st_data_t)ce);
}
