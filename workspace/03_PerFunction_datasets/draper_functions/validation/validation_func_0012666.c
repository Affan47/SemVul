Close()
{
  if (m_outFile == NULL) {
    return;
  }

  this->flush();
  this->pop();

  m_outFile->close();
  delete m_outFile;
  m_outFile = NULL;
  return;
}
