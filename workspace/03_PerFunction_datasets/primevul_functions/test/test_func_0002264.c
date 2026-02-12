void unsubscribeAll(Subscriber *subscriber, bool mayFlush = true) {
        if (subscriber) {
            for (Topic *topic : subscriber->subscriptions) {


                if (mayFlush && topic->triggered) {
                    drain();
                }


                topic->subs.erase(subscriber);
                trimTree(topic);
            }
            subscriber->subscriptions.clear();
        }
    }
