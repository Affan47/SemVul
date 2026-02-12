static void statement (LexState *ls) {
  int line = ls->linenumber;
  enterlevel(ls);
  switch (ls->t.token) {
    case ';': {
      luaX_next(ls);
      break;
    }
    case TK_IF: {
      ifstat(ls, line);
      break;
    }
    case TK_WHILE: {
      whilestat(ls, line);
      break;
    }
    case TK_DO: {
      luaX_next(ls);
      block(ls);
      check_match(ls, TK_END, TK_DO, line);
      break;
    }
    case TK_FOR: {
      forstat(ls, line);
      break;
    }
    case TK_REPEAT: {
      repeatstat(ls, line);
      break;
    }
    case TK_FUNCTION: {
      funcstat(ls, line);
      break;
    }
    case TK_LOCAL: {
      luaX_next(ls);
      if (testnext(ls, TK_FUNCTION))
        localfunc(ls);
      else
        localstat(ls);
      break;
    }
    case TK_DBCOLON: {
      luaX_next(ls);
      labelstat(ls, str_checkname(ls), line);
      break;
    }
    case TK_RETURN: {
      luaX_next(ls);
      retstat(ls);
      break;
    }
    case TK_BREAK: {
      breakstat(ls);
      break;
    }
    case TK_GOTO: {
      luaX_next(ls);
      gotostat(ls);
      break;
    }
    default: {
      exprstat(ls);
      break;
    }
  }
  lua_assert(ls->fs->f->maxstacksize >= ls->fs->freereg &&
             ls->fs->freereg >= luaY_nvarstack(ls->fs));
  ls->fs->freereg = luaY_nvarstack(ls->fs);
  leavelevel(ls);
}
