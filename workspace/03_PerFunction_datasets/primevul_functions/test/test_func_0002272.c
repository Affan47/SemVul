void subscribe(std::string_view topic, Subscriber *subscriber) {

        Topic *iterator = root;


        for (size_t start = 0, stop = 0; stop != std::string::npos; start = stop + 1) {
            stop = topic.find('/', start);
            std::string_view segment = topic.substr(start, stop - start);

            auto lb = iterator->children.lower_bound(segment);

            if (lb != iterator->children.end() && !(iterator->children.key_comp()(segment, lb->first))) {
                iterator = lb->second;
            } else {

                Topic *newTopic = new Topic;
                newTopic->parent = iterator;
                newTopic->name = new char[segment.length()];
                newTopic->length = segment.length();
                newTopic->terminatingWildcardChild = nullptr;
                newTopic->wildcardChild = nullptr;
                memcpy(newTopic->name, segment.data(), segment.length());


                iterator->children.insert(lb, {std::string_view(newTopic->name, segment.length()), newTopic});


                if (segment.length() == 1) {

                    if (segment[0] == '+') {
                        iterator->wildcardChild = newTopic;
                    }

                    if (segment[0] == '#') {
                        iterator->terminatingWildcardChild = newTopic;
                    }
                }

                iterator = newTopic;
            }
        }


        if (iterator->triggered) {
            drain();
        }


        auto [it, inserted] = iterator->subs.insert(subscriber);


        if (inserted) {
            subscriber->subscriptions.push_back(iterator);
        }
    }
