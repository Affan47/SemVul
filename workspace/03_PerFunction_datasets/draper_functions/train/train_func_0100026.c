worklist_peek_ith(const struct worklist *pwl,
		       struct universal *prod, int idx)
{

  if (idx < 0 || pwl->length <= idx) {
    prod->kind = VUT_NONE;
    prod->value.building = NULL;
    return FALSE;
  }

  *prod = pwl->entries[idx];

  return TRUE;
}
