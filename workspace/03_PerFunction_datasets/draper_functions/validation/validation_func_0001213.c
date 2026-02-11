isGray(QRgb c)
{
    return qRed(c) == qGreen(c)
	&& qRed(c) == qBlue(c);
}
