void JBIG2Stream::readEndOfStripeSeg(unsigned int length)
{

    byteCounter += curStr->discardChars(length);
}
