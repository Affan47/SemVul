spiciralloue( cir, taille )
circuit		*cir;
int		 taille;
{
  void		*pt;

  if(!cir)
  {
    fflush( stdout );
    fprintf( stderr, "*** mbkspi internal error *** : spiciralloue()\n" );
    EXIT(1);
  }

  pt = mbkalloc( taille );
  cir->FREE = addchain( cir->FREE, pt );
  cir->TAILLE = cir->TAILLE + taille ;
  return( pt );
}
