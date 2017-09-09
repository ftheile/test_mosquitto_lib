#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stdbool.h>

struct cli {
	struct mosquitto* mosq;
	int qos;
	// Other client data...
};

bool cli_init(struct cli* me, const char* brokerURL, int qos);
void cli_cleanup(struct cli* me);
bool cli_publish(struct cli* me, float temp);

#endif

