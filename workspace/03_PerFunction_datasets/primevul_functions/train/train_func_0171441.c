int handler::update_auto_increment()
{
  ulonglong nr, nb_reserved_values;
  bool append= FALSE;
  THD *thd= table->in_use;
  struct system_variables *variables= &thd->variables;
  int result=0, tmp;
  DBUG_ENTER("handler::update_auto_increment");


  DBUG_ASSERT(next_insert_id >= auto_inc_interval_for_cur_row.minimum());

  if ((nr= table->next_number_field->val_int()) != 0 ||
      (table->auto_increment_field_not_null &&
       thd->variables.sql_mode & MODE_NO_AUTO_VALUE_ON_ZERO))
  {


    if (thd->is_error())
      DBUG_RETURN(HA_ERR_AUTOINC_ERANGE);


    if ((longlong) nr > 0 || (table->next_number_field->flags & UNSIGNED_FLAG))
      adjust_next_insert_id_after_explicit_value(nr);
    insert_id_for_cur_row= 0;
    DBUG_RETURN(0);
  }

  if (table->versioned())
  {
    Field *end= table->vers_end_field();
    DBUG_ASSERT(end);
    bitmap_set_bit(table->read_set, end->field_index);
    if (!end->is_max())
    {
      if (thd->lex->sql_command == SQLCOM_ALTER_TABLE)
      {
        if (!table->next_number_field->real_maybe_null())
          DBUG_RETURN(HA_ERR_UNSUPPORTED);
        table->next_number_field->set_null();
      }
      DBUG_RETURN(0);
    }
  }


  if (thd->lex->sql_command == SQLCOM_ALTER_TABLE)
    table->next_number_field->set_notnull();

  if ((nr= next_insert_id) >= auto_inc_interval_for_cur_row.maximum())
  {

    const Discrete_interval *forced=
      thd->auto_inc_intervals_forced.get_next();
    if (forced != NULL)
    {
      nr= forced->minimum();
      nb_reserved_values= forced->values();
    }
    else
    {


      ulonglong nb_desired_values;


      if ((auto_inc_intervals_count == 0) && (estimation_rows_to_insert > 0))
        nb_desired_values= estimation_rows_to_insert;
      else if ((auto_inc_intervals_count == 0) &&
               (thd->lex->many_values.elements > 0))
      {


        nb_desired_values= thd->lex->many_values.elements;
      }
      else
      {

        if (auto_inc_intervals_count <= AUTO_INC_DEFAULT_NB_MAX_BITS)
        {
          nb_desired_values= AUTO_INC_DEFAULT_NB_ROWS *
            (1 << auto_inc_intervals_count);
          set_if_smaller(nb_desired_values, AUTO_INC_DEFAULT_NB_MAX);
        }
        else
          nb_desired_values= AUTO_INC_DEFAULT_NB_MAX;
      }
      get_auto_increment(variables->auto_increment_offset,
                         variables->auto_increment_increment,
                         nb_desired_values, &nr,
                         &nb_reserved_values);
      if (nr == ULONGLONG_MAX)
        DBUG_RETURN(HA_ERR_AUTOINC_READ_FAILED);


      nr= compute_next_insert_id(nr-1, variables);
    }

    if (table->s->next_number_keypart == 0)
    {

      append= TRUE;
    }
    else
    {


      DBUG_PRINT("info",("auto_increment: special not-first-in-index"));
    }
  }

  if (unlikely(nr == ULONGLONG_MAX))
      DBUG_RETURN(HA_ERR_AUTOINC_ERANGE);

  DBUG_ASSERT(nr != 0);
  DBUG_PRINT("info",("auto_increment: %llu  nb_reserved_values: %llu",
                     nr, append ? nb_reserved_values : 0));


  {
    Check_level_instant_set check_level_save(thd, CHECK_FIELD_IGNORE);
    tmp= table->next_number_field->store((longlong)nr, TRUE);
  }

  if (unlikely(tmp))
  {


    if (thd->killed == KILL_BAD_DATA ||
        nr > table->next_number_field->get_max_int_value())
    {


      result= HA_ERR_AUTOINC_ERANGE;
    }
    else
    {


      nr= prev_insert_id(table->next_number_field->val_int(), variables);
      if (unlikely(table->next_number_field->store((longlong)nr, TRUE)))
        nr= table->next_number_field->val_int();
    }
  }
  if (append)
  {
    auto_inc_interval_for_cur_row.replace(nr, nb_reserved_values,
                                          variables->auto_increment_increment);
    auto_inc_intervals_count++;

    if (((WSREP(thd) && wsrep_emulate_bin_log ) || mysql_bin_log.is_open())
        && !thd->is_current_stmt_binlog_format_row())
      thd->auto_inc_intervals_in_cur_stmt_for_binlog.
        append(auto_inc_interval_for_cur_row.minimum(),
               auto_inc_interval_for_cur_row.values(),
               variables->auto_increment_increment);
  }


  insert_id_for_cur_row= nr;

  if (result)
    DBUG_RETURN(result);


  set_next_insert_id(compute_next_insert_id(nr, variables));

  DBUG_RETURN(0);
}
