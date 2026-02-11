normalize_to_tf( const Expr& e, TReturn*& t1, int y )
{
  int chOp = t1->getLFSCProof()->getChOp();
  if( t1->getProvesY()!=1 ){
    ostringstream ose;
    ose << "Bad mode for norm to tf " << t1->getProvesY() << std::endl;
    print_error( ose.str().c_str(), cout );
  }
  std::vector< int > emptyL;
  std::vector< int > emptyLUsed;
  t1->getL( emptyL, emptyLUsed );

  if( t1->getLFSCProof()->AsLFSCLraPoly() && false )
  {
#ifdef PRINT_MAJOR_METHODS
    cout << ";[M]: Normalize 1 to " << y << ", simplify case" << std::endl;
#endif
    t1 = new TReturn( t1->getLFSCProof()->getChild( 0 ), emptyL, emptyLUsed, nullRat, false, y );
  }
  else
  {

#ifdef PRINT_MAJOR_METHODS
    cout << ";[M]: Normalize 1 to " << y << ", iff/impl, atom" << std::endl;
#endif

    Expr eatom = queryAtomic( e );
    int val = queryM( e );
    int knd = eatom.getKind();


    RefPtr< LFSCProof > p = LFSCPfVar::Make( "@v", abs( val ) );

    Expr ea = Expr( NOT, e );
    p = LFSCLraPoly::Make( ea, p.get() );

    p = LFSCLraContra::Make(
          LFSCLraAdd::Make( p.get(), t1->getLFSCProof(),
                            get_normalized( knd, (val<0) ),
                            get_normalized( knd, !(val<0) ) ),
          is_comparison( knd ) ? (int)GT : (int)DISTINCT );

    p = LFSCAssume::Make( val, p.get(), false, 1 );


    t1 = new TReturn( p.get(), emptyL, emptyLUsed, nullRat, false, y );
  }
  t1->getLFSCProof()->setChOp( chOp );
}
