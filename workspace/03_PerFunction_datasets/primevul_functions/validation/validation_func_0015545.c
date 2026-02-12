ConnStateData::connFinishedWithConn(int size)
{
    if (size == 0) {
        if (pipeline.empty() && inBuf.isEmpty()) {

            debugs(33, 4, HERE << clientConnection << " closed");
            return true;
        } else if (!Config.onoff.half_closed_clients) {

            debugs(33, 3, HERE << clientConnection << " aborted (half_closed_clients disabled)");
            pipeline.terminateAll(0);
            return true;
        }
    }

    return false;
}
