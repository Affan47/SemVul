bool Decoder::canSplitFunctionOn(llvm::BasicBlock* bb)
{
	for (auto* u : bb->users())
	{


		auto* br = dyn_cast<BranchInst>(u);
		if (br == nullptr || br->isConditional())
		{
			LOG << "\t\t\t\t\t\t" << "!CAN : user not uncond for "
					<< llvmObjToString(u)
					<< ", user = " << llvmObjToString(br) << std::endl;
			return false;
		}


		AsmInstruction brAsm(br);
		AsmInstruction bbAsm(bb);
		if (brAsm.getEndAddress() == bbAsm.getAddress())
		{
			LOG << "\t\t\t\t\t\t" << "branch from ASM insn right before: "
					<< brAsm.getAddress() << " -> " << bbAsm.getAddress()
					<< std::endl;
			return false;
		}


	}

	return true;
}
