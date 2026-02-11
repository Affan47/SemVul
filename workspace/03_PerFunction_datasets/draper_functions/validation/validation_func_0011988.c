DebuggerInspectableFrame(
    JavaScriptFrame* frame,
    int frame_index,
    Isolate* isolate) {
  ASSERT(isolate == Isolate::Current());
  ASSERT(frame->is_optimized());
  ASSERT(isolate->deoptimizer_data()->deoptimized_frame_info_ == NULL);


  JSFunction* function = JSFunction::cast(frame->function());
  Code* code = frame->LookupCode();


  SafepointEntry safepoint_entry = code->GetSafepointEntry(frame->pc());
  int deoptimization_index = safepoint_entry.deoptimization_index();
  ASSERT(deoptimization_index != Safepoint::kNoDeoptimizationIndex);


  unsigned stack_slots = code->stack_slots();
  unsigned fp_to_sp_delta = ((stack_slots + 2) * kPointerSize);

  Deoptimizer* deoptimizer = new Deoptimizer(isolate,
                                             function,
                                             Deoptimizer::DEBUGGER,
                                             deoptimization_index,
                                             frame->pc(),
                                             fp_to_sp_delta,
                                             code);
  Address tos = frame->fp() - fp_to_sp_delta;
  deoptimizer->FillInputFrame(tos, frame);


  Deoptimizer::ComputeOutputFrames(deoptimizer);


  ASSERT_LT(frame_index, deoptimizer->output_count());
  DeoptimizedFrameInfo* info =
      new DeoptimizedFrameInfo(deoptimizer, frame_index);
  isolate->deoptimizer_data()->deoptimized_frame_info_ = info;


  Address top =
      reinterpret_cast<Address>(deoptimizer->output_[frame_index]->GetTop());
  uint32_t size = deoptimizer->output_[frame_index]->GetFrameSize();


  deoptimizer->DeleteFrameDescriptions();


  deoptimizer->MaterializeHeapNumbersForDebuggerInspectableFrame(
      top, size, info);


  delete deoptimizer;

  return info;
}
