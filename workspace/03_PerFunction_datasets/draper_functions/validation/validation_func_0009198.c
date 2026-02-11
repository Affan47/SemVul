AddAngleConstraint(int a, int b, int c, double angle)
  {
    OBFFConstraint constraint;
    constraint.type = OBFF_CONST_ANGLE;
    constraint.ia   = a;
    constraint.ib   = b;
    constraint.ic   = c;
    constraint.constraint_value = angle;
    constraint.factor = _factor;
    _constraints.push_back(constraint);
  }
