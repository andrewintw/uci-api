#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <uci.h>
#include "uci_api.h"

#if 0
int uci_set_confdir(struct uci_context *ctx, const char *dir)
{
	if (ctx == NULL || dir == NULL) {
		fprintf(stderr, "Invalid context or directory.\n");
		return 1;
	}

	if (uci_set_confdir(ctx, dir) != UCI_OK) {
		fprintf(stderr, "Failed to set custom UCI config directory.\n");
		return 1;
	}

	return UCI_OK;
}
#endif

char *get_uci_value(struct uci_context *ctx, const char *uci_option)
{
	struct uci_ptr ptr;
	char *value = NULL;
	char *tuple_str = NULL;

	tuple_str = strdup(uci_option);
	if (!tuple_str) {
		fprintf(stderr, "Failed to allocate memory for tuple_str.\n");
		goto cleanup;
	}

	if (UCI_OK != uci_lookup_ptr(ctx, &ptr, tuple_str, true)) {
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

	if (tuple_str) {
		free(tuple_str);
	}
	return value;
}

int set_uci_value(struct uci_context *ctx, const char *uci_option, const char *uci_value)
{
	struct uci_ptr ptr;
	char *tuple_str = NULL;
	int ret = 1;

	tuple_str = strdup(uci_option);
	if (!tuple_str) {
		fprintf(stderr, "Failed to allocate memory for tuple_str.\n");
		return 1;
	}

	if (UCI_OK != uci_lookup_ptr(ctx, &ptr, tuple_str, true)) {
		uci_perror(ctx, "uci_lookup_ptr");
		goto cleanup;
	}

	if (ptr.o == NULL) {
		fprintf(stderr, "UCI option not found.\n");
		goto cleanup;
	}

	ptr.value = uci_value;
	if (UCI_OK != uci_set(ctx, &ptr)) {
		uci_perror(ctx, "uci_set");
		goto cleanup;
	}

	if (UCI_OK != uci_commit(ctx, &ptr.p, false)) {
		uci_perror(ctx, "uci_commit");
		goto cleanup;
	}

	ret = UCI_OK;

  cleanup:
	if (tuple_str) {
		free(tuple_str);
	}

	return ret;
}
