dispatchMouseEvent(QMouseEvent *_mouse, int overrideId, int overrideDetail)
{
    bool cancelable = true;
    int detail = overrideDetail;
    EventImpl::EventId evtId;
    if (overrideId) {
        evtId = static_cast<EventImpl::EventId>(overrideId);
    }
    else {
        switch (_mouse->type()) {
            case QEvent::MouseButtonPress:
                evtId = EventImpl::MOUSEDOWN_EVENT;
                break;
            case QEvent::MouseButtonRelease:
                evtId = EventImpl::MOUSEUP_EVENT;
                break;
            case QEvent::MouseButtonDblClick:
                evtId = EventImpl::CLICK_EVENT;
                detail = 1;
                break;
            case QEvent::MouseMove:
                evtId = EventImpl::MOUSEMOVE_EVENT;
                cancelable = false;
                break;
            default:
                return;
        }
    }

    int exceptioncode = 0;
    int pageX = _mouse->x();
    int pageY = _mouse->y();
    if ( document()->view() )
        document()->view()->revertTransforms( pageX, pageY );
    int clientX = pageX;
    int clientY = pageY;
    if ( document()->view() )
        document()->view()->contentsToViewport( pageX, pageY, pageX, pageY );

    int screenX = _mouse->globalX();
    int screenY = _mouse->globalY();

    int button = -1;
    switch (_mouse->button()) {
        case Qt::LeftButton:
            button = 0;
            break;
        case Qt::MidButton:
            button = 1;
            break;
        case Qt::RightButton:
            button = 2;
            break;
        default:
            break;
    }
    bool ctrlKey = (_mouse->modifiers() & Qt::ControlModifier);
    bool altKey = (_mouse->modifiers() & Qt::AltModifier);
    bool shiftKey = (_mouse->modifiers() & Qt::ShiftModifier);
    bool metaKey = (_mouse->modifiers() & Qt::MetaModifier);

    EventImpl* const evt = new MouseEventImpl(evtId, true, cancelable, document()->defaultView(),
                   detail,screenX,screenY,clientX,clientY,pageX,pageY,ctrlKey,altKey,shiftKey,metaKey,
                   button,0);
    evt->ref();
    dispatchEvent(evt,exceptioncode,true);
    evt->deref();
}
