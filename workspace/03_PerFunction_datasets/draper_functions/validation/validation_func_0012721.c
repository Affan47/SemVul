colorChanged( const QColor &c )
{
    QPixmap pix(16, 16);
    pix.fill(c);
    aColor->setIcon(pix);
}
