newFalseBody(PrgBodyNode* body, uint32 oldHash) {
	body->clearLiteral(true); body->setIgnore(true);
	for (HeadVec::const_iterator it = body->heads_begin(), end = body->heads_end(); it != end; ++it) {
		setSimplifyBodies(it->node());
	}
	removeFromIndex(body, oldHash);
}
