void nsexec(void)
{
	int pipenum;
	jmp_buf env;
	int sync_child_pipe[2], sync_grandchild_pipe[2];
	struct nlconfig_t config = { 0 };


	pipenum = initpipe();
	if (pipenum == -1)
		return;


	nl_parse(pipenum, &config);


	update_oom_score_adj(config.oom_score_adj, config.oom_score_adj_len);


	if (config.namespaces) {
		if (prctl(PR_SET_DUMPABLE, 0, 0, 0, 0) < 0)
			bail("failed to set process as non-dumpable");
	}


	if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sync_child_pipe) < 0)
		bail("failed to setup sync pipe between parent and child");


	if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sync_grandchild_pipe) < 0)
		bail("failed to setup sync pipe between parent and grandchild");


	switch (setjmp(env)) {


	case JUMP_PARENT:{
			int len;
			pid_t child, first_child = -1;
			bool ready = false;


			prctl(PR_SET_NAME, (unsigned long)"runc:[0:PARENT]", 0, 0, 0);


			child = clone_parent(&env, JUMP_CHILD);
			if (child < 0)
				bail("unable to fork: child_func");


			while (!ready) {
				enum sync_t s;
				int ret;

				syncfd = sync_child_pipe[1];
				close(sync_child_pipe[0]);

				if (read(syncfd, &s, sizeof(s)) != sizeof(s))
					bail("failed to sync with child: next state");

				switch (s) {
				case SYNC_ERR:

					if (read(syncfd, &ret, sizeof(ret)) != sizeof(ret))
						bail("failed to sync with child: read(error code)");

					exit(ret);
				case SYNC_USERMAP_PLS:


					if (config.is_rootless_euid && !config.is_setgroup)
						update_setgroups(child, SETGROUPS_DENY);


					update_uidmap(config.uidmappath, child, config.uidmap, config.uidmap_len);
					update_gidmap(config.gidmappath, child, config.gidmap, config.gidmap_len);

					s = SYNC_USERMAP_ACK;
					if (write(syncfd, &s, sizeof(s)) != sizeof(s)) {
						kill(child, SIGKILL);
						bail("failed to sync with child: write(SYNC_USERMAP_ACK)");
					}
					break;
				case SYNC_RECVPID_PLS:{
						first_child = child;


						if (read(syncfd, &child, sizeof(child)) != sizeof(child)) {
							kill(first_child, SIGKILL);
							bail("failed to sync with child: read(childpid)");
						}


						s = SYNC_RECVPID_ACK;
						if (write(syncfd, &s, sizeof(s)) != sizeof(s)) {
							kill(first_child, SIGKILL);
							kill(child, SIGKILL);
							bail("failed to sync with child: write(SYNC_RECVPID_ACK)");
						}


						len = dprintf(pipenum, "{\"pid\": %d, \"pid_first\": %d}\n", child, first_child);
						if (len < 0) {
							kill(child, SIGKILL);
							bail("unable to generate JSON for child pid");
						}
					}
					break;
				case SYNC_CHILD_READY:
					ready = true;
					break;
				default:
					bail("unexpected sync value: %u", s);
				}
			}


			ready = false;
			while (!ready) {
				enum sync_t s;
				int ret;

				syncfd = sync_grandchild_pipe[1];
				close(sync_grandchild_pipe[0]);

				s = SYNC_GRANDCHILD;
				if (write(syncfd, &s, sizeof(s)) != sizeof(s)) {
					kill(child, SIGKILL);
					bail("failed to sync with child: write(SYNC_GRANDCHILD)");
				}

				if (read(syncfd, &s, sizeof(s)) != sizeof(s))
					bail("failed to sync with child: next state");

				switch (s) {
				case SYNC_ERR:

					if (read(syncfd, &ret, sizeof(ret)) != sizeof(ret))
						bail("failed to sync with child: read(error code)");

					exit(ret);
				case SYNC_CHILD_READY:
					ready = true;
					break;
				default:
					bail("unexpected sync value: %u", s);
				}
			}
			exit(0);
		}


	case JUMP_CHILD:{
			pid_t child;
			enum sync_t s;


			syncfd = sync_child_pipe[0];
			close(sync_child_pipe[1]);


			prctl(PR_SET_NAME, (unsigned long)"runc:[1:CHILD]", 0, 0, 0);


			if (config.namespaces)
				join_namespaces(config.namespaces);


			if (config.cloneflags & CLONE_NEWUSER) {
				if (unshare(CLONE_NEWUSER) < 0)
					bail("failed to unshare user namespace");
				config.cloneflags &= ~CLONE_NEWUSER;


				if (config.namespaces) {
					if (prctl(PR_SET_DUMPABLE, 1, 0, 0, 0) < 0)
						bail("failed to set process as dumpable");
				}
				s = SYNC_USERMAP_PLS;
				if (write(syncfd, &s, sizeof(s)) != sizeof(s))
					bail("failed to sync with parent: write(SYNC_USERMAP_PLS)");


				if (read(syncfd, &s, sizeof(s)) != sizeof(s))
					bail("failed to sync with parent: read(SYNC_USERMAP_ACK)");
				if (s != SYNC_USERMAP_ACK)
					bail("failed to sync with parent: SYNC_USERMAP_ACK: got %u", s);

				if (config.namespaces) {
					if (prctl(PR_SET_DUMPABLE, 0, 0, 0, 0) < 0)
						bail("failed to set process as dumpable");
				}


				if (setresuid(0, 0, 0) < 0)
					bail("failed to become root in user namespace");
			}


			if (unshare(config.cloneflags & ~CLONE_NEWCGROUP) < 0)
				bail("failed to unshare namespaces");


			child = clone_parent(&env, JUMP_INIT);
			if (child < 0)
				bail("unable to fork: init_func");


			s = SYNC_RECVPID_PLS;
			if (write(syncfd, &s, sizeof(s)) != sizeof(s)) {
				kill(child, SIGKILL);
				bail("failed to sync with parent: write(SYNC_RECVPID_PLS)");
			}
			if (write(syncfd, &child, sizeof(child)) != sizeof(child)) {
				kill(child, SIGKILL);
				bail("failed to sync with parent: write(childpid)");
			}


			if (read(syncfd, &s, sizeof(s)) != sizeof(s)) {
				kill(child, SIGKILL);
				bail("failed to sync with parent: read(SYNC_RECVPID_ACK)");
			}
			if (s != SYNC_RECVPID_ACK) {
				kill(child, SIGKILL);
				bail("failed to sync with parent: SYNC_RECVPID_ACK: got %u", s);
			}

			s = SYNC_CHILD_READY;
			if (write(syncfd, &s, sizeof(s)) != sizeof(s)) {
				kill(child, SIGKILL);
				bail("failed to sync with parent: write(SYNC_CHILD_READY)");
			}


			exit(0);
		}


	case JUMP_INIT:{


			enum sync_t s;


			syncfd = sync_grandchild_pipe[0];
			close(sync_grandchild_pipe[1]);
			close(sync_child_pipe[0]);
			close(sync_child_pipe[1]);


			prctl(PR_SET_NAME, (unsigned long)"runc:[2:INIT]", 0, 0, 0);

			if (read(syncfd, &s, sizeof(s)) != sizeof(s))
				bail("failed to sync with parent: read(SYNC_GRANDCHILD)");
			if (s != SYNC_GRANDCHILD)
				bail("failed to sync with parent: SYNC_GRANDCHILD: got %u", s);

			if (setsid() < 0)
				bail("setsid failed");

			if (setuid(0) < 0)
				bail("setuid failed");

			if (setgid(0) < 0)
				bail("setgid failed");

			if (!config.is_rootless_euid && config.is_setgroup) {
				if (setgroups(0, NULL) < 0)
					bail("setgroups failed");
			}


			if (config.cloneflags & CLONE_NEWCGROUP) {
				uint8_t value;
				if (read(pipenum, &value, sizeof(value)) != sizeof(value))
					bail("read synchronisation value failed");
				if (value == CREATECGROUPNS) {
					if (unshare(CLONE_NEWCGROUP) < 0)
						bail("failed to unshare cgroup namespace");
				} else
					bail("received unknown synchronisation value");
			}

			s = SYNC_CHILD_READY;
			if (write(syncfd, &s, sizeof(s)) != sizeof(s))
				bail("failed to sync with patent: write(SYNC_CHILD_READY)");


			close(sync_grandchild_pipe[0]);


			nl_free(&config);


			return;
		}
	default:
		bail("unexpected jump value");
	}


	bail("should never be reached");
}
