advance(int distance, AdvanceMode mode)
{
  Cursor c = *this;
  if (mode == ByCharacter) {
    while (distance) {
      int lineLength = document()->lineLength(c.line());

      if (distance > 0) {
        int advance = qMin(lineLength - c.column(), distance);

        if (distance > advance) {
          if (c.line() + 1 >= document()->lines())
            return false;

          c.setPosition(c.line() + 1, 0);

          distance -= advance + 1;

        } else {
          c.setColumn(c.column() + distance);
          distance = 0;
        }

      } else {
        int back = qMin(c.column(), -distance);
        if (-distance > back) {
          if (c.line() - 1 < 0)
            return false;

          c.setPosition(c.line() - 1, document()->lineLength(c.line() - 1));

          distance += back + 1;

        } else {
          c.setColumn(c.column() + distance);
          distance = 0;
        }
      }
    }

  } else {

    return false;
  }

  setPosition(c);
  return true;
}
