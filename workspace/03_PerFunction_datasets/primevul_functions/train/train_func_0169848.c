void Item_trigger_field::set_required_privilege(bool rw)
{


  want_privilege= (rw ? SELECT_ACL | UPDATE_ACL : UPDATE_ACL);
}
