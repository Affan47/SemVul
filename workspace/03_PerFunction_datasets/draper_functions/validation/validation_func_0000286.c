associateClientWindow() {
    frame().setShapingClient(m_client, false);

    frame().moveResizeForClient(m_client->x(), m_client->y(),
                                m_client->width(), m_client->height(),
                                m_client->gravity(), m_client->old_bw);

    updateSizeHints();
    frame().setClientWindow(*m_client);
}
