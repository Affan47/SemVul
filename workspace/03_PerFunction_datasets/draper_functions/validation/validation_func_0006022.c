handleMotion(const XMotionEvent &motion) {
    if (fClickButtonDown) {
        if (fClickDrag) {
            handleDrag(fClickEvent, motion);
        } else {
            int const dx(abs(motion.x_root - fClickEvent.x_root));
            int const dy(abs(motion.y_root - fClickEvent.y_root));
            int const motionDelta(max(dx, dy));
            int curButtons = 0;

            curButtons =
                ((motion.state & Button1Mask) ? (1 << 1) : 0) |
                ((motion.state & Button2Mask) ? (1 << 2) : 0) |
                ((motion.state & Button3Mask) ? (1 << 3) : 0) |
                ((motion.state & Button4Mask) ? (1 << 4) : 0) |
                ((motion.state & Button5Mask) ? (1 << 5) : 0);

            if (((motion.time - fClickTime > (unsigned) ClickMotionDelay) ||
                (motionDelta >= ClickMotionDistance)) &&
                ((1 << fClickButton) == curButtons)
               )
            {

                fClickDrag = 1;
                handleBeginDrag(fClickEvent, motion);
            }
        }
    }
}
