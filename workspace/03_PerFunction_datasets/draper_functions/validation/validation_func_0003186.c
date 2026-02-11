adjustLabelPos( QWidget *label, int targetX )
{
    QRect r = label->geometry();
    int d = targetX - r.x();
    if( d )
    {
        r.translate( qMin( qAbs(d), r.width()/6 ) * (d > 0 ? 1 : -1), 0 );
        label->setGeometry( r );
    }
}
