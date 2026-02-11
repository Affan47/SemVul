set_storage_via_libcall (rtx object, rtx size, rtx val, bool tailcall)
{
  tree call_expr, fn, object_tree, size_tree, val_tree;
  enum machine_mode size_mode;
  rtx retval;


  object = copy_to_mode_reg (Pmode, XEXP (object, 0));

  size_mode = TYPE_MODE (sizetype);
  size = convert_to_mode (size_mode, size, 1);
  size = copy_to_mode_reg (size_mode, size);


  object_tree = make_tree (ptr_type_node, object);
  if (!CONST_INT_P (val))
    val = convert_to_mode (TYPE_MODE (integer_type_node), val, 1);
  size_tree = make_tree (sizetype, size);
  val_tree = make_tree (integer_type_node, val);

  fn = clear_storage_libcall_fn (true);
  call_expr = build_call_expr (fn, 3, object_tree, val_tree, size_tree);
  CALL_EXPR_TAILCALL (call_expr) = tailcall;

  retval = expand_normal (call_expr);

  return retval;
}
