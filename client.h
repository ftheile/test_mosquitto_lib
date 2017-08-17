#ifndef _CLIENT_H_
#define _CLIENT_H_

struct cli {
	struct mosquitto* mosq;
	// Other client data...
};

void cli_init(struct cli* me, const char* brokerURL);
void cli_cleanup(struct cli* me);
void cli_publish(struct cli* me, float temp);

#endif

