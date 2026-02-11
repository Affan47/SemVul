process_if(Node node, RfmBlock block)
{
    RfmBlock   join;
    RfmBlock   taken;
    RfmBlock   not_taken;
    RfmLabel   join_label;
    RfmLabel   taken_label;
    RfmLabel   not_taken_label;
    RfmBranch  join_branch;
    RfmBranch  taken_branch;
    RfmBranch  not_taken_branch;
    RfmOperand op_taken;
    RfmOperand op_not_taken;
    RfmStm     stm;
    Boolean    is_not;
    RfmOperand op_comp;
    RfmQuad    quad;

    taken = MakeRfmBlockWithLabel(block, NULL, &taken_label);
    not_taken = MakeRfmBlockWithLabel(taken, NULL, &not_taken_label);
    join = MakeRfmBlockWithLabel(not_taken, NULL, &join_label);

    MoveForkRfmBranch(join, block);
    taken_branch = ConnectRfmBlock(block, taken, RFM_BRANCH_TAKEN);
    taken_branch->label = taken_label;
    not_taken_branch = ConnectRfmBlock(block, not_taken,
                                       RFM_BRANCH_NOT_TAKEN);
    not_taken_branch->label = not_taken_label;
    join_branch = ConnectRfmBlock(taken, join,
                                  RFM_BRANCH_UNCONDITIONAL);
    join_branch->label = join_label;
    join_branch = ConnectRfmBlock(not_taken, join,
                                  RFM_BRANCH_UNCONDITIONAL);
    join_branch->label = join_label;


    op_taken = MakeLabelRfmOperand(taken_label, NULL);
    op_not_taken = MakeLabelRfmOperand(not_taken_label, NULL);

    stm = MakeRfmStm(block, block->stm_tail, node->FIRST_CHILD);
    if (node->FIRST_CHILD->CODE == NODE_NOT) {
        is_not = TRUE;
        op_comp = ReformExpClass(node->FIRST_CHILD->FIRST_CHILD, stm);
    } else {
        is_not = FALSE;
        op_comp = ReformExpClass(node->FIRST_CHILD, stm);
    }

    quad = MakeRfmQuad(stm, stm->quad_tail, node);
    quad->operator = OPE_JF;
    quad->operand[0] = op_not_taken;
    quad->operand[1] = op_comp;
    not_taken_branch->quad = quad;

    quad = MakeRfmQuad(stm, stm->quad_tail, node);
    quad->operator = OPE_JMP;
    quad->operand[0] = op_taken;
    taken_branch->quad = quad;

    if (is_not) {
        if (node->SECOND_CHILD) {
            (void)ReformBlockClass(node->SECOND_CHILD, not_taken);
        }
        if (node->THIRD_CHILD) {
            (void)ReformBlockClass(node->THIRD_CHILD, taken);
        }
    } else {
        if (node->SECOND_CHILD) {
            (void)ReformBlockClass(node->SECOND_CHILD, taken);
        }
        if (node->THIRD_CHILD) {
            (void)ReformBlockClass(node->THIRD_CHILD, not_taken);
        }
    }

    return(join);
}
