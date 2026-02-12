LibarchivePlugin::~LibarchivePlugin()
{
    for (const auto e : qAsConst(m_emittedEntries)) {

        e->deleteLater();
    }
}
