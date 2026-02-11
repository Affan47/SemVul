min_reset_ref()
{
  int itmp,itmpall;
  itmpall = 0;
  for (int i = 0; i < n_min_energy; i++) {
    itmp = fix[list_min_energy[i]]->min_reset_ref();
    if (itmp) itmpall = 1;
  }
  return itmpall;
}
