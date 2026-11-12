/*
 * C Static Analysis Lab
 *
 * WARNING: This file contains DELIBERATE security vulnerabilities for
 * educational static analysis. Do not execute the --unsafe mode.
 * Do not reuse any vulnerable functions in real software.
 *
 * Standard: ISO C23
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME_SIZE 16
#define COMMAND_SIZE 256

/* C23 permits static_assert without a message. */
static_assert(USERNAME_SIZE > 1);

/**
 * Demonstrates an unchecked copy into a fixed-size stack buffer.
 * CWE-120: Classic Buffer Overflow.
 */
static void demonstrate_stack_overflow(const char *input)
{
    char username[USERNAME_SIZE];

    strcpy(username, input); /* Intentionally unsafe: no bounds checking. */
    printf("Username: %s\n", username);
}

/**
 * Demonstrates allocating no space for a string's terminating null byte.
 * CWE-131: Incorrect Calculation of Buffer Size.
 */
static void demonstrate_heap_overflow(const char *input)
{
    size_t length = strlen(input);
    char *copy = malloc(length); /* Intentionally missing +1 for '\0'. */

    if (copy == nullptr)
    {
        return;
    }

    strcpy(copy, input); /* Writes the null byte beyond the allocation. */
    puts(copy);
    free(copy);
}

/**
 * Demonstrates interpreting user input as a printf format string.
 * CWE-134: Use of Externally-Controlled Format String.
 */
static void demonstrate_format_string(const char *input)
{
    printf(input); /* Intentionally unsafe: input controls format specifiers. */
    putchar('\n');
}

/**
 * Demonstrates constructing a shell command with untrusted input.
 * CWE-78: Improper Neutralization of Special Elements in an OS Command.
 */
static void demonstrate_command_injection(const char *input)
{
    char command[COMMAND_SIZE];

    (void)snprintf(command, sizeof(command), "echo %s", input);
    (void)system(command); /* Intentionally unsafe: invokes a shell. */
}

/**
 * Demonstrates accessing dynamically allocated memory after it is freed.
 * CWE-416: Use After Free.
 */
static void demonstrate_use_after_free(void)
{
    char *message = malloc(32);

    if (message == nullptr)
    {
        return;
    }

    strcpy(message, "temporary message");
    free(message);
    puts(message); /* Intentionally unsafe: dangling pointer. */
}

/**
 * Demonstrates writing one element past a statically sized array.
 * CWE-787: Out-of-bounds Write.
 */
static void demonstrate_out_of_bounds_write(void)
{
    int scores[4] = { 75, 80, 85, 90 };

    scores[4] = 100; /* Intentionally unsafe: indexes 0 through 3 only. */
    printf("Extra score: %d\n", scores[4]);
}

/**
 * Prints usage information by default; unsafe examples require an explicit
 * flag solely to maintain detectable input-to-sink flows for static analysis.
 */
int main(int argc, char *argv[])
{
    /* bool is a built-in keyword in C23; no <stdbool.h> needed. */
    bool unsafe_requested = argc == 3 && strcmp(argv[1], "--unsafe") == 0;

    if (!unsafe_requested)
    {
        puts("C Static Analysis Lab: deliberately vulnerable examples.");
        puts("For code scanning only. Do not run with --unsafe.");
        return EXIT_SUCCESS;
    }

    /* WARNING: DO NOT RUN this educational branch. */
    demonstrate_stack_overflow(argv[2]);
    demonstrate_heap_overflow(argv[2]);
    demonstrate_format_string(argv[2]);
    demonstrate_command_injection(argv[2]);
    demonstrate_use_after_free();
    demonstrate_out_of_bounds_write();

    return EXIT_SUCCESS;
}
