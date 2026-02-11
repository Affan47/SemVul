increase_priority()
{

        int old_priority = getpriority(PRIO_PROCESS, 0);
        int priority = old_priority;
        while ( (setpriority(PRIO_PROCESS, 0, priority-1) == 0) &&
                (priority > BEST_PRIORITY) )
        {
                priority--;
        }
        if (priority != old_priority) {
                if (verbose) printf("Priority changed to %d\n", priority);
        }
        else {
                if (verbose) printf("Warning: Cannot change priority. Run as root or renice for best results.\n");
        }


}
