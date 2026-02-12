void Decoder::getOrCreateBranchTarget(
		utils::Address addr,
		llvm::BasicBlock*& tBb,
		llvm::Function*& tFnc,
		llvm::Instruction* from)
{
	tBb = nullptr;
	tFnc = nullptr;

	auto* fromFnc = from->getFunction();

	if (auto* bb = getBasicBlockAtAddress(addr))
	{
		tBb = bb;
		LOG << "\t\t\t\t" << "B: getBasicBlockAtAddress() @ " << addr << std::endl;
	}
	else if (getBasicBlockContainingAddress(addr))
	{
		auto ai = AsmInstruction(_module, addr);
		if (ai.isInvalid())
		{


			LOG << "\t\t\t\t" << "B: invalid ASM @ " << addr << std::endl;
			return;
		}
		else if (ai.getFunction() == fromFnc)
		{
			tBb = ai.makeStart();
			addBasicBlock(addr, tBb);
			LOG << "\t\t\t\t" << "B: addBasicBlock @ " << addr << std::endl;
		}
		else
		{


			LOG << "\t\t\t\t" << "B: ASM in diff fnc @ " << addr << std::endl;
			return;
		}
	}

	else if (auto* targetFnc = getFunctionAtAddress(addr))
	{
		tFnc = targetFnc;
		LOG << "\t\t\t\t" << "B: getFunctionAtAddress() @ " << addr << std::endl;
	}
	else if (auto* bb = getBasicBlockBeforeAddress(addr))
	{
		tBb = createBasicBlock(addr, bb->getParent(), bb);
		LOG << "\t\t\t\t" << "B: getBasicBlockBeforeAddress() @ " << addr << std::endl;
	}
	else
	{
		tFnc = createFunction(addr);
		tBb = tFnc && !tFnc->empty() ? &tFnc->front() : nullptr;
		LOG << "\t\t\t\t" << "B: default @ " << addr << std::endl;
	}

	if (tBb && tBb->getPrevNode() == nullptr)
	{
		tFnc = tBb->getParent();
	}

	if (tBb && tBb->getParent() == fromFnc)
	{
		return;
	}
	if (tFnc)
	{
		return;
	}

	LOG << "\t\t\t\t" << "B: splitFunctionOn @ " << addr << std::endl;
	tFnc = splitFunctionOn(addr);
	tBb = tFnc && !tFnc->empty() ? &tFnc->front() : tBb;
}
