InitializeMpExceptionStackSwitchHandlers (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINTN                           Index;
  UINTN                           Bsp;
  UINTN                           ExceptionNumber;
  UINTN                           OldGdtSize;
  UINTN                           NewGdtSize;
  UINTN                           NewStackSize;
  IA32_DESCRIPTOR                 Gdtr;
  CPU_EXCEPTION_INIT_DATA         EssData;
  UINT8                           *GdtBuffer;
  UINT8                           *StackTop;
  UINTN                           NumberOfProcessors;

  if (!PcdGetBool (PcdCpuStackGuard)) {
    return;
  }

  MpInitLibGetNumberOfProcessors(&NumberOfProcessors, NULL);
  MpInitLibWhoAmI (&Bsp);

  ExceptionNumber = FixedPcdGetSize (PcdCpuStackSwitchExceptionList);
  NewStackSize = FixedPcdGet32 (PcdCpuKnownGoodStackSize) * ExceptionNumber;

  Status = PeiServicesAllocatePool (
             NewStackSize * NumberOfProcessors,
             (VOID **)&StackTop
             );
  ASSERT(StackTop != NULL);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return;
  }
  StackTop += NewStackSize  * NumberOfProcessors;


  EssData.Ia32.Revision = CPU_EXCEPTION_INIT_DATA_REV;
  EssData.Ia32.InitDefaultHandlers = FALSE;

  EssData.Ia32.StackSwitchExceptions = FixedPcdGetPtr(PcdCpuStackSwitchExceptionList);
  EssData.Ia32.StackSwitchExceptionNumber = ExceptionNumber;
  EssData.Ia32.KnownGoodStackSize = FixedPcdGet32(PcdCpuKnownGoodStackSize);


  Gdtr.Base = 0;
  Gdtr.Limit = 0;
  for (Index = 0; Index < NumberOfProcessors; ++Index) {


    if (Index == Bsp) {
      GetGdtr(&Gdtr);
    } else {


      MpInitLibStartupThisAP (GetGdtr, Index, NULL, 0, (VOID *)&Gdtr, NULL);
    }


    OldGdtSize = Gdtr.Limit + 1;
    EssData.Ia32.ExceptionTssDescSize = sizeof (IA32_TSS_DESCRIPTOR) *
                                        (ExceptionNumber + 1);
    EssData.Ia32.ExceptionTssSize = sizeof (IA32_TASK_STATE_SEGMENT) *
                                    (ExceptionNumber + 1);
    NewGdtSize = sizeof (IA32_TSS_DESCRIPTOR) +
                 OldGdtSize +
                 EssData.Ia32.ExceptionTssDescSize +
                 EssData.Ia32.ExceptionTssSize;

    Status = PeiServicesAllocatePool (
               NewGdtSize,
               (VOID **)&GdtBuffer
               );
    ASSERT (GdtBuffer != NULL);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return;
    }


    EssData.Ia32.GdtTable = ALIGN_POINTER(GdtBuffer, sizeof (IA32_TSS_DESCRIPTOR));
    NewGdtSize -= ((UINT8 *)EssData.Ia32.GdtTable - GdtBuffer);
    EssData.Ia32.GdtTableSize = NewGdtSize;

    EssData.Ia32.ExceptionTssDesc = ((UINT8 *)EssData.Ia32.GdtTable + OldGdtSize);
    EssData.Ia32.ExceptionTss = ((UINT8 *)EssData.Ia32.GdtTable + OldGdtSize +
                                 EssData.Ia32.ExceptionTssDescSize);

    EssData.Ia32.KnownGoodStackTop = (UINTN)StackTop;
    DEBUG ((DEBUG_INFO,
            "Exception stack top[cpu%lu]: 0x%lX\n",
            (UINT64)(UINTN)Index,
            (UINT64)(UINTN)StackTop));

    if (Index == Bsp) {
      InitializeExceptionStackSwitchHandlers (&EssData);
    } else {
      MpInitLibStartupThisAP (
        InitializeExceptionStackSwitchHandlers,
        Index,
        NULL,
        0,
        (VOID *)&EssData,
        NULL
        );
    }

    StackTop  -= NewStackSize;
  }
}
