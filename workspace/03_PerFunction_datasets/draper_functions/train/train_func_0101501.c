dumpCExpression ( dumpInterface* dump, const DLTree* C )
{
	if ( C == NULL )
		return;

	Token t = C->Element().getToken();
	diOp tag;

	switch (t)
	{
	case TOP:
		return dump->dumpTop();
	case BOTTOM:
		return dump->dumpBottom();
	case CNAME:
	case INAME:
		return dump->dumpConcept(static_cast<TConcept*>(C->Element().getNE()));
	case NOT:
		dump->startOp(diNot);
		dumpCExpression ( dump, C->Left() );
		return dump->finishOp(diNot);
	case AND:
	case OR:
		tag = t == AND ? diAnd : diOr;
		dump->startOp(tag);
		dumpCExpression ( dump, C->Left() );
		dump->contOp(tag);
		dumpCExpression ( dump, C->Right() );
		return dump->finishOp(tag);

	case EXISTS:
	case FORALL:
	case LE:
	case GE:
		tag = t == EXISTS ? diExists : t == FORALL ? diForall : t == GE ? diGE : diLE;
		if ( t == GE || t == LE )
			dump->startOp ( tag, C->Element().getData() );
		else
			dump->startOp(tag);
		dumpRExpression ( dump, C->Left() );
		dump->contOp(tag);
		dumpCExpression ( dump, C->Right() );
		return dump->finishOp(tag);
	default:
		fpp_unreachable();
	}
}
