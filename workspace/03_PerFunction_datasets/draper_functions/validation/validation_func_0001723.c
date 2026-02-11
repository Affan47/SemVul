pointer_set_traverse (const struct pointer_set_t *pset,
			   bool (*fn) (const void *, void *), void *data)
{
  size_t i;
  for (i = 0; i < pset->n_slots; ++i)
    if (pset->slots[i] && !fn (pset->slots[i], data))
      break;
}
