addEqualityAxiom ( DLTree* left, DLTree* right )
{

	if ( addNonprimitiveDefinition ( left, right ) )
		return;


	if ( addNonprimitiveDefinition ( right, left ) )
		return;

	if ( switchToNonprimitive ( left, right ) )
		return;

	if ( switchToNonprimitive ( right, left ) )
		return;


	addSubsumeAxiom ( clone(left), clone(right) );
	addSubsumeAxiom ( right, left );
}
