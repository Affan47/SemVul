FDKsbrEnc_WriteEnvSingleChannelElement(
                                       HANDLE_SBR_HEADER_DATA sbrHeaderData,
                                       HANDLE_PARAMETRIC_STEREO         hParametricStereo,
                                       HANDLE_SBR_BITSTREAM_DATA        sbrBitstreamData,
                                       HANDLE_SBR_ENV_DATA              sbrEnvData,
                                       HANDLE_COMMON_DATA               cmonData,
                                       UINT                             sbrSyntaxFlags
                                      )

{
  INT payloadBits = 0;

  cmonData->sbrHdrBits  = 0;
  cmonData->sbrDataBits = 0;


  if (sbrEnvData != NULL) {


    payloadBits += encodeSbrHeader (sbrHeaderData,
                                    sbrBitstreamData,
                                    cmonData);


    payloadBits += encodeSbrData (sbrEnvData,
                                  NULL,
                                  hParametricStereo,
                                  cmonData,
                                  SBR_ID_SCE,
                                  0,
                                  sbrSyntaxFlags);

  }
  return payloadBits;
}
