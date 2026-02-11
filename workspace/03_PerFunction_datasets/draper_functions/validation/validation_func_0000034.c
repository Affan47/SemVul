primitive_dll_validp() {
  cell library = ctx->peek();
  if (to_boolean(library))
    ctx->replace(tag_boolean(untag_check<dll>(library)->handle != NULL));
  else
    ctx->replace(true_object);
}
