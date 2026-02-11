optimize()
{
	foreach( Predicate *predicate, m_predicates ) {
		predicate->optimize();
	}
}
