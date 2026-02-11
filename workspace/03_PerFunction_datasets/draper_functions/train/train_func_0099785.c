free_connection(ConnectionX *c)
{
    *c->_pprev = c->_next[end_all];
    if (c->_next[end_all])
	c->_next[end_all]->_pprev = c->_pprev;
    if (_conn_tail == &c->_next[end_all])
	_conn_tail = c->_pprev;
    c->_next[0] = _free_conn;
    _free_conn = c;
}
