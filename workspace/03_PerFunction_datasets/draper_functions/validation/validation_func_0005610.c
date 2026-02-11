getFirstPt() {

    if (m_gradientMode == LINEAR) {
        return m_linearGrad->getFirstPt();

    } else if (m_gradientMode == CIRCULAR) {
        return m_pointGrad->getFirstPt();

    } else if (m_gradientMode == ELLIPSE) {
        return m_ellipseGrad->getFirstPt();

    } else {
        return cvPoint(0,0);
    }

}
