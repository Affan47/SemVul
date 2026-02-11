clearMachineInstState()
{

    mOpType = mi_NOP;
    mOpInst = sid_INVALID;
    mDo_Alpha = false;
    mArgCnt = 0;

    for(int i=0; i<MAXOPPARRAMS; i++) {
        mOpParrams[i].Arg = GL_NONE;
        mOpParrams[i].Filled = false;
        mOpParrams[i].MaskRep = GL_NONE;
        mOpParrams[i].Mod = GL_NONE;
    }

}
