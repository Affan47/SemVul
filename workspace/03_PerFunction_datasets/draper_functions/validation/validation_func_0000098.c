ReverseSubExpressions()

{
    int i;
    for( i = 0; i < nSubExprCount / 2; i++ )
    {
        ods_formula_node *temp;

        temp = papoSubExpr[i];
        papoSubExpr[i] = papoSubExpr[nSubExprCount - i - 1];
        papoSubExpr[nSubExprCount - i - 1] = temp;
    }
}
