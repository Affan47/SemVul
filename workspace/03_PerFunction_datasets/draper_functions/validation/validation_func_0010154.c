inf_adopted_state_vector_from_string_diff(const gchar* str,
                                          InfAdoptedStateVector* orig,
                                          GError** error)
{
  InfAdoptedStateVector* vec;
  gsize vec_pos;
  gsize orig_pos;
  InfAdoptedStateVectorComponent* vec_comp;
  InfAdoptedStateVectorComponent* orig_comp;

  g_return_val_if_fail(str != NULL, NULL);
  g_return_val_if_fail(orig != NULL, NULL);

  vec = inf_adopted_state_vector_from_string(str, error);
  if(vec == NULL) return NULL;

  vec_pos = 0;

  for(orig_pos = 0; orig_pos < orig->size; ++orig_pos)
  {
    orig_comp = orig->data + orig_pos;
    if(orig_comp->n == 0) continue;

    if(vec_pos == vec->size)
    {
      inf_adopted_state_vector_insert(
        vec,
        orig_comp->id,
        orig_comp->n,
        vec_pos
      );
    }
    else
    {
      vec_comp = vec->data + vec_pos;
      while(vec_comp->id < orig_comp->id)
      {
        ++vec_pos;
        if(vec_pos < vec->size)
        {
          vec_comp = vec->data + vec_pos;
        }
        else
        {
          break;
        }
      }

      if(vec_comp->id == orig_comp->id)
      {
        vec_comp->n += orig_comp->n;
        ++vec_pos;
      }
      else
      {
        inf_adopted_state_vector_insert(
          vec,
          orig_comp->id,
          orig_comp->n,
          vec_pos
        );
      }
    }
  }

  return vec;
}
