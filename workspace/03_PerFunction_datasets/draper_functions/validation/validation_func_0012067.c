parseList(char next)
{
    switch (next)
    {
	case ')':
	    m_bridge.listEnd();
	    m_state.pop();
	break;

	case '[':
	    m_bridge.listMapItem();
	    m_state.push(PARSE_MAP);
	break;

	case '(':
	    m_bridge.listListItem();
	    m_state.push(PARSE_LIST);
	break;

	case '$':
	    m_state.push(PARSE_STRING);
	break;

	case '@':
	    m_state.push(PARSE_INT);
	break;

	case '#':
	    m_state.push(PARSE_FLOAT);
	break;

	default:


	break;
    }
}
