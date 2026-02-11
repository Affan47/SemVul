val_real()
{
  double nr;

  nr= Item_variance_field::val_real();
  DBUG_ASSERT(nr >= 0.0);
  return sqrt(nr);
}
