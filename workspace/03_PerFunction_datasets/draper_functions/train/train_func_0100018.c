general_plist_writer (object type)
{
  CHECK_TYPE(STACK_1,type);
  { object new_value = popSTACK();
    pushSTACK(O(object_xlib__plist));
    pushSTACK(new_value);
    funcall (L(set_slot_value), 3);
  }
}
