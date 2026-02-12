MemoryDiscoveredPpiNotifyCallback (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS      Status;
  BOOLEAN         InitStackGuard;


  InitStackGuard = FALSE;
  if (IsIa32PaeSupported () && PcdGetBool (PcdCpuStackGuard)) {
    EnablePaging ();
    InitStackGuard = TRUE;
  }

  Status = InitializeCpuMpWorker ((CONST EFI_PEI_SERVICES **)PeiServices);
  ASSERT_EFI_ERROR (Status);

  if (InitStackGuard) {
    SetupStackGuardPage ();
  }

  return Status;
}
