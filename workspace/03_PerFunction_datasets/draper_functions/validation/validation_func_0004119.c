wheelEvent(QWheelEvent * event)
{
    QPoint pt = event->pos();
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;


    if (m_CursorCaptured == YAXIS)
    {


        float zoom_fac = event->delta() < 0 ? 1.1 : 0.9;
        float ratio = (float)pt.y() / (float)m_OverlayPixmap.height();
        float db_range = (float)(m_MaxdB - m_MindB);
        float y_range = (float)m_OverlayPixmap.height();
        float db_per_pix = db_range / y_range;
        float fixed_db = m_MaxdB - pt.y() * db_per_pix;

        db_range = qBound(1.0f, db_range * zoom_fac, 2000.0f);

        m_MaxdB = fixed_db + ratio*db_range;
        m_MindB = m_MaxdB - db_range;
    }
    else if (m_CursorCaptured == XAXIS)
    {

        float zoom_factor = event->delta() < 0 ? 1.1 : 0.9;
        float new_range = qBound(10.0f,
                                 (float)(m_Span) * zoom_factor,
                                 (float)(m_SampleFreq) * 10.0f);


        float ratio = (float)pt.x() / (float)m_OverlayPixmap.width();

        float fixed_hz = freqFromX(pt.x());

        float f_max = fixed_hz + (1.0 - ratio) * new_range;
        float f_min = f_max - new_range;
        qint64 fc = (qint64)(f_min + (f_max - f_min) / 2.0);

        setFftCenterFreq(fc-m_CenterFreq);
        setSpanFreq((quint32)new_range);

        zoom_factor = (float)m_SampleFreq/(float)m_Span;
        qDebug() << QString("Spectrum zoom: %1x").arg(zoom_factor, 0, 'f', 1);
    }
    else if (event->modifiers() & Qt::ControlModifier)
    {

        m_DemodLowCutFreq -= numSteps*m_ClickResolution;
        m_DemodHiCutFreq += numSteps*m_ClickResolution;
        clampDemodParameters();
        emit newFilterFreq(m_DemodLowCutFreq, m_DemodHiCutFreq);
    }

    else if (event->modifiers() & Qt::ShiftModifier)
    {

        m_DemodLowCutFreq += numSteps*m_ClickResolution;
        m_DemodHiCutFreq += numSteps*m_ClickResolution;
        clampDemodParameters();
        emit newFilterFreq(m_DemodLowCutFreq, m_DemodHiCutFreq);
    }
    else
    {

        m_DemodCenterFreq += (numSteps*m_ClickResolution);
        m_DemodCenterFreq = roundFreq(m_DemodCenterFreq, m_ClickResolution );
        emit newDemodFreq(m_DemodCenterFreq, m_DemodCenterFreq-m_CenterFreq);
    }

    if (m_Running)
        m_DrawOverlay = true;
    else
        drawOverlay();
}
