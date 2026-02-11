isMounted() const {
        const QString dev = device->currentText();
        return !dev.isEmpty() && KMountPoint::currentMountPoints().findByDevice(dev);
    }
