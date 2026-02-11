init( const Spacegroup& spacegroup, const Cell& cell, const Resolution& resolution, const bool& generate )
{

  const Spacegroup* sp = &spacegroup;
  const Cell* cp = &cell;
  const Resolution* rp = &resolution;

  if ( sp->is_null() ) sp = parent_of_type_ptr<const Spacegroup>();
  if ( cp->is_null() ) cp = parent_of_type_ptr<const Cell>();
  if ( rp->is_null() ) rp = parent_of_type_ptr<const Resolution>();
  generate_ = generate_ | generate;

  if ( sp != NULL && cp != NULL && rp != NULL )
    if ( !sp->is_null() && !cp->is_null() && !rp->is_null() )
      HKL_info::init( *sp, *cp, *rp, generate_ );
  Container::update();
}
