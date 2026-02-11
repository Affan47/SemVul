OtherFrame(int other_frame) {
  delete _prev_others;
  _prev_others = _curr_others;
  _num_prev_others = _num_curr_others;
  _curr_others = new int[1];
  _curr_others[0] = other_frame;
  _num_curr_others = 1;
}
