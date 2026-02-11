QueueWrittenLength( QUEUE *q )
{
    if ( q ) {
        int len = q->nFirst+q->nLength;
        return (len > q->nTotLength)? q->nTotLength : len;
    } else {
        return 0;
    }
}
