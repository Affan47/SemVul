selectedBackground( ) const
{
  if (hasProperty(SelectedBackground))
    return qVariantValue<QBrush>(properties()[SelectedBackground]);

  return QBrush();
}
