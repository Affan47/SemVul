GetFrameSize() const
{
    return (m_pVideodecoder) ? m_pVideodecoder->GetDestFmt().biSizeImage : 0;
}
