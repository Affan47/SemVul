Resize() {
    register BoxElement* e;
    Shape aggrshape;
    BoxCanonical total;
    int major, minor;
    register int have;
    register int need;
    boolean grow;
    BoxCanonical s;
    register int pos;
    register int len;
    register int n;

    ComputeShape(&aggrshape);
    GetActual(major, minor);
    GetCanonical(&aggrshape, total);
    n = total.major.natural;
    if (major > n) {

	grow = true;
	have = total.major.stretch;
	need = Math::min(major - n, have);
    } else {

	grow = false;
	have = total.major.shrink;
	need = Math::min(n - major, have);
    }
    pos = 0;
    for (e = head; e != nil; e = e->next) {
	GetCanonical(e->child->GetShape(), s);
	len = s.major.natural;
	if (have > 0) {
	    if (grow) {
		n = int(double(s.major.stretch)*double(need)/double(have));
		len += n;
		have -= s.major.stretch;
	    } else {
		n = int(double(s.major.shrink)*double(need)/double(have));
		len -= n;
		have -= s.major.shrink;
	    }
	    need -= n;
	}
	n = s.minor.natural;
	if (n == 0) {
	    n = minor;
	} else if (n > minor) {
	    n = Math::max(n - s.minor.shrink, minor);
	} else if (n < minor) {
	    n = Math::min(n + s.minor.stretch, minor);
	}
	if (n > 0 && len > 0) {
	    e->visible = true;
	    PlaceElement(e->child, pos, len, minor, n);
	} else {
	    e->visible = false;
	}
	pos += len;
    }
}
