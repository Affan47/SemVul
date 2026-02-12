InitializeExceptionStackSwitchHandlers (
  IN OUT VOID *Buffer
  )
{
  CPU_EXCEPTION_INIT_DATA           *EssData;
  IA32_DESCRIPTOR                   Idtr;
  EFI_STATUS                        Status;

  EssData = Buffer;


  AsmReadIdtr (&Idtr);
  EssData->Ia32.IdtTable = (VOID *)Idtr.Base;
  EssData->Ia32.IdtTableSize = Idtr.Limit + 1;
  Status = InitializeCpuExceptionHandlersEx (NULL, EssData);
  ASSERT_EFI_ERROR (Status);
}
