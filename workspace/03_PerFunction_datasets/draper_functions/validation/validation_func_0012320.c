suitable_reference_p (struct data_reference *a, enum ref_step_type *ref_step)
{
  tree ref = DR_REF (a), step = DR_STEP (a);

  if (!step
      || !is_gimple_reg_type (TREE_TYPE (ref))
      || tree_could_throw_p (ref))
    return false;

  if (integer_zerop (step))
    *ref_step = RS_INVARIANT;
  else if (integer_nonzerop (step))
    *ref_step = RS_NONZERO;
  else
    *ref_step = RS_ANY;

  return true;
}
