getNofComponents(bool only_emf_components) const
{
  if ( ptrGmtr != NULL )
    return ptrGmtr->getNofComponents(only_emf_components);
  else if ( meshData != NULL )
    return 1;
  else
    return 0;
}
