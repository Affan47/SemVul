kill_brancher(unsigned int id) {
    if (failed())
      return;
    for (Brancher* b = Brancher::cast(bl.next());
         b != Brancher::cast(&bl); b = Brancher::cast(b->next()))
      if (b->id() == id) {

        if (b_commit == b)
          b_commit = Brancher::cast(b->next());
        if (b_status == b)
          b_status = Brancher::cast(b->next());
        b->unlink();
        rfree(b,b->dispose(*this));
        return;
      }
  }
