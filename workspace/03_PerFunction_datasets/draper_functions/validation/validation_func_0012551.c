updateSourceEvent(const QString &name)
{
	Q_UNUSED (name)

	if (m_OSFile.open (QIODevice::ReadOnly | QIODevice::Text) && m_OSActive)
	{
		QTextStream in (&m_OSFile);
		setData(I18N_NOOP("ed2k_state"), in.readLine().toInt());
		setData(I18N_NOOP("ed2k_server_name"), in.readLine());
		setData(I18N_NOOP("ed2k_server_ip"), in.readLine());
		setData(I18N_NOOP("ed2k_server_port"), in.readLine().toInt());
		setData(I18N_NOOP("ed2k_id_high_low"), in.readLine());
		setData(I18N_NOOP("kad_status"), in.readLine().toInt());
		setData(I18N_NOOP("down_speed"), in.readLine().toDouble());
		setData(I18N_NOOP("up_speed"), in.readLine().toDouble());
		setData(I18N_NOOP("clients_in_up_queue"), in.readLine().toInt());
		setData(I18N_NOOP("shared_files_count"), in.readLine().toInt());
		setData(I18N_NOOP("nickname"), in.readLine());
		setData(I18N_NOOP("total_bytes_downloaded"), in.readLine().toLongLong());
		setData(I18N_NOOP("total_bytes_uploaded"), in.readLine().toLongLong());
		setData(I18N_NOOP("version"), in.readLine());
		setData(I18N_NOOP("session_bytes_downloaded"), in.readLine().toLongLong());
		setData(I18N_NOOP("session_bytes_uploaded"), in.readLine().toLongLong());
		setData(I18N_NOOP("uptime"), in.readLine().toInt());
		m_OSFile.close();
		scheduleSourcesUpdated();
		return true;
	} else {
		return false;
	}
}
