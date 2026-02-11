read(bool)
{
  if(!isOpen())
    return;

  READ_STRING(d->tag.setTitle, 28);
  READ_BYTE_AS(mark);
  READ_BYTE_AS(type);

  READ_ASSERT(mark == 0x1A && type == 0x10);

  seek(32);

  READ_U16L_AS(length);
  READ_U16L_AS(sampleCount);

  d->properties.setSampleCount(sampleCount);

  READ_U16L(d->properties.setPatternCount);
  READ_U16L(d->properties.setFlags);
  READ_U16L(d->properties.setTrackerVersion);
  READ_U16L(d->properties.setFileFormatVersion);

  READ_ASSERT(readBlock(4) == "SCRM");

  READ_BYTE(d->properties.setGlobalVolume);
  READ_BYTE(d->properties.setBpmSpeed);
  READ_BYTE(d->properties.setTempo);

  READ_BYTE_AS(masterVolume);
  d->properties.setMasterVolume(masterVolume & 0x7f);
  d->properties.setStereo((masterVolume & 0x80) != 0);


  seek(12, Current);

  int channels = 0;
  for(int i = 0; i < 32; ++ i) {
    READ_BYTE_AS(setting);


    if(setting != 0xff) ++ channels;
  }
  d->properties.setChannels(channels);

  seek(96);
  ushort realLength = 0;
  for(ushort i = 0; i < length; ++ i) {
    READ_BYTE_AS(order);
    if(order == 255) break;
    if(order != 254) ++ realLength;
  }
  d->properties.setLengthInPatterns(realLength);

  seek(channels, Current);


  StringList comment;
  for(ushort i = 0; i < sampleCount; ++ i) {
    seek(96L + length + ((long)i << 1));

    READ_U16L_AS(sampleHeaderOffset);
    seek((long)sampleHeaderOffset << 4);

    READ_BYTE_AS(sampleType);
    READ_STRING_AS(dosFileName, 13);
    READ_U16L_AS(sampleDataOffset);
    READ_U32L_AS(sampleLength);
    READ_U32L_AS(repeatStart);
    READ_U32L_AS(repeatStop);
    READ_BYTE_AS(sampleVolume);

    seek(1, Current);

    READ_BYTE_AS(packing);
    READ_BYTE_AS(sampleFlags);
    READ_U32L_AS(baseFrequency);

    seek(12, Current);

    READ_STRING_AS(sampleName, 28);


    comment.append(sampleName);
  }

  d->tag.setComment(comment.toString("\n"));
  d->tag.setTrackerName("ScreamTracker III");
}
