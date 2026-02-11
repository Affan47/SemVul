PushOff(SprintStack *ss, ptrdiff_t off, JSOp op)
{
    uintN top;

    if (!SprintEnsureBuffer(&ss->sprinter, PAREN_SLOP))
        return JS_FALSE;


    top = ss->top;
    JS_ASSERT(top < StackDepth(ss->printer->script));
    if (top >= StackDepth(ss->printer->script)) {
        JS_ReportOutOfMemory(ss->sprinter.context);
        return JS_FALSE;
    }


    ss->offsets[top] = off;
    ss->opcodes[top] = jsbytecode((op == JSOP_GETPROP2) ? JSOP_GETPROP
                                : (op == JSOP_GETELEM2) ? JSOP_GETELEM
                                : op);
    ss->top = ++top;
    AddParenSlop(ss);
    return JS_TRUE;
}
