print_attack_info(void){
	if(ether_ntop(&(idata.hsrcaddr), plinkaddr, sizeof(plinkaddr)) == 0){
		puts("ether_ntop(): Error converting address");
		exit(EXIT_FAILURE);
	}

	printf("Ethernet Source Address: %s%s\n", plinkaddr, (!idata.hsrcaddr_f)?" (automatically selected)":"");


	if(ether_ntop(&(idata.hdstaddr), plinkaddr, sizeof(plinkaddr)) == 0){
		puts("ether_ntop(): Error converting address");
		exit(EXIT_FAILURE);
	}

	printf("Ethernet Destination Address: %s%s\n", plinkaddr, (!idata.hdstaddr_f)?" (automatically selected)":"");

	if(inet_ntop(AF_INET6, &(idata.srcaddr), psrcaddr, sizeof(psrcaddr)) == NULL){
		puts("inet_ntop(): Error converting IPv6 Source Address to presentation format");
		exit(EXIT_FAILURE);
	}

	if(idata.dstaddr_f){
		printf("IPv6 Source Address: %s%s\n", psrcaddr, ((!idata.srcaddr_f)?" (automatically selected)":""));
	}

	if(inet_ntop(AF_INET6, &(idata.dstaddr), pdstaddr, sizeof(pdstaddr)) == NULL){
		puts("inet_ntop(): Error converting IPv6 Destination Address to presentation format");
		exit(EXIT_FAILURE);
	}

	printf("IPv6 Destination Address: %s\n", pdstaddr);

	printf("IPv6 Hop Limit: %u%s\n", hoplimit, (hoplimit_f)?"":" (randomized)");

	printf("Protocol: %s\tDestination Port: %u\n", (protocol==IPPROTO_TCP)?"TCP":"UDP", dstport);
}
