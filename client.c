#include "client.h"
#include <stdio.h>
#include <mosquitto.h>

void cli_init(struct cli* me, const char* brokerURL, int qos)
{
	me->qos = qos;
	me->mosq = mosquitto_new(NULL, true, me);
	mosquitto_connect(me->mosq, brokerURL, 1883, 60);
}

void cli_cleanup(struct cli* me)
{
	mosquitto_disconnect(me->mosq);
	mosquitto_destroy(me->mosq);
}

void cli_publish(struct cli* me, float temp)
{
#ifdef BINARY_TRANSFER
	mosquitto_publish(me->mosq, NULL, "sensors/temperature", sizeof(temp), &temp, me->qos, false);
	printf("%.1f\n", temp);
#else
	char payload[8];
	int len;
	len = sprintf(payload, "%.1f", temp);
	mosquitto_publish(me->mosq, NULL, "sensors/temperature", len, payload, me->qos, false);
	printf("%s\n", payload);
#endif
}
