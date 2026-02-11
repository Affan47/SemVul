addVSIlluminationInvocation(LightParams* curLightParams, Function* vsMain, const int groupOrder, int& internalCounter)
{
    FunctionInvocation* curFuncInvocation = NULL;


    if (curLightParams->mDirection.get() != NULL &&
        curLightParams->mVSOutDirection.get() != NULL)
    {

        if (mNormalMapSpace == NMS_TANGENT)
        {
            curFuncInvocation = OGRE_NEW FunctionInvocation(SGX_FUNC_TRANSFORMNORMAL, groupOrder, internalCounter++);
            curFuncInvocation->pushOperand(mVSTBNMatrix, Operand::OPS_IN);
            curFuncInvocation->pushOperand(curLightParams->mDirection, Operand::OPS_IN, Operand::OPM_XYZ);
            curFuncInvocation->pushOperand(curLightParams->mVSOutDirection, Operand::OPS_OUT);
            vsMain->addAtomInstance(curFuncInvocation);
        }

        else if (mNormalMapSpace == NMS_OBJECT)
        {
            curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_ASSIGN, groupOrder, internalCounter++);
            curFuncInvocation->pushOperand(curLightParams->mDirection, Operand::OPS_IN, Operand::OPM_XYZ);
            curFuncInvocation->pushOperand(curLightParams->mVSOutDirection, Operand::OPS_OUT);
            vsMain->addAtomInstance(curFuncInvocation);
        }
    }


    if (curLightParams->mPosition.get() != NULL &&
        curLightParams->mVSOutToLightDir.get() != NULL)
    {

        curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_SUBTRACT, groupOrder, internalCounter++);
        curFuncInvocation->pushOperand(curLightParams->mPosition, Operand::OPS_IN, Operand::OPM_XYZ);
        curFuncInvocation->pushOperand(mVSWorldPosition, Operand::OPS_IN);
        curFuncInvocation->pushOperand(mVSLocalDir, Operand::OPS_OUT);
        vsMain->addAtomInstance(curFuncInvocation);


        curFuncInvocation = OGRE_NEW FunctionInvocation(SGX_FUNC_TRANSFORMNORMAL, groupOrder, internalCounter++);
        curFuncInvocation->pushOperand(mWorldInvRotMatrix, Operand::OPS_IN);
        curFuncInvocation->pushOperand(mVSLocalDir, Operand::OPS_IN);
        curFuncInvocation->pushOperand(mVSLocalDir, Operand::OPS_OUT);
        vsMain->addAtomInstance(curFuncInvocation);


        if (mNormalMapSpace == NMS_TANGENT)
        {
            curFuncInvocation = OGRE_NEW FunctionInvocation(SGX_FUNC_TRANSFORMNORMAL, groupOrder, internalCounter++);
            curFuncInvocation->pushOperand(mVSTBNMatrix, Operand::OPS_IN);
            curFuncInvocation->pushOperand(mVSLocalDir, Operand::OPS_IN);
            curFuncInvocation->pushOperand(curLightParams->mVSOutToLightDir, Operand::OPS_OUT);
            vsMain->addAtomInstance(curFuncInvocation);
        }


        else if (mNormalMapSpace == NMS_OBJECT)
        {
            curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_ASSIGN, groupOrder, internalCounter++);
            curFuncInvocation->pushOperand(mVSLocalDir, Operand::OPS_IN);
            curFuncInvocation->pushOperand(curLightParams->mVSOutToLightDir, Operand::OPS_OUT);
            vsMain->addAtomInstance(curFuncInvocation);
        }
    }


    return true;
}
