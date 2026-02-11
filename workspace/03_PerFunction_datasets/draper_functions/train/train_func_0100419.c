AjouteFin ( int Som, struct Liste * L )
{
	struct Chainon * C = ( struct Chainon * ) malloc ( sizeof ( struct Chainon ) );

	C->Sommet = Som ;
	C->suiv = NULL ;

	if ( L->der )
		L->der->suiv = C ;
	else
		L->prems = C ;

	L->der = C;

	return ;
}
