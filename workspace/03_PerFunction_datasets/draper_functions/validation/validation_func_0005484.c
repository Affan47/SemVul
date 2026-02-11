DeadCodeElimination(Thread& thread) {
	for(IRef ref = 0; ref < (IRef)nodes.size(); ref++) {
		IRNode& node = nodes[ref];
		if(!node.live) {
			node.op = IROpCode::nop;
			node.arity = IRNode::NULLARY;
			node.group = IRNode::NOP;
		}
	}
}
