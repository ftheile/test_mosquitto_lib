#include "mosquitto.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

struct cli {
	struct mosquitto* mosq;
	// Other client data...
};

static struct cli theClient;

static void cli_init(struct cli* me)
{
	me->mosq = mosquitto_new(NULL, true, me);
	mosquitto_connect(me->mosq, "localhost", 1883, 60);
}

static void cli_cleanup(struct cli* me)
{
	mosquitto_disconnect(me->mosq);
	mosquitto_destroy(me->mosq);
}

static void cli_publish(struct cli* me, float temp)
{
	char payload[8];
	int len;
	len = sprintf(payload, "%.1f", temp);
	mosquitto_publish(me->mosq, NULL, "sensors/temperature", len, payload, 1, false);
	printf("%s\n", payload);
}

#define MAX_SAMPLES 20

int main()
{
	int i;

	mosquitto_lib_init();
	cli_init(&theClient);

	// Generate simulated measurements and publish them:
	for (i=0; i<MAX_SAMPLES; i++) {
		float temp = 10 * sin(i * 2 * M_PI / MAX_SAMPLES);
		cli_publish(&theClient, temp);
		sleep(1);
	}

	cli_cleanup(&theClient);
	mosquitto_lib_cleanup();

	return 0;
}
