visit(Bitwise* node)
{
	Node* lhs = node->getLhs();
	Node* rhs = node->getRhs();
	Opcode op = OP_ADD;

	switch (node->getOperator()) {
		case Bitwise::BOP_AND:    op = OP_BW_AND; break;
		case Bitwise::BOP_OR:     op = OP_BW_OR;  break;
		case Bitwise::BOP_XOR:    op = OP_BW_XOR; break;
		case Bitwise::BOP_NOT:    op = OP_BW_NOT; break;
		case Bitwise::BOP_LSHIFT: op = OP_BW_LS;  break;
		case Bitwise::BOP_RSHIFT: op = OP_BW_RS;  break;
	}

	lhs->accept(*this);
	if (rhs) {
		rhs->accept(*this);
	}

	IR& arith = m_builder->push(op, createOp(lhs));

	if (rhs) {
		arith.op2 = createOp(rhs);

		if (node->isAugmented()) {
			arith.result = createOp(lhs);

			node->setVOffset(lhs->getVOffset());
			node->setScope(lhs->getScope());

			return;
		}
	}

	setTempResult(node, arith.result);

	arith.loc = node->getLocation();
}
