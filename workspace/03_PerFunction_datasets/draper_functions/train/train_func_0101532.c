bind_display_list() {

  exp_bind* curr;

  curr = eb_head;

  printf( "Expression binding list:\n" );

  while( curr != NULL ) {

    switch( curr->type ) {
      case FUNIT_AFUNCTION :
      case FUNIT_FUNCTION :
        printf( "  Expr: %d, %s, line %d;  Functional Unit: %s;  Function: %s\n",
                curr->exp->id, expression_string_op( curr->exp->op ), curr->exp->line,
                obf_funit( curr->funit->name ), obf_sig( curr->name ) );
        break;
      case FUNIT_ATASK :
      case FUNIT_TASK :
        printf( "  Expr: %d, %s, line %d;  Functional Unit: %s;  Task: %s\n",
                curr->exp->id, expression_string_op( curr->exp->op ), curr->exp->line,
                obf_funit( curr->funit->name ), obf_sig( curr->name ) );
        break;
      case FUNIT_ANAMED_BLOCK :
      case FUNIT_NAMED_BLOCK :
        printf( "  Expr: %d, %s, line %d;  Functional Unit: %s;  Named Block: %s\n",
                curr->exp->id, expression_string_op( curr->exp->op ), curr->exp->line,
                obf_funit( curr->funit->name ), obf_sig( curr->name ) );
        break;
      case 0 :
        if( curr->clear_assigned > 0 ) {
          printf( "  Signal to be cleared: %s\n", obf_sig( curr->name ) );
        } else {
          printf( "  Expr: %d, %s, line %d;  Functional Unit: %s;  Signal: %s\n",
                  curr->exp->id, expression_string_op( curr->exp->op ), curr->exp->line,
                  obf_funit( curr->funit->name ), obf_sig( curr->name ) );
        }
        break;
      default :  break;
    }

    curr = curr->next;

  }

}
