#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_NAME_SIZE 32

void count_max_link_depth(int recursive_depth) {
	char previous_file_name[BUFFER_NAME_SIZE];
	char current_file_name[BUFFER_NAME_SIZE];

	sprintf(previous_file_name, "rec_count_test%d", recursive_depth);
	sprintf(current_file_name, "rec_count_test%d", recursive_depth + 1);

	if (symlink(previous_file_name, current_file_name) != 0) {
		printf("Unknown error while creaing symlink. Terminating.\n");
		exit(-4);
	}
	
	++recursive_depth;

	int file_descriptor;
	if ((file_descriptor = open(current_file_name, O_RDWR | O_CREAT, 0666)) < 0) {
		printf("Max recursive link depth was reached. Creating more links is not possible.\n");
		printf("Result recursive depth = %d\n", recursive_depth - 1);
		if (remove(current_file_name) < 0) {
			printf("Unable to remove a link. Terminating.\n");
			exit(-5);
		}
		return;
	}
	
	if (close(file_descriptor) < 0) {
		printf("Unable to close the file. Terminating.\n");
		exit(-3);
	}

	count_max_link_depth(recursive_depth);
	
	if (remove(current_file_name) < 0) {
		printf("Unable to remove a link. Terminating.\n");
		exit(-5);
	}
}

int main() {
	char file_name[] = "rec_count_test0";
	int file_descriptor;

	if ((file_descriptor = open(file_name, O_RDWR | O_CREAT, 0666)) < 0) {
		printf("Unable to open the file. Terminating.\n");
		exit(-1);
	}
	
	if (close(file_descriptor) < 0) {
		printf("Unable to close the file.\n");
		exit(-2);
	}

	count_max_link_depth(0);
	if (remove(file_name) < 0) {
		printf("Unable to remove the initial file. Terminating.\n");
		exit(-6);
	}

	return 0;
}
