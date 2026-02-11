no_others_quoted_str() {
    String *result = NewString("");
    Printf(result, "\"%s\" :type :%s", name, type);
    if (klass)
      Printf(result, " :class \"%s\"", klass);
    return result;
  }
