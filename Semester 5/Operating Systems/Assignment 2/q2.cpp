#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>

using namespace std;

#define BUFFER_SIZE 256

void restoreFD(int saved_stdout, int saved_stderr) {
    dup2(saved_stdout, STDOUT_FILENO);
    dup2(saved_stderr, STDERR_FILENO);
    close(saved_stdout);
    close(saved_stderr);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <input file> <output file> <error file>\n";
        return 1;
    }

    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd < 0) {
        cerr << "Error: Cannot open input file: " << strerror(errno) << endl;
        return 1;
    }

    int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        cerr << "Error: Cannot open output file: " << strerror(errno) << endl;
        close(input_fd);
        return 1;
    }

    int error_fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (error_fd < 0) {
        cerr << "Error: Cannot open error file: " << strerror(errno) << endl;
        close(input_fd);
        close(output_fd);
        return 1;
    }

    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stderr = dup(STDERR_FILENO);
    dup2(output_fd, STDOUT_FILENO);
    dup2(error_fd, STDERR_FILENO);

    char buffer[BUFFER_SIZE];
    int bytes_read;
    cout << "Processing input file..." << endl;

    while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0) {
        int i = 0;
        while (i < bytes_read) {
            char* endptr;
            while (i < bytes_read && (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t')) {
                i++;
            }

            if (i < bytes_read) {
                char* num_start = &buffer[i];
                long num = strtol(num_start, &endptr, 10);

                if (num_start == endptr) {
                    char invalid_entry[BUFFER_SIZE];
                    int length = 0;

                    while (i < bytes_read && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\t') {
                        invalid_entry[length++] = buffer[i++];
                    }
                    invalid_entry[length] = '\0';

                    cerr << "Error: Invalid number format for '" << string(invalid_entry) << "'\n";
                } else {
                    i += (endptr - num_start);
                    cout << "Read number: " << num << endl;
                    if (num == 0) {
                        cout << "Error: Division by zero encountered.\n";
                        cerr << "Error: Division by zero encountered.\n";
                    } else {
                        cout << "Processed number: " << (100 / num) << endl;
                    }
                }
            }
        }
    }

    restoreFD(saved_stdout, saved_stderr);
    cout << "File descriptors restored. Process complete." << endl;
    close(input_fd);
    close(output_fd);
    close(error_fd);

    return 0;
}

