setComponentValue(QColor &color, KColorChooserMode chooserMode, qreal value)
{
    if (chooserMode >= ChooserRed) {
        if (chooserMode == ChooserRed) {
            color.setRedF(value);
        } else if (chooserMode == ChooserGreen) {
            color.setGreenF(value);
        } else {
            color.setBlueF(value);
        }
    } else {
        qreal h, s, v, a;
        color.getHsvF(&h, &s, &v, &a);
        if (chooserMode == ChooserHue) {
            h = value;
        } else if (chooserMode == ChooserSaturation) {
            s = value;
        } else {
            v = value;
        }
        color.setHsvF(h, s, v, a);
    }
}

}
