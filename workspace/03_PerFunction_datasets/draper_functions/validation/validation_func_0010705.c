makeEngine(ExecState *exec, const UString &p, JSValue *flagsInput)
{
  int reflags = RegExp::None;

  if (!flagsInput->isUndefined()) {
    const UString flags = flagsInput->toString(exec);


    for (int pos = 0; pos < flags.size(); ++pos) {
      switch (flags[pos].unicode()) {
      case 'g':
        if (reflags & RegExp::Global) {
          throwError(exec, SyntaxError,
                     "Regular expression flag 'g' given twice", 1, -1, "<regexp>");
          return 0;
        }
        reflags |= RegExp::Global;
        break;
      case 'i':
        if (reflags & RegExp::IgnoreCase) {
          throwError(exec, SyntaxError,
                     "Regular expression flag 'i' given twice", 1, -1, "<regexp>");
          return 0;
        }
        reflags |= RegExp::IgnoreCase;
        break;
      case 'm':
        if (reflags & RegExp::Multiline) {
          throwError(exec, SyntaxError,
                     "Regular expression flag 'm' given twice", 1, -1, "<regexp>");
          return 0;
        }
        reflags |= RegExp::Multiline;
        break;
      default: {
          throwError(exec, SyntaxError,
                     "Invalid regular expression flags", 1, -1, "<regexp>");
          return 0;
        }
      }
    }
  }

  RegExp *re = new RegExp(p, reflags);
  if (!re->isValid()) {
    throwError(exec, SyntaxError,
               "Invalid regular expression", 1, -1, "<regexp>");
    delete re;
    return 0;
  }
  return re;
}
