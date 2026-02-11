simple_action(Packet *p)
{
    if (p->length() > _nbytes) {
	unsigned nbytes = p->length() - _nbytes;
	if (_extra_anno)
	    SET_EXTRA_LENGTH_ANNO(p, EXTRA_LENGTH_ANNO(p) + nbytes);
        p->take(nbytes);
    }
    return p;
}
