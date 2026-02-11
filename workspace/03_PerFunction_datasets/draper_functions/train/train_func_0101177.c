get_affected_vars( std::set<ushort_t>* setAffectedVars ) const
{
  for( size_t i = 0; i < add_list().size(); ++i )
    {
      setAffectedVars->insert(add_list().atom( i ));
    }

  for( size_t i = 0; i < del_list().size(); ++i )
    {
      setAffectedVars->insert(del_list().atom( i ));
    }
}
