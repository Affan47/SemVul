void LIRGenerator::volatile_field_store(LIR_Opr value, LIR_Address* address,
                                        CodeEmitInfo* info) {
  if (address->type() == T_LONG) {
    address = new LIR_Address(address->base(),
                              address->index(), address->scale(),
                              address->disp(), T_DOUBLE);


    LIR_Opr temp_double = new_register(T_DOUBLE);
    LIR_Opr spill = new_register(T_LONG);
    set_vreg_flag(spill, must_start_in_memory);
    __ move(value, spill);
    __ volatile_move(spill, temp_double, T_LONG);
    __ volatile_move(temp_double, LIR_OprFact::address(address), T_LONG, info);
  } else {
    __ store(value, address, info);
  }
}
