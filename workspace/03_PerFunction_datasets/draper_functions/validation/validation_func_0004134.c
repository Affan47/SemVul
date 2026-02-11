race_calc_assignments(
  statement* stmt,
  int        sb_index
) { PROFILE(RACE_CALC_ASSIGNMENTS);

  if( (stmt != NULL) && (stmt->conn_id != stmt_conn_id) ) {

    stmt->conn_id = stmt_conn_id;


    if( stmt->suppl.part.stop_true == 0 ) {
      race_calc_assignments( stmt->next_true, sb_index );
    }
    if( (stmt->suppl.part.stop_false == 0) && (stmt->next_true != stmt->next_false) ) {
      race_calc_assignments( stmt->next_false, sb_index );
    }


    race_calc_expr_assignment( stmt->exp, sb_index );

  }

  PROFILE_END;

}
