shape_update()
{
  Region **regions = domain->regions;
  for (int ilist = 0; ilist < nregion; ilist++)
    regions[list[ilist]]->shape_update();
}
