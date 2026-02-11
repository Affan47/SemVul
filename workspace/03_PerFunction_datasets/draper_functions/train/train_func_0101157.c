prodCapability (Capability *cap, Task *task)
{
    ACQUIRE_LOCK(&cap->lock);
    if (!cap->running_task) {
        cap->running_task = task;
        releaseCapability_(cap,rtsTrue);
    }
    RELEASE_LOCK(&cap->lock);
}
