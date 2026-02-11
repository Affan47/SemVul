mergeSorts ( TRole* R )
{

	R->mergeSupersDomain();
	merge ( R->getDomainLabel(), R->getBPDomain() );

	for ( TRole::const_iterator q = R->begin_topfunc(), q_end = R->end_topfunc(); q != q_end; ++q )
		merge ( R->getDomainLabel(), (*q)->getFunctional() );
}
