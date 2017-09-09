#include "client.h"
#include <stdbool.h>
#include <stdio.h>
#include <mosquitto.h>

bool cli_init(struct cli* me, const char* brokerURL, int qos)
{
	if (me) {
		me->qos = qos;
		me->mosq = mosquitto_new(NULL, true, me);
		return (mosquitto_connect(me->mosq, brokerURL, 1883, 60) == MOSQ_ERR_SUCCESS);
	} else {
		return false;
	}
}

void cli_cleanup(struct cli* me)
{
	if (me) {
		mosquitto_disconnect(me->mosq);
		mosquitto_destroy(me->mosq);
	}
}

bool cli_publish(struct cli* me, float temp)
{
	if (me) {
#ifdef BINARY_TRANSFER
		printf("%.1f\n", temp);
		return (mosquitto_publish(me->mosq, NULL, "sensors/temperature", sizeof(temp), &temp, me->qos, false) == MOSQ_ERR_SUCCESS);
#else
		char payload[8];
		int len;
		len = sprintf(payload, "%.1f", temp);
		printf("%s\n", payload);
		return (mosquitto_publish(me->mosq, NULL, "sensors/temperature", len, payload, me->qos, false) == MOSQ_ERR_SUCCESS);
#endif
	} else {
		return false;
	}
}
