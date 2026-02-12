void drain() {


        if (!numTriggeredTopics) {
            return;
        }


        int numFilteredTriggeredTopics = 0;
        for (int i = 0; i < numTriggeredTopics; i++) {
            if (triggeredTopics[i]->subs.size()) {
                triggeredTopics[numFilteredTriggeredTopics++] = triggeredTopics[i];
            } else {


                triggeredTopics[i]->messages.clear();
                triggeredTopics[i]->triggered = false;
            }
        }
        numTriggeredTopics = numFilteredTriggeredTopics;

        if (!numTriggeredTopics) {
            return;
        }


        min = (Subscriber *)UINTPTR_MAX;
        for (int i = 0; i < numTriggeredTopics; i++) {
            if ((triggeredTopics[i]->subs.size()) && (min > *triggeredTopics[i]->subs.begin())) {
                min = *triggeredTopics[i]->subs.begin();
            }
        }


        if (min != (Subscriber *)UINTPTR_MAX) {


            std::map<uint64_t, std::pair<std::string, std::string>> intersectionCache;


            std::set<Subscriber *>::iterator it[64];
            std::set<Subscriber *>::iterator end[64];
            for (int i = 0; i < numTriggeredTopics; i++) {
                it[i] = triggeredTopics[i]->subs.begin();
                end[i] = triggeredTopics[i]->subs.end();
            }


            for (int nonEmpty = numTriggeredTopics; nonEmpty; ) {

                Subscriber *nextMin = (Subscriber *)UINTPTR_MAX;


                std::map<unsigned int, std::pair<std::string, std::string>> *perSubscriberIntersectingTopicMessages[64];
                int numPerSubscriberIntersectingTopicMessages = 0;

                uint64_t intersection = 0;

                for (int i = 0; i < numTriggeredTopics; i++) {
                    if ((it[i] != end[i]) && (*it[i] == min)) {


                        intersection |= ((uint64_t)1 << i);
                        perSubscriberIntersectingTopicMessages[numPerSubscriberIntersectingTopicMessages++] = &triggeredTopics[i]->messages;

                        it[i]++;
                        if (it[i] == end[i]) {
                            nonEmpty--;
                        }
                        else {
                            if (nextMin > *it[i]) {
                                nextMin = *it[i];
                            }
                        }
                    }
                    else {

                        if ((it[i] != end[i]) && (nextMin > *it[i])) {
                            nextMin = *it[i];
                        }
                    }
                }


                if (intersectionCache[intersection].first.length() == 0) {


                    std::map<unsigned int, std::pair<std::string, std::string>> complete;
                    for (int i = 0; i < numPerSubscriberIntersectingTopicMessages; i++) {
                        complete.insert(perSubscriberIntersectingTopicMessages[i]->begin(), perSubscriberIntersectingTopicMessages[i]->end());
                    }


                    std::pair<std::string, std::string> res;
                    for (auto &p : complete) {
                        res.first.append(p.second.first);
                        res.second.append(p.second.second);
                    }

                    cb(min, intersectionCache[intersection] = std::move(res));
                }
                else {
                    cb(min, intersectionCache[intersection]);
                }

                min = nextMin;
            }

        }


        for (int i = 0; i < numTriggeredTopics; i++) {
            triggeredTopics[i]->messages.clear();
            triggeredTopics[i]->triggered = false;
        }
        numTriggeredTopics = 0;
    }
