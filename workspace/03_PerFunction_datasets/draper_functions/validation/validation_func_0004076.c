drawHandle( QPainter *painter,
    const QRect &sliderRect, int pos ) const
{
    const int bw = d_data->borderWidth;

    pos++;
    if ( orientation() == Qt::Horizontal )
    {
        QRect handleRect(
            pos - d_data->handleSize.width() / 2,
            sliderRect.y(),
            d_data->handleSize.width(),
            sliderRect.height()
        );

        qDrawShadePanel( painter,
            handleRect, palette(), false, bw,
            &palette().brush( QPalette::Button ) );

        qDrawShadeLine( painter, pos, sliderRect.top() + bw,
            pos, sliderRect.bottom() - bw,
            palette(), true, 1 );
    }
    else
    {
        QRect handleRect(
            sliderRect.left(),
            pos - d_data->handleSize.height() / 2,
            sliderRect.width(),
            d_data->handleSize.height()
        );

        qDrawShadePanel( painter,
            handleRect, palette(), false, bw,
            &palette().brush( QPalette::Button ) );

        qDrawShadeLine( painter, sliderRect.left() + bw, pos,
            sliderRect.right() - bw, pos,
            palette(), true, 1 );
    }
}
