exclude_is_line_excluded(
  func_unit* funit,
  int        line
) { PROFILE(EXCLUDE_IS_LINE_EXCLUDED);

  func_iter  fi;
  statement* stmt;

  func_iter_init( &fi, funit, TRUE, FALSE );
  while( ((stmt = func_iter_get_next_statement( &fi )) != NULL) && (stmt->exp->line != line) );
  func_iter_dealloc( &fi );

  PROFILE_END;

  return( (stmt == NULL) || (stmt->suppl.part.excluded == 1) );

}
