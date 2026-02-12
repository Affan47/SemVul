void lex_end_nops(LEX *lex)
{
  DBUG_ENTER("lex_end_nops");
  sp_head::destroy(lex->sphead);
  lex->sphead= NULL;


  lex->mi.reset(lex->sql_command == SQLCOM_CHANGE_MASTER);
  delete_dynamic(&lex->delete_gtid_domain);

  DBUG_VOID_RETURN;
}
