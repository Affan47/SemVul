DoJump() {
  ASSERT(cgen()->has_valid_frame());


  ASSERT(cgen()->HasValidEntryRegisters());

  if (is_bound()) {

    ASSERT(direction_ == BIDIRECTIONAL);
    cgen()->frame()->PrepareMergeTo(entry_frame_);
    cgen()->frame()->MergeTo(entry_frame_);
    cgen()->DeleteFrame();
    __ jmp(&entry_label_);
  } else if (entry_frame_ != NULL) {


    ASSERT(cgen()->frame()->Equals(entry_frame_));
    cgen()->DeleteFrame();
    __ jmp(&entry_label_);
  } else {


    AddReachingFrame(cgen()->frame());
    RegisterFile empty;
    cgen()->SetFrame(NULL, &empty);
    __ jmp(&merge_labels_.last());
  }
}
