#ifndef UCI_API_H
#define UCI_API_H

#include <uci.h>

#if 0
int uci_set_confdir(struct uci_context *ctx, const char *dir);
#endif

char *get_uci_value(struct uci_context *ctx, const char *uci_option);
int set_uci_value(struct uci_context *ctx, const char *uci_option, const char *uci_value);

#endif							// UCI_API_H
