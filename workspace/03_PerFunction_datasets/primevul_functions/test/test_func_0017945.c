static void
xmlXPathOptimizeExpression(xmlXPathCompExprPtr comp, xmlXPathStepOpPtr op)
{


    if ((op->op == XPATH_OP_COLLECT ) &&
        (op->ch1 != -1) &&
        (op->ch2 == -1 ))
    {
        xmlXPathStepOpPtr prevop = &comp->steps[op->ch1];

        if ((prevop->op == XPATH_OP_COLLECT ) &&
            ((xmlXPathAxisVal) prevop->value ==
                AXIS_DESCENDANT_OR_SELF) &&
            (prevop->ch2 == -1) &&
            ((xmlXPathTestVal) prevop->value2 == NODE_TEST_TYPE) &&
            ((xmlXPathTypeVal) prevop->value3 == NODE_TYPE_NODE))
        {


            switch ((xmlXPathAxisVal) op->value) {
                case AXIS_CHILD:
                case AXIS_DESCENDANT:


                    op->ch1   = prevop->ch1;
                    op->value = AXIS_DESCENDANT;
                    break;
                case AXIS_SELF:
                case AXIS_DESCENDANT_OR_SELF:


                    op->ch1   = prevop->ch1;
                    op->value = AXIS_DESCENDANT_OR_SELF;
                    break;
                default:
                    break;
            }
	}
    }


    if (op->ch1 != -1)
        xmlXPathOptimizeExpression(comp, &comp->steps[op->ch1]);
    if (op->ch2 != -1)
}
