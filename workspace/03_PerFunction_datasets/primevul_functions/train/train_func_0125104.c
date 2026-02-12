Status validateBSONIterative(Buffer* buffer) {
            std::deque<ValidationObjectFrame> frames;
            ValidationObjectFrame* curr = NULL;
            ValidationState::State state = ValidationState::BeginObj;

            uint64_t idElemStartPos = 0;
            BSONElement idElem;

            while (state != ValidationState::Done) {
                switch (state) {
                case ValidationState::BeginObj:
                    frames.push_back(ValidationObjectFrame());
                    curr = &frames.back();
                    curr->setStartPosition(buffer->position());
                    curr->setIsCodeWithScope(false);
                    if (!buffer->readNumber<int>(&curr->expectedSize)) {
                        return makeError("bson size is larger than buffer size", idElem);
                    }
                    state = ValidationState::WithinObj;

                case ValidationState::WithinObj: {
                    const bool atTopLevel = frames.size() == 1;

                    if (atTopLevel && idElemStartPos) {
                        idElem = BSONElement(buffer->getBasePtr() + idElemStartPos);
                        buffer->setIdElem(idElem);
                        idElemStartPos = 0;
                    }

                    const uint64_t elemStartPos = buffer->position();
                    ValidationState::State nextState = state;
                    Status status = validateElementInfo(buffer, &nextState, idElem);
                    if (!status.isOK())
                        return status;


                    if (nextState != ValidationState::EndObj && idElem.eoo() && atTopLevel) {
                        if (strcmp(buffer->getBasePtr() + elemStartPos + 1, "_id") == 0) {
                            idElemStartPos = elemStartPos;
                        }
                    }

                    state = nextState;
                    break;
                }
                case ValidationState::EndObj: {
                    int actualLength = buffer->position() - curr->startPosition();
                    if ( actualLength != curr->expectedSize ) {
                        return makeError("bson length doesn't match what we found", idElem);
                    }
                    frames.pop_back();
                    if (frames.empty()) {
                        state = ValidationState::Done;
                    }
                    else {
                        curr = &frames.back();
                        if (curr->isCodeWithScope())
                            state = ValidationState::EndCodeWScope;
                        else
                            state = ValidationState::WithinObj;
                    }
                    break;
                }
                case ValidationState::BeginCodeWScope: {
                    frames.push_back(ValidationObjectFrame());
                    curr = &frames.back();
                    curr->setStartPosition(buffer->position());
                    curr->setIsCodeWithScope(true);
                    if ( !buffer->readNumber<int>( &curr->expectedSize ) )
                        return makeError("invalid bson CodeWScope size", idElem);
                    Status status = buffer->readUTF8String( NULL );
                    if ( !status.isOK() )
                        return status;
                    state = ValidationState::BeginObj;
                    break;
                }
                case ValidationState::EndCodeWScope: {
                    int actualLength = buffer->position() - curr->startPosition();
                    if ( actualLength != curr->expectedSize ) {
                        return makeError("bson length for CodeWScope doesn't match what we found",
                                         idElem);
                    }
                    frames.pop_back();
                    if (frames.empty())
                        return makeError("unnested CodeWScope", idElem);
                    curr = &frames.back();
                    state = ValidationState::WithinObj;
                    break;
                }
                case ValidationState::Done:
                    break;
                }
            }

            return Status::OK();
        }
