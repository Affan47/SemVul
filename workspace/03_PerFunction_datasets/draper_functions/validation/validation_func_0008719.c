EvalBondExpr(BondExpr *expr,OBBond *bond)
  {
    for (;;)
      switch( expr->type )
        {
        case BE_LEAF:

          if( expr->leaf.prop == BL_CONST )
            return((expr->leaf.value != 0) ? true : false);
          else
            switch( expr->leaf.value )
              {
              case BT_SINGLE:
                return(bond->GetBO() == 1 && !bond->IsAromatic());
              case BT_AROM:
                return(bond->IsAromatic());
              case BT_DOUBLE:
                return(bond->GetBO()==2 && !bond->IsAromatic());
              case BT_TRIPLE:
                return(bond->GetBO()==3);
              case BT_QUAD:
                return(bond->GetBO()==4);
              case BT_RING:
                return(bond->IsInRing());
              case BT_UP:
                return(bond->IsUp());
              case BT_DOWN:
                return(bond->IsDown());
              case BT_UPUNSPEC:
                return(!bond->IsDown());
              case BT_DOWNUNSPEC:
                return(!bond->IsUp());
              default:
                return(false);
              }
          break;

        case BE_NOT:
          return(!EvalBondExpr(expr->mon.arg,bond));
        case BE_ANDHI:
        case BE_ANDLO:
          if (!EvalBondExpr(expr->bin.lft,bond))
            return(false);
          expr = expr->bin.rgt;
          break;

        case BE_OR:
          if (EvalBondExpr(expr->bin.lft,bond))
            return(true);
          expr = expr->bin.rgt;
          break;
        default:
          return false;
        }
  }
