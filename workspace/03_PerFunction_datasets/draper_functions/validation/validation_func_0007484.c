rb_struct_getmember(obj, id)
    VALUE obj;
    ID id;
{
    VALUE members, slot;
    long i;

    members = rb_struct_members(obj);
    slot = ID2SYM(id);
    for (i=0; i<RARRAY(members)->len; i++) {
	if (RARRAY(members)->ptr[i] == slot) {
	    return RSTRUCT(obj)->ptr[i];
	}
    }
    rb_name_error(id, "%s is not struct member", rb_id2name(id));
    return Qnil;
}
