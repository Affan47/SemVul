Status SetOpDevice(EagerContext& ctx, EagerOperation* op, Device** device) {


  const DeviceNameUtils::ParsedName& preferred_device =
      DeviceNameUtils::HasSomeDetails(op->GetDeviceParsedName())
          ? op->GetDeviceParsedName()
          : DeviceNameUtils::AddressSpace(ctx.HostCPUParsedName());


  auto ndef = op->MutableAttrs()->BuildNodeDef();
#ifdef INTEL_MKL
  if (IsMKLEnabled() &&
      absl::StartsWith(op->Name(), mkl_op_registry::kMklOpPrefix)) {
    GetMKLNodeDef(&ndef);
  }
#endif

  TF_RETURN_IF_ERROR(ctx.SelectDevice(preferred_device, ndef, device));

  VLOG(1) << "PreferredDevice " << op->Name() << ": " << preferred_device;
  VLOG(1) << "Placer place op [" << op->Name()
          << "] on device: " << (*device)->name();
  VLOG(4) << "Available kernels for " << op->Name() << " are"
          << KernelsRegisteredForOp(op->Name());
  op->SetDevice(*device);
  return Status::OK();
}
