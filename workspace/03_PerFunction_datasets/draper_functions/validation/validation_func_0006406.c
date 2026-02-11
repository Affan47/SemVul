AddToQueue(Workq* q, int id, uint flag) {


  int* stk = astack_;
  int nstk = 0;

  stk[nstk++] = id;
  while (nstk > 0) {
    DCHECK_LE(nstk, nastack_);
    id = stk[--nstk];

    if (id == Mark) {
      q->mark();
      continue;
    }

    if (id == 0)
      continue;


    if (q->contains(id))
      continue;
    q->insert_new(id);


    Prog::Inst* ip = prog_->inst(id);
    switch (ip->opcode()) {
      case kInstFail:
        break;

      case kInstByteRange:
      case kInstMatch:
        break;

      case kInstCapture:
      case kInstNop:
        stk[nstk++] = ip->out();
        break;

      case kInstAlt:
      case kInstAltMatch:


        stk[nstk++] = ip->out1();
        if (q->maxmark() > 0 &&
            id == prog_->start_unanchored() && id != prog_->start())
          stk[nstk++] = Mark;
        stk[nstk++] = ip->out();
        break;

      case kInstEmptyWidth:
        if ((ip->empty() & flag) == ip->empty())
          stk[nstk++] = ip->out();
        break;
    }
  }
}
