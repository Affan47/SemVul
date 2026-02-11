PrintBinop (
    Expr                expr )
{
    UInt                oldPrec;
    const Char *        op;

    oldPrec = PrintPreceedence;


    switch ( TNUM_EXPR(expr) ) {
    case T_OR:     op = "or";   PrintPreceedence =  2;  break;
    case T_AND:    op = "and";  PrintPreceedence =  4;  break;
    case T_EQ:     op = "=";    PrintPreceedence =  8;  break;
    case T_LT:     op = "<";    PrintPreceedence =  8;  break;
    case T_GT:     op = ">";    PrintPreceedence =  8;  break;
    case T_NE:     op = "<>";   PrintPreceedence =  8;  break;
    case T_LE:     op = "<=";   PrintPreceedence =  8;  break;
    case T_GE:     op = ">=";   PrintPreceedence =  8;  break;
    case T_IN:     op = "in";   PrintPreceedence =  8;  break;
    case T_SUM:    op = "+";    PrintPreceedence = 10;  break;
    case T_DIFF:   op = "-";    PrintPreceedence = 10;  break;
    case T_PROD:   op = "*";    PrintPreceedence = 12;  break;
    case T_QUO:    op = "/";    PrintPreceedence = 12;  break;
    case T_MOD:    op = "mod";  PrintPreceedence = 12;  break;
    case T_POW:    op = "^";    PrintPreceedence = 16;  break;
    default:       op = "<bogus-operator>";   break;
    }


    if ( oldPrec > PrintPreceedence ) Pr("%>(%>",0L,0L);
    else Pr("%2>",0L,0L);


    if ( TNUM_EXPR(expr) == T_POW
         && ((  (IS_INTEXPR(ADDR_EXPR(expr)[0])
                 && INT_INTEXPR(ADDR_EXPR(expr)[0]) < 0)
                || TNUM_EXPR(ADDR_EXPR(expr)[0]) == T_INTNEG)
             || TNUM_EXPR(ADDR_EXPR(expr)[0]) == T_POW) ) {
        Pr( "(", 0L, 0L );
        PrintExpr( ADDR_EXPR(expr)[0] );
        Pr( ")", 0L, 0L );
    }
    else {
        PrintExpr( ADDR_EXPR(expr)[0] );
    }


    Pr("%2< %2>%s%> %<",(Int)op,0L);


    PrintPreceedence++;
    PrintExpr( ADDR_EXPR(expr)[1] );
    PrintPreceedence--;


    if ( oldPrec > PrintPreceedence ) Pr("%2<)",0L,0L);
    else Pr("%2<",0L,0L);


    PrintPreceedence = oldPrec;
}
