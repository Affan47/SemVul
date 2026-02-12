ecma_op_container_create_iterator (ecma_value_t this_arg,
                                   uint8_t type,

                                   lit_magic_string_id_t lit_id,
                                   ecma_builtin_id_t proto_id,
                                   ecma_pseudo_array_type_t iterator_type)
{
  ecma_extended_object_t *map_object_p = ecma_op_container_get_object (this_arg, lit_id);

  if (map_object_p == NULL)
  {
    return ECMA_VALUE_ERROR;
  }

  return ecma_op_create_iterator_object (this_arg,
                                         ecma_builtin_get (proto_id),
                                         (uint8_t) iterator_type,
                                         type);
}
