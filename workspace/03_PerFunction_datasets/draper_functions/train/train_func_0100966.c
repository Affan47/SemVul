StringToCompressionType(const char *option)
{
  CompressionType
    compression_type = UndefinedCompression;

  if (LocaleCompare("None",option) == 0)
    compression_type=NoCompression;
  else if (LocaleCompare("BZip",option) == 0)
    compression_type=BZipCompression;
  else if (LocaleCompare("BZip2",option) == 0)
    compression_type=BZipCompression;
  else if (LocaleCompare("BZ2",option) == 0)
    compression_type=BZipCompression;
  else if (LocaleCompare("Fax",option) == 0)
    compression_type=FaxCompression;
  else if (LocaleCompare("Group3",option) == 0)
    compression_type=Group3Compression;
  else if (LocaleCompare("Group4",option) == 0)
    compression_type=Group4Compression;
  else if (LocaleCompare("JPEG",option) == 0)
    compression_type=JPEGCompression;
  else if (LocaleCompare("Lossless",option) == 0)
    compression_type=LosslessJPEGCompression;
  else if (LocaleCompare("LZW",option) == 0)
    compression_type=LZWCompression;
  else if (LocaleCompare("RLE",option) == 0)
    compression_type=RLECompression;
  else if (LocaleCompare("Zip",option) == 0)
    compression_type=ZipCompression;
  else if (LocaleCompare("GZip",option) == 0)
    compression_type=ZipCompression;
  else if ((LocaleCompare("LZMA",option) == 0) ||
	   (LocaleCompare("LZMA2",option) == 0))
    compression_type=LZMACompression;
  else if (LocaleCompare("JPEG2000",option) == 0)
    compression_type=JPEG2000Compression;
  else if ((LocaleCompare("JBIG",option) == 0) ||
	   (LocaleCompare("JBIG1",option) == 0))
    compression_type=JBIG1Compression;
  else if (LocaleCompare("JBIG2",option) == 0)
    compression_type=JBIG2Compression;

  return compression_type;
}
