rel(Home home, SetVar x, SetOpType op, SetVar y, SetRelType r,
      const IntSet& z) {
    Set::Limits::check(z, "Set::rel");
    ConstSetView zv(home, z);
    if (r == SRT_CMPL) {
      post_compl(home, x, op, y, zv);
    } else {
      post_nocompl(home, x, op, y, r, zv);
    }
  }
}
