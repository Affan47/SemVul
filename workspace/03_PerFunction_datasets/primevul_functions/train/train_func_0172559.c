PidRefStack* Parser::PushPidRef(IdentPtr pid)
{
    if (PHASE_ON1(Js::ParallelParsePhase))
    {


        return pid->FindOrAddPidRef(&m_nodeAllocator, GetCurrentBlock()->sxBlock.blockId, GetCurrentFunctionNode()->sxFnc.functionId);
    }

    Assert(GetCurrentBlock() != nullptr);
    AssertMsg(pid != nullptr, "PID should be created");
    PidRefStack *ref = pid->GetTopRef();
    int blockId = GetCurrentBlock()->sxBlock.blockId;
    int funcId = GetCurrentFunctionNode()->sxFnc.functionId;
    if (!ref || (ref->GetScopeId() < blockId))
    {
        ref = Anew(&m_nodeAllocator, PidRefStack);
        if (ref == nullptr)
        {
            Error(ERRnoMemory);
        }
        pid->PushPidRef(blockId, funcId, ref);
    }
    else if (m_reparsingLambdaParams)
    {


        ref = this->FindOrAddPidRef(pid, blockId, funcId);

        ref->funcId = funcId;
    }

    return ref;
}
