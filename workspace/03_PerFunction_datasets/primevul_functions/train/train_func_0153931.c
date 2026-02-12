void JBIG2Stream::readProfilesSeg(unsigned int length)
{

    byteCounter += curStr->discardChars(length);
}
