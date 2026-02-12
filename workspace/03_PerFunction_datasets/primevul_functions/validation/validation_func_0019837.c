int RGWGetObj_ObjStore_SWIFT::verify_permission()
{
  op_ret = RGWGetObj_ObjStore::verify_permission();


  if (s->auth.identity->is_anonymous() && op_ret == -EACCES) {
    return -EPERM;
  } else {
    return op_ret;
  }
}
