boundaryPointsValid(  )
{
    short valid =  compareBoundaryPoints( m_startContainer, m_startOffset,
                                          m_endContainer, m_endOffset );
    if( valid == 1 )  return false;
    else  return true;

}
