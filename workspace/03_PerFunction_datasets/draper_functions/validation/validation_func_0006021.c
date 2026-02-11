at_unset_to() {
    _at->attach_x   = _at->attach_y = _at->to_position_exists = false;
    _at->attach_any = _at->attach_lx || _at->attach_ly;
}
