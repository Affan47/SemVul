Status WrapInCallOp(EagerOperation* op, EagerOperation** wrapped_op) {
  DCHECK(!op->is_function());
  const OpDef& opdef = OpRegistry::Global()->LookUp(op->Name())->op_def;


  TF_RETURN_IF_ERROR(VerifyWrappableInCallOp(opdef, op));


  auto op_attrs = op->GetOpAttrs();
  string fname;
  TF_RETURN_IF_ERROR(BuildWrappedOpName(op, opdef, op_attrs, &fname));
  if (!op->EagerContext().GetFunctionDef(fname)) {
    FunctionDef fdef;

    TF_RETURN_IF_ERROR(
        BuildWrappedOpSignature(op, opdef, fname, *fdef.mutable_signature()));

    NodeDef* ndef = fdef.add_node_def();
    ndef->set_op(op->Name());
    ndef->set_name(op->Name());
    const auto& signature = fdef.signature();
    for (size_t i = 0; i < signature.input_arg_size(); i++) {
      ndef->add_input(absl::StrCat(fdef.signature().input_arg(i).name(), ":0"));
    }


    for (const auto& attr : opdef.attr()) {
      (*ndef->mutable_attr())[attr.name()].set_placeholder(attr.name());
    }


    ndef->set_device(op->DeviceName());

#ifdef INTEL_MKL
    if (IsMKLEnabled() &&
        absl::StartsWith(op->Name(), mkl_op_registry::kMklOpPrefix)) {
      GetMKLNodeDef(ndef);
    }
#endif


    TF_RETURN_IF_ERROR(
        PopulateRetMap(&fdef, op_attrs, op, opdef, signature, ndef->name()));
    VLOG(1) << fdef.DebugString();
    TF_RETURN_IF_ERROR(op->EagerContext().AddFunctionDef(std::move(fdef)));
  }

  auto& ctx = op->EagerContext();
  AbstractOperationPtr call_op(ctx.CreateOperation());
  TF_RETURN_IF_ERROR(call_op->Reset(fname.c_str(), op->DeviceName().c_str()));
  for (auto t : op->Inputs()) {
    TF_RETURN_IF_ERROR(call_op->AddInput(t));
  }
  *wrapped_op = down_cast<EagerOperation*>(call_op.release());


  (*wrapped_op)->AddAttrs(op_attrs);
  return AddMixedTypeListAttrs(*wrapped_op, op_attrs, opdef);
}
