StuckNode( nd, val )
  nptr  nd;
  int   val;
  {
    tptr  t;

    if( stuckTrans == NULL ) stuckTrans = init_fault_trans();

    t = stuckTrans;
    if( val == LOW )
      {
	t->ttype = NCHAN;	t->gate = VDD_node;	t->source = GND_node;
      }
    else
      {
	t->ttype = PCHAN;	t->gate = GND_node;	t->source = VDD_node;
      }

    t->drain = nd;
    CONNECT( t->gate->ngate, t );
    CONNECT( nd->nterm, t );
  }
