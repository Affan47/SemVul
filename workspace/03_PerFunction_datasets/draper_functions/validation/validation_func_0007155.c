replace_blank_ports(RouterT *r)
{
  ElementT *idle = 0;
  int idle_next_in = 0, idle_next_out = 0;
  for (RouterT::iterator x = r->begin_elements(); x; x++) {
    Vector<int> connv;

    r->find_connection_vector_to(x, connv);
    connv.resize(element_ninputs[x->name()], -1);
    for (int p = 0; p < connv.size(); p++)
      if (connv[p] == -1) {
	if (!idle)
	  idle = r->add_anon_element(idlet, "", LandmarkT("<click-undead>"));
	r->add_connection(idle, idle_next_out++, x, p);
      }

    r->find_connection_vector_from(x, connv);
    connv.resize(element_noutputs[x->name()], -1);
    for (int p = 0; p < connv.size(); p++)
      if (connv[p] == -1) {
	if (!idle)
	  idle = r->add_anon_element(idlet, "", LandmarkT("<click-undead>"));
	r->add_connection(x, p, idle, idle_next_in++);
      }
  }
}
