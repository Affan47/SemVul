pvalCasePatDefWalkStatements( pval *p, pval **statement )
{
	if (!(*statement))
		*statement = p->u2.statements;
	else {
		*statement = (*statement)->next;
	}
	return *statement;
}
