undo_memory_destroy (UNDO_MEMORY * memory)
{
  if (memory == NULL)
    UNDO_ERROR (UNDO_BADPARAM);

  undo_memory_clear (memory);
  free (memory);

  UNDO_SUCCESS;
}
