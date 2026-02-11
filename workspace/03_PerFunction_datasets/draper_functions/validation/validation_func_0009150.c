DeoptimizeFunction(JSFunction* function) {
  AssertNoAllocation no_allocation;

  if (!function->IsOptimized()) return;


  Code* code = function->code();


  code->InvalidateRelocation();


  Address instruction_start = function->code()->instruction_start();
  Address jump_table_address =
      instruction_start + function->code()->safepoint_table_offset();
  Address previous_pc = instruction_start;

  SafepointTableDeoptimiztionEntryIterator deoptimizations(function->code());
  Address entry_pc = NULL;

  SafepointEntry current_entry = deoptimizations.Next(&entry_pc);
  while (current_entry.is_valid()) {
    int gap_code_size = current_entry.gap_code_size();
    unsigned deoptimization_index = current_entry.deoptimization_index();

#ifdef DEBUG

    ZapCodeRange(previous_pc, entry_pc);
#endif

    Address call_address = entry_pc + gap_code_size;

    Address call_end_address =
        call_address + MacroAssembler::kCallInstructionLength;


    Address next_pc = NULL;
    SafepointEntry next_entry = deoptimizations.Next(&next_pc);

    if (!next_entry.is_valid() || next_pc >= call_end_address) {

      CodePatcher patcher(call_address, Assembler::kCallInstructionLength);
      patcher.masm()->Call(GetDeoptimizationEntry(deoptimization_index, LAZY),
                           RelocInfo::NONE);
      previous_pc = call_end_address;
    } else {


      Address short_call_end_address =
          call_address + MacroAssembler::kShortCallInstructionLength;
      ASSERT(next_pc >= short_call_end_address);


      jump_table_address -= MacroAssembler::kJumpInstructionLength;
      CodePatcher jump_patcher(jump_table_address,
                               MacroAssembler::kJumpInstructionLength);
      jump_patcher.masm()->Jump(
          GetDeoptimizationEntry(deoptimization_index, LAZY),
          RelocInfo::NONE);


      CodePatcher call_patcher(call_address,
                               MacroAssembler::kShortCallInstructionLength);
      call_patcher.masm()->call(jump_table_address);
      previous_pc = short_call_end_address;
    }


    current_entry = next_entry;
    entry_pc = next_pc;
  }

#ifdef DEBUG

  ZapCodeRange(previous_pc, jump_table_address);
#endif


  DeoptimizingCodeListNode* node = new DeoptimizingCodeListNode(code);
  node->set_next(deoptimizing_code_list_);
  deoptimizing_code_list_ = node;


  function->ReplaceCode(function->shared()->code());

  if (FLAG_trace_deopt) {
    PrintF("[forced deoptimization: ");
    function->PrintName();
    PrintF(" / %" V8PRIxPTR "]\n", reinterpret_cast<intptr_t>(function));
  }
}
