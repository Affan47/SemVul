parse_plusminus_unit_test(GtError *err)
{
  int had_err = 0;
  bool destination;
  gt_ensure(had_err, parse_plusminus(&destination, "+") == 0);
  gt_ensure(had_err, destination);
  gt_ensure(had_err, parse_plusminus(&destination, "-") == 0);
  gt_ensure(had_err, !destination);
  gt_ensure(had_err, parse_plusminus(&destination, "xy") != 0);
  gt_ensure(had_err, parse_plusminus(&destination, "x") != 0);
  gt_ensure(had_err, parse_plusminus(&destination, "") != 0);
  return had_err;
}
