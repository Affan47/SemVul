HandleSequence(EventHandler& eventHandler)
	{

		switch(m_scanner.peek().type) {
			case Token::BLOCK_SEQ_START: HandleBlockSequence(eventHandler); break;
			case Token::FLOW_SEQ_START: HandleFlowSequence(eventHandler); break;
			default: break;
		}
	}
