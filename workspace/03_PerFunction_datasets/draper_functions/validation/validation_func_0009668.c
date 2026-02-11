simple_action(Packet *p)
{
    if (_length)
	p->set_mac_header(p->data() + _offset, _length);
    else
	p->set_mac_header(p->data() + _offset);
    return p;
}
