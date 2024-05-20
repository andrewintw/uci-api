#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <uci.h>
#include "uci_api.h"

int uci_set_confdir(struct uci_context *ctx, const char *dir)
{
	if (uci_set_confdir(ctx, dir) != UCI_OK) {
		fprintf(stderr, "Failed to set custom UCI config directory.\n");
		return 1;
	}

	return UCI_OK;
}

char *get_uci_value(struct uci_context *ctx, const char *uci_option)
{
	struct uci_ptr ptr;
	char *value = NULL;

	if (UCI_OK != uci_lookup_ptr(ctx, &ptr, (char *) uci_option, true)) {
		uci_perror(ctx, __func__);
		goto cleanup;
	}

	if (ptr.o && ptr.o->v.string) {
		value = strdup(ptr.o->v.string);
		if (!value) {
			fprintf(stderr, "Failed to allocate memory for value.\n");
			goto cleanup;
		}
	} else {
		fprintf(stderr, "Failed to get UCI option value.\n");
		goto cleanup;
	}

  cleanup:
	if (!value) {
		value = strdup("");
	}
	return value;
}

int set_uci_value(struct uci_context *ctx, const char *uci_option, const char *uci_value)
{
	struct uci_ptr ptr;

	if (UCI_OK != uci_lookup_ptr(ctx, &ptr, (char *) uci_option, true)) {
		uci_perror(ctx, "uci_lookup_ptr");
		return 1;
	}

	if (ptr.o == NULL) {
		fprintf(stderr, "UCI option not found.\n");
		return 1;
	}

	ptr.value = uci_value;
	if (UCI_OK != uci_set(ctx, &ptr)) {
		uci_perror(ctx, "uci_set");
		return 1;
	}

	if (UCI_OK != uci_commit(ctx, &ptr.p, false)) {
		uci_perror(ctx, "uci_commit");
		return 1;
	}

	return UCI_OK;
}
