apply(const QImage &image, const QRect& clipRect  ) const
{
    QImage out;
    QImage::Format fmt = image.format();
    Punch(image, &out, clipRect);
    if (out.format() != fmt) {
        out = out.convertToFormat(fmt);
    }
    return out;
}
