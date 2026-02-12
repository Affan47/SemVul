bool handler::check_table_binlog_row_based_internal(bool binlog_row)
{
  THD *thd= table->in_use;

  return (table->s->can_do_row_logging &&
          thd->is_current_stmt_binlog_format_row() &&


          IF_WSREP(((WSREP_EMULATE_BINLOG(thd) &&
                     wsrep_thd_is_local(thd)) ||
                    ((WSREP(thd) ||
                      (thd->variables.option_bits & OPTION_BIN_LOG)) &&
                     mysql_bin_log.is_open())),
                    (thd->variables.option_bits & OPTION_BIN_LOG) &&
                    mysql_bin_log.is_open()));
}
