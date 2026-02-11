elementStartLocal(
                                            const String& element,
                                            const XMLAttributes& attributes)
{
    if (element == AnimationAffectorHandler::ElementName)
        d_chainedHandler = new AnimationAffectorHandler(attributes, *d_anim);
    else if (element == AnimationSubscriptionHandler::ElementName)
        d_chainedHandler = new AnimationSubscriptionHandler(attributes, *d_anim);
    else
        Logger::getSingleton().logEvent(
            "AnimationDefinitionHandler::elementStart: "
            "<" + element + "> is invalid at this location.", Errors);
}
