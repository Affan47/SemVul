BOOL msusb_msinterface_write(MSUSB_INTERFACE_DESCRIPTOR* MsInterface, wStream* out)
{
	MSUSB_PIPE_DESCRIPTOR** MsPipes;
	MSUSB_PIPE_DESCRIPTOR* MsPipe;
	UINT32 pnum = 0;

	if (!MsInterface)
		return FALSE;

	if (!Stream_EnsureRemainingCapacity(out, 16 + MsInterface->NumberOfPipes * 20))
		return FALSE;


	Stream_Write_UINT16(out, MsInterface->Length);

	Stream_Write_UINT8(out, MsInterface->InterfaceNumber);

	Stream_Write_UINT8(out, MsInterface->AlternateSetting);

	Stream_Write_UINT8(out, MsInterface->bInterfaceClass);

	Stream_Write_UINT8(out, MsInterface->bInterfaceSubClass);

	Stream_Write_UINT8(out, MsInterface->bInterfaceProtocol);

	Stream_Write_UINT8(out, 0);

	Stream_Write_UINT32(out, MsInterface->InterfaceHandle);

	Stream_Write_UINT32(out, MsInterface->NumberOfPipes);

	MsPipes = MsInterface->MsPipes;

	for (pnum = 0; pnum < MsInterface->NumberOfPipes; pnum++)
	{
		MsPipe = MsPipes[pnum];

		Stream_Write_UINT16(out, MsPipe->MaximumPacketSize);

		Stream_Write_UINT8(out, MsPipe->bEndpointAddress);

		Stream_Write_UINT8(out, MsPipe->bInterval);

		Stream_Write_UINT32(out, MsPipe->PipeType);

		Stream_Write_UINT32(out, MsPipe->PipeHandle);

		Stream_Write_UINT32(out, MsPipe->MaximumTransferSize);

		Stream_Write_UINT32(out, MsPipe->PipeFlags);
	}

	return TRUE;
}
