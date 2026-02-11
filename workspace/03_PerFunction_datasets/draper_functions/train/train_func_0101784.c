operator=(const Cldesc &rhs)
{

  if (this != &rhs)
    _description   = rhs._description;
    _start_1st_col = rhs._start_1st_col;

  return *this;
}
