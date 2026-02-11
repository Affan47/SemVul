resolve_pexpr_type(void)
{
      if (debug_elab_pexpr) {
	    cerr << get_fileline() << ": debug: "
		 << "Resolve_pexpr_type for binary " << human_readable_op(op_)
		 << "." << endl;
      }

      left_->resolve_pexpr_type();
      right_->resolve_pexpr_type();

      switch (op_) {
	  case '+':
	  case '-':
	  case '*':
	  case '/':
	    suppress_binary_operand_sign_if_needed(left_, right_);
	    cast_signed_base_(left_->has_sign() && right_->has_sign());
	    break;
	  default:
	    break;
      }
}
