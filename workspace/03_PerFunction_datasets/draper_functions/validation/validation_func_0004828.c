init1dtab ( t4tab *p0, dtab *t1, dtab *t2, dtab *ot )
{
  t4tab *p ;
  for ( p = p0 ; p->code ; p++ )
    if ( p->bits <= 9 ) {
      addcode ( t1, p->code, 9 - p->bits, p->rlen + 1, p->bits,
	       ( p - p0 ) > 63 ? t1 : ot ) ;
    } else {
      addcode ( t1, p->code >> ( p->bits - 9 ), 0, 0, 4, t2 ) ;
      addcode ( t2, p->code, 13 - p->bits, p->rlen + 1, p->bits - 4,
	       ( p - p0 ) > 63 ? t1 : ot ) ;
    }
}
