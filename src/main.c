#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "uci_api.h"

int main(int argc, char *argv[])
{
	static struct uci_context *ctx = NULL;

	ctx = uci_alloc_context();
	if (!ctx) {
		fprintf(stderr, "Failed to allocate UCI context.\n");
		return 1;
	}

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

		if (set_uci_value(ctx, uci_option, uci_value) == 0) {
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
