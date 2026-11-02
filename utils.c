/* utils.c - shared input/validation helpers
 * Owner: Diogenus A. (Functions, Integration, Data Validation)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include "utils.h"

#define SCRATCH_LEN 256

/* Read one line with fgets (never overflows). Strips the newline.
 * Returns 1 if the whole line fitted, 0 if it was too long (rest is discarded).
 * If input ends (Ctrl+Z / Ctrl+D / piped file finished) the program exits cleanly,
 * so an input loop can never spin forever. */
int readLine(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (fgets(buffer, (int)size, stdin) == NULL) {
        printf("\nInput ended. Exiting MFMS.\n");
        exit(EXIT_SUCCESS);
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return 1;
    }
    if (length < size - 1) {          /* no newline but buffer not full: last line, no \n */
        return 1;
    }
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* throw away the rest of an over-long line */
    }
    return 0;
}

void trim(char *text)
{
    size_t end = strlen(text);
    size_t start = 0;

    while (end > 0 && isspace((unsigned char)text[end - 1])) {
        end--;
    }
    text[end] = '\0';

    while (text[start] != '\0' && isspace((unsigned char)text[start])) {
        start++;
    }
    if (start > 0) {
        memmove(text, text + start, strlen(text + start) + 1);
    }
}

/* Copy src to dest in lower case (dest is always null-terminated). */
static void toLowerCopy(char *dest, size_t size, const char *src)
{
    size_t i;
    for (i = 0; i + 1 < size && src[i] != '\0'; i++) {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

int equalsIgnoreCase(const char *a, const char *b)
{
    char lowerA[SCRATCH_LEN];
    char lowerB[SCRATCH_LEN];

    toLowerCopy(lowerA, sizeof lowerA, a);
    toLowerCopy(lowerB, sizeof lowerB, b);
    return strcmp(lowerA, lowerB) == 0;
}

int containsIgnoreCase(const char *text, const char *part)
{
    char lowerText[SCRATCH_LEN];
    char lowerPart[SCRATCH_LEN];

    toLowerCopy(lowerText, sizeof lowerText, text);
    toLowerCopy(lowerPart, sizeof lowerPart, part);
    return strstr(lowerText, lowerPart) != NULL;
}

/* Join first + separator + second into dest using strcpy/strcat.
 * Returns 1 on success, 0 (dest left empty) if the result would not fit. */
int buildLabel(char *dest, size_t size, const char *first,
               const char *separator, const char *second)
{
    if (strlen(first) + strlen(separator) + strlen(second) >= size) {
        dest[0] = '\0';
        return 0;
    }
    strcpy(dest, first);
    strcat(dest, separator);
    strcat(dest, second);
    return 1;
}

/* A whole number between min and max. Letters, blanks and out-of-range
 * values are rejected with a message and the user is asked again. */
int promptInt(const char *prompt, int min, int max)
{
    char line[64];
    char *end;
    long value;

    for (;;) {
        printf("%s", prompt);
        if (!readLine(line, sizeof line)) {
            printf("  Error: input is too long.\n");
            continue;
        }
        trim(line);
        if (strlen(line) == 0) {
            printf("  Error: input cannot be empty.\n");
            continue;
        }
        errno = 0;
        value = strtol(line, &end, 10);
        if (*end != '\0') {
            printf("  Error: please enter a whole number.\n");
            continue;
        }
        if (errno == ERANGE || value < min || value > max) {
            printf("  Error: please enter a number between %d and %d.\n", min, max);
            continue;
        }
        return (int)value;
    }
}

/* A non-negative amount of money (salary, budget, value, expenditure). */
double promptMoney(const char *prompt)
{
    char line[64];
    char *end;
    double value;

    for (;;) {
        printf("%s", prompt);
        if (!readLine(line, sizeof line)) {
            printf("  Error: input is too long.\n");
            continue;
        }
        trim(line);
        if (strlen(line) == 0) {
            printf("  Error: input cannot be empty.\n");
            continue;
        }
        value = strtod(line, &end);
        if (*end != '\0' || !isfinite(value)) {
            printf("  Error: please enter a valid number.\n");
            continue;
        }
        if (value < 0) {
            printf("  Error: the value cannot be negative.\n");
            continue;
        }
        if (value > 1000000000000.0) {
            printf("  Error: the value is too large.\n");
            continue;
        }
        return value;
    }
}

/* Text that must not be empty and must fit in dest. */
void promptText(const char *prompt, char *dest, size_t size)
{
    char line[SCRATCH_LEN];

    for (;;) {
        printf("%s", prompt);
        if (!readLine(line, sizeof line)) {
            printf("  Error: input is too long.\n");
            continue;
        }
        trim(line);
        if (strlen(line) == 0) {
            printf("  Error: this field cannot be empty.\n");
            continue;
        }
        if (strlen(line) >= size) {
            printf("  Error: maximum %d characters allowed.\n", (int)size - 1);
            continue;
        }
        strcpy(dest, line);       /* safe: length was checked above */
        return;
    }
}

/* Very simple email check: something@something.something, no spaces. */
int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');
    const char *dot;

    if (at == NULL || at == email) {
        return 0;                                  /* no @, or nothing before it */
    }
    if (strchr(at + 1, '@') != NULL || strchr(email, ' ') != NULL) {
        return 0;                                  /* second @ or a space */
    }
    dot = strrchr(at + 1, '.');
    if (dot == NULL || dot == at + 1 || dot[1] == '\0') {
        return 0;                                  /* need text, a dot, then text */
    }
    return 1;
}

/* Phone numbers: digits, spaces, + and -, with 7 to 15 digits. */
int isValidPhone(const char *phone)
{
    size_t i;
    int digits = 0;

    for (i = 0; i < strlen(phone); i++) {
        if (isdigit((unsigned char)phone[i])) {
            digits++;
        } else if (phone[i] != '+' && phone[i] != ' ' && phone[i] != '-') {
            return 0;
        }
    }
    return digits >= 7 && digits <= 15;
}

void promptEmail(const char *prompt, char *dest, size_t size)
{
    char temp[EMAIL_LEN];

    for (;;) {
        promptText(prompt, temp, sizeof temp);
        if (isValidEmail(temp)) {
            break;
        }
        printf("  Error: enter a valid email such as name@example.com.\n");
    }
    if (strlen(temp) < size) {
        strcpy(dest, temp);
    }
}

void promptPhone(const char *prompt, char *dest, size_t size)
{
    char temp[PHONE_LEN];

    for (;;) {
        promptText(prompt, temp, sizeof temp);
        if (isValidPhone(temp)) {
            break;
        }
        printf("  Error: use 7-15 digits (spaces, + and - allowed).\n");
    }
    if (strlen(temp) < size) {
        strcpy(dest, temp);
    }
}
