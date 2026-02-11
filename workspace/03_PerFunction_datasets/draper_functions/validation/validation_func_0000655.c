encodeSbrSingleChannelElement (HANDLE_SBR_ENV_DATA   sbrEnvData,
                               HANDLE_FDK_BITSTREAM  hBitStream
                               ,HANDLE_PARAMETRIC_STEREO hParametricStereo
                               ,UINT  sbrSyntaxFlags
                               )
{
  INT i, payloadBits = 0;

  payloadBits += FDKwriteBits (hBitStream, 0, SI_SBR_DATA_EXTRA_BITS);

  if (sbrEnvData->ldGrid) {
      if ( sbrEnvData->hSbrBSGrid->frameClass != FIXFIXonly ) {

        payloadBits += encodeSbrGrid (sbrEnvData, hBitStream);
      } else {

        payloadBits += encodeLowDelaySbrGrid ( sbrEnvData, hBitStream, encodeFreqs(LD_TRANSMISSION));
      }
  }
  else
  {
    if (sbrSyntaxFlags & SBR_SYNTAX_SCALABLE) {
      payloadBits += FDKwriteBits (hBitStream, 1, SI_SBR_COUPLING_BITS);
    }
    payloadBits += encodeSbrGrid (sbrEnvData, hBitStream);
  }

  payloadBits += encodeSbrDtdf (sbrEnvData, hBitStream);

  for (i = 0; i < sbrEnvData->noOfnoisebands; i++) {
    payloadBits += FDKwriteBits (hBitStream, sbrEnvData->sbr_invf_mode_vec[i], SI_SBR_INVF_MODE_BITS);
  }

  payloadBits += writeEnvelopeData (sbrEnvData, hBitStream, 0);
  payloadBits += writeNoiseLevelData (sbrEnvData, hBitStream, 0);

  payloadBits += writeSyntheticCodingData (sbrEnvData,hBitStream);

  payloadBits += encodeExtendedData(hParametricStereo, hBitStream);

  return payloadBits;
}
