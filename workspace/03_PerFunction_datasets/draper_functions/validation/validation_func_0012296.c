print( std::ostream& os, const TermTable& terms ) const
{
  os << '(' << name();
  for( ObjectList::const_iterator oi = arguments_.begin();
                                                  oi != arguments_.end(); ++oi )
    {
      os << ' ';
      terms.print_term( os, *oi );
    }
  os << ')';
}
