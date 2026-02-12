bool unsubscribe(std::string_view topic, Subscriber *subscriber) {

        if (subscriber) {

            Topic *iterator = root;
            for (size_t start = 0, stop = 0; stop != std::string::npos; start = stop + 1) {
                stop = topic.find('/', start);
                std::string_view segment = topic.substr(start, stop - start);

                std::map<std::string_view, Topic *>::iterator it = iterator->children.find(segment);
                if (it == iterator->children.end()) {

                    return false;
                }

                iterator = it->second;
            }


            for (auto it = subscriber->subscriptions.begin(); it != subscriber->subscriptions.end(); it++) {
                if (*it == iterator) {

                    if (iterator->triggered) {
                        drain();
                    }


                    subscriber->subscriptions.erase(it);


                    iterator->subs.erase(subscriber);
                    trimTree(iterator);
                    return true;
                }
            }
        }
        return false;
    }
