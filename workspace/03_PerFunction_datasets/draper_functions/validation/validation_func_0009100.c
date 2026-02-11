setCaptureMode(QCamera::CaptureMode mode)
{
    Q_D(QCamera);

    if (mode != captureMode()) {
        if (d->control) {
            d->_q_preparePropertyChange(QCameraControl::CaptureMode);
            d->control->setCaptureMode(mode);
        }
    }
}
