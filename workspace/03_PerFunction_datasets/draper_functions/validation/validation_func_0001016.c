write(const QString& data, WriteMode mode)
{
	if (state() == Disconnected)
		return;
	if (state() == NotStarted
	||  (m_pinging && mode == Buffered))
	{
		m_writeBuffer.append(data);
		return;
	}

	Q_ASSERT(m_ioDevice->isWritable());
	emit debugMessage(QString(">%1(%2): %3")
			  .arg(name())
			  .arg(m_id)
			  .arg(data));

	m_ioDevice->write(data.toAscii() + "\n");
}
