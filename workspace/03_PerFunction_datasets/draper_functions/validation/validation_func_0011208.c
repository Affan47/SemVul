getvexexprnumnode( Expr )

  vexexpr *Expr;
{
  chain_list *ScanOper;
  long        NumNode;

  if ( IsVexNodeAtom( Expr ) )
  {
    return( 1 );
  }

  NumNode = 1;

  for ( ScanOper  = Expr->OPERAND;
        ScanOper != (chain_list *)0;
        ScanOper  = ScanOper->NEXT )
  {
    NumNode += getvexexprnumnode( GetVexOperand( ScanOper ) );
  }

  return( NumNode );
}
