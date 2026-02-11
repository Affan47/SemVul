Copy(char *start, int bytes)
{


    int bytes_left = m_buffer_size - (egptr() - m_chunk_buffer);
    if (bytes_left < bytes)
    {
        char *temp =  new char [m_buffer_size + bytes];
        memcpy (temp, m_chunk_buffer, m_buffer_size);
        setg (temp, temp+(gptr()-m_chunk_buffer), temp + (egptr() - m_chunk_buffer));
        delete [] m_chunk_buffer;
        m_chunk_buffer = temp;
    }


    memcpy (egptr(), start, bytes);
    setg(m_chunk_buffer, gptr(), egptr()+bytes);


}
