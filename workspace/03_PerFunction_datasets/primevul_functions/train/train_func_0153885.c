void JBIG2Stream::readExtensionSeg(unsigned int length)
{

    byteCounter += curStr->discardChars(length);
}
