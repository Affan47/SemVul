expand_builtin_apply_args ()
{


  if (apply_args_value != 0)
    return apply_args_value;
  {


    rtx temp;
    rtx seq;

    start_sequence ();
    temp = expand_builtin_apply_args_1 ();
    seq = get_insns ();
    end_sequence ();

    apply_args_value = temp;


    push_topmost_sequence ();
    emit_insn_before (seq, NEXT_INSN (get_insns ()));
    pop_topmost_sequence ();
    return temp;
  }
}
