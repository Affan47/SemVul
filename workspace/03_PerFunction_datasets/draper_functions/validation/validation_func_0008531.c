inclinenumber (void)
{
  static char *pragmas [] =
    {"debug", "nodebug", "endinput", "end", "ifnot", "if", "else", NULL};
  next();
  ++lua_linenumber;
  if (current == '$') {
    char buff[PRAGMASIZE+1];
    int ifnot = 0;
    int skip = ifstate[iflevel].skip;
    next();
    readname(buff);
    switch (luaI_findstring(buff, pragmas)) {
      case 0:
        if (!skip) lua_debug = 1;
        break;
      case 1:
        if (!skip) lua_debug = 0;
        break;
      case 2:
        if (!skip) {
          current = EOZ;
          iflevel = 0;
        }
        break;
      case 3:
        if (iflevel-- == 0)
          luaI_auxsyntaxerror("unmatched $endif");
        break;
      case 4:
        ifnot = 1;

      case 5:
        if (iflevel == MAX_IFS-1)
          luaI_auxsyntaxerror("too many nested `$ifs'");
        readname(buff);
        iflevel++;
        ifstate[iflevel].elsepart = 0;
        ifstate[iflevel].condition = checkcond(buff) ? !ifnot : ifnot;
        ifstate[iflevel].skip = skip || !ifstate[iflevel].condition;
        break;
      case 6:
        if (ifstate[iflevel].elsepart)
          luaI_auxsyntaxerror("unmatched $else");
        ifstate[iflevel].elsepart = 1;
        ifstate[iflevel].skip =
                    ifstate[iflevel-1].skip || ifstate[iflevel].condition;
        break;
      default:
        luaI_auxsynterrbf("invalid pragma", buff);
    }
    skipspace();
    if (current == '\n')
      inclinenumber();
    else if (current != EOZ)
      luaI_auxsyntaxerror("invalid pragma format");
    ifskip();
  }
}
