void Item_func_nullif::print(String *str, enum_query_type query_type)
{


  if ((query_type & QT_ITEM_ORIGINAL_FUNC_NULLIF) ||
      (arg_count == 2) ||
      (args[0] == args[2]))
  {


    DBUG_ASSERT(arg_count == 2 ||
                args[0] == args[2] || current_thd->lex->context_analysis_only);
    str->append(func_name());
    str->append('(');
    if (arg_count == 2)
      args[0]->print(str, query_type);
    else
      args[2]->print(str, query_type);
    str->append(',');
    args[1]->print(str, query_type);
    str->append(')');
  }
  else
  {


    str->append(STRING_WITH_LEN("(case when "));
    args[0]->print(str, query_type);
    str->append(STRING_WITH_LEN(" = "));
    args[1]->print(str, query_type);
    str->append(STRING_WITH_LEN(" then NULL else "));
    args[2]->print(str, query_type);
    str->append(STRING_WITH_LEN(" end)"));
  }
}
