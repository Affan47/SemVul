Status makeError(std::string baseMsg, BSONElement idElem) {
            if (idElem.eoo()) {
                baseMsg += " in object with unknown _id";
            }
            else {
                baseMsg += " in object with " + idElem.toString(true, true);
            }
            return Status(ErrorCodes::InvalidBSON, baseMsg);
        }
