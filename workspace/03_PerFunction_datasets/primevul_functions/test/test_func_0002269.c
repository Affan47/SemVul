void trimTree(Topic *topic) {
        repeat:
        if (!topic->subs.size() && !topic->children.size() && !topic->terminatingWildcardChild && !topic->wildcardChild) {
            Topic *parent = topic->parent;

            if (topic->length == 1) {
                if (topic->name[0] == '#') {
                    parent->terminatingWildcardChild = nullptr;
                } else if (topic->name[0] == '+') {
                    parent->wildcardChild = nullptr;
                }
            }

            parent->children.erase(std::string_view(topic->name, topic->length));


            if (topic->triggered) {
                Topic *tmp[64];
                int length = 0;
                for (int i = 0; i < numTriggeredTopics; i++) {
                    if (triggeredTopics[i] != topic) {
                        tmp[length++] = triggeredTopics[i];
                    }
                }

                for (int i = 0; i < length; i++) {
                    triggeredTopics[i] = tmp[i];
                }
                numTriggeredTopics = length;
            }


            delete [] topic->name;
            delete topic;

            if (parent != root) {
                topic = parent;
                goto repeat;

            }
        }
    }
