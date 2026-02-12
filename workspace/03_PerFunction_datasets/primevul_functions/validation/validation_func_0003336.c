ecma_op_container_get_object (ecma_value_t this_arg,
                              lit_magic_string_id_t lit_id)
{
  if (ecma_is_value_object (this_arg))
  {
    ecma_extended_object_t *map_object_p = (ecma_extended_object_t *) ecma_get_object_from_value (this_arg);

    if (ecma_get_object_type ((ecma_object_t *) map_object_p) == ECMA_OBJECT_TYPE_CLASS
        && map_object_p->u.class_prop.class_id == lit_id)
    {
      return map_object_p;
    }
  }

#if ENABLED (JERRY_ERROR_MESSAGES)
  ecma_raise_standard_error_with_format (ECMA_ERROR_TYPE,
                                         "Expected a % object.",
                                         ecma_make_string_value (ecma_get_magic_string (lit_id)));
#else
  ecma_raise_type_error (NULL);
#endif

  return NULL;
}
