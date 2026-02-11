parse_lname (const struct parser_table* entry, char **argv, int *arg_ptr)
{
  const char *name;
  fnmatch_sanitycheck();
  if (collect_arg(argv, arg_ptr, &name))
    {
      struct predicate *our_pred = insert_primary (entry);
      our_pred->args.str = name;
      our_pred->est_success_rate = 0.1 * estimate_pattern_match_rate(name, 0);
      return true;
    }
  return false;
}
