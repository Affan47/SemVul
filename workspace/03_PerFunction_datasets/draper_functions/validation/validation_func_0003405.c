geta(int id) {
  if (is_object(id))
    return obj_val();
  else
    return nil;
}
