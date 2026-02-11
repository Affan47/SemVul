VasySimulateVexSum( Expr )

  vexexpr *Expr;
{
  vasysimul        *SimulExpr1;
  vasysimul        *SimulExpr2;
  chain_list     *ScanChain;
  vexexpr        *Operand;
  long            Oper;

  Oper = GetVexOperValue( Expr );

  ScanChain = Expr->OPERAND;
  Operand   = GetVexOperand( ScanChain );
  SimulExpr1 = VasySimulateVex( Operand );
  ScanChain = ScanChain->NEXT;

  while ( ScanChain != (chain_list *)0 )
  {
    Operand   = GetVexOperand( ScanChain );
    SimulExpr2 = VasySimulateVex( Operand );

    if ( Oper == VEX_SUB )
    {
      SimulExpr2 = VasySimulateNegSimul( SimulExpr2 );
    }

    SimulExpr1 = VasySimulateSumSimul( SimulExpr1, SimulExpr2 );

    ScanChain = ScanChain->NEXT;
  }

  return( SimulExpr1 );
}
