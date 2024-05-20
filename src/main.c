#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "uci_api.h"

int main(int argc, char *argv[])
{
	struct uci_context *ctx;

#if 0
	const char *custom_confdir = "/etc/config";

	if (access(custom_confdir, F_OK) == -1) {
		fprintf(stderr, "UCI config directory does not exist: %s\n", custom_confdir);
		return 1;
	}
#endif

	ctx = uci_alloc_context();
	if (!ctx) {
		fprintf(stderr, "Failed to allocate UCI context.\n");
		return 1;
	}
#if 0
	if (uci_set_confdir(ctx, custom_confdir) != UCI_OK) {
		uci_free_context(ctx);
		return 1;
	}
#endif

	if (argc == 2) {
		char *uci_option = argv[1];
		char *value = get_uci_value(ctx, uci_option);

		if (value) {
			printf("UCI Value: %s\n", value);
			free(value);
		} else {
			fprintf(stderr, "Failed to retrieve UCI value.\n");
		}
	} else if (argc == 3) {
		char *uci_option = argv[1];
		char *uci_value = argv[2];

		if (set_uci_value(ctx, uci_option, uci_value) == UCI_OK) {
			printf("Successfully set UCI value.\n");
		} else {
			fprintf(stderr, "Failed to set UCI value.\n");
		}
	} else {
		fprintf(stderr, "Usage: %s <uci_option> [uci_value]\n", argv[0]);
		uci_free_context(ctx);
		return 1;
	}

	uci_free_context(ctx);

	return 0;
}
