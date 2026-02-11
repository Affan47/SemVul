kf_move_up_and_sol() {
  if (line_start(position())==position() && position()>0)
    return shift_position(line_start(position()-1)) + NORMAL_INPUT_MOVE;
  else
    return shift_position(line_start(position())) + NORMAL_INPUT_MOVE;
}
