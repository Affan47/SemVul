parseMap(char next)
{
    switch (next)
    {
	case ']':
	    m_bridge.mapEnd();
	    m_state.pop();
	break;

	case '[':
	    m_state.push(PARSE_MAP);
	    m_state.push(PARSE_MAP_BEGIN);
	    m_state.push(PARSE_NAME);
	break;

	case '(':
	    m_state.push(PARSE_LIST);
	    m_state.push(PARSE_LIST_BEGIN);
	    m_state.push(PARSE_NAME);
	break;

	case '$':
	    m_state.push(PARSE_STRING);
	    m_state.push(PARSE_NAME);
	break;

	case '@':
	    m_state.push(PARSE_INT);
	    m_state.push(PARSE_NAME);
	break;

	case '#':
	    m_state.push(PARSE_FLOAT);
	    m_state.push(PARSE_NAME);
	break;

	default:


	break;
    }
}
