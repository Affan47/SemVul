resetKeyboardVars(bool noMatches )
{

    if (d->lastHitAction) {
        d->lastHitAction->setText(d->originalText);
        d->lastHitAction = 0L;
    }

    if (!noMatches) {
        d->keySeq.clear();
    }

    d->noMatches = noMatches;
}
