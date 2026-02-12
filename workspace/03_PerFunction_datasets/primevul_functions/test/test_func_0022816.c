void LEX::reset_n_backup_query_tables_list(Query_tables_list *backup)
{
  backup->set_query_tables_list(this);


  this->reset_query_tables_list(TRUE);
}
