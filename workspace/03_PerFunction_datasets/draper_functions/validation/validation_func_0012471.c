replace_bitfield_extract(RfmQuad quad, RfmStm stm)
{
    RfmOperand  op_func;
    RfmFunc     func;

    if (quad == NULL) {
        return;
    }
    op_func = quad->operand[1];
    func = MakeIntrinsicRfmFunc(INFUNC_BITEXTRACT,
                                quad->node->RESULT_ATTR);
    op_func->tbl.func = func;
    DeleteRfmNodeLink(op_func->node_link->next);
}
