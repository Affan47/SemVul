augment(list<vertex*>& l)
{

  list<vertex*> delQ;

  list<vertex*>::iterator it = l.begin();
  while (it != l.end()) {
    if ((*it)->getPartner()) {
      delQ.push_front((*it));
      it = l.erase(it);
    }
    else
      it++;
  }

  while (!delQ.empty()) {
    vertex* fr = delQ.front();
    delQ.pop_front();
    fr->unLink(delQ);
  }

  if (l.empty()) {
    cout << "-E- No free vertices left!" << endl;
    return;
  }

  while (!l.empty()) {
    vertex* curr = l.front();
    l.pop_front();
    int idx = 0;

    int length=0;
    while (1) {
      delQ.push_front(curr);

      if (!curr->getPredecessor()) {
	if (!idx && length) {
	  cout << "-E- This vertex must have predecessor" << endl;
	  return;
	}
	break;
      }

      curr->flipPredEdge(idx);

      curr = curr->getPredecessor();
      idx = (idx+1)%2;
      length++;
    }

    while (!delQ.empty()) {
      vertex* fr = delQ.front();
      delQ.pop_front();
      fr->unLink(delQ);
    }
  }
}
