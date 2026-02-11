delbddnode( BddSystem, BddNode )

  bddsystem *BddSystem;
  bddnode   *BddNode;
{
  long NumberNode;

  setbddlocalsystem( BddSystem );

  NumberNode = BddLocalSystem->NUMBER_NODE;

  loc_delbdd( BddNode );

  if ( BddLocalSystem->NUMBER_NODE < NumberNode )
  {
    resetbddhopertable( BddLocalSystem->HASH_OPER );
  }
}
