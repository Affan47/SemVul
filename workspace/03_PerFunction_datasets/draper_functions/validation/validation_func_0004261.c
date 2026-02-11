scm_struct_create_handle (SCM obj)
{
  SCM handle = scm_hash_fn_create_handle_x (scm_struct_table,
					    obj,
					    SCM_BOOL_F,
					    scm_struct_ihashq,
					    scm_sloppy_assq,
					    0);
  if (scm_is_false (SCM_CDR (handle)))
    SCM_SETCDR (handle, scm_cons (SCM_BOOL_F, SCM_BOOL_F));
  return handle;
}
