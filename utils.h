/* utils.h - shared constants and input/validation helpers
 * Used by every module. Owner: Diogenus A. (Functions, Integration, Data Validation)
 */
#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/* ---- Shared size limits ---- */
#define NAME_LEN        50
#define EMAIL_LEN       50
#define PHONE_LEN       20
#define COND_LEN        30
#define MAX_EMPLOYEES   100
#define MAX_BUDGETS     50
#define MAX_SUPPLIERS   100
#define MAX_ASSETS      100

/* ---- Reading input safely ---- */
int    readLine(char *buffer, size_t size);          /* 1 = ok, 0 = line was too long */
void   trim(char *text);                              /* remove leading/trailing spaces */

/* ---- Prompts that keep asking until the input is valid ---- */
int    promptInt(const char *prompt, int min, int max);
double promptMoney(const char *prompt);               /* rejects negative / non-numeric */
void   promptText(const char *prompt, char *dest, size_t size);   /* rejects empty / too long */
void   promptEmail(const char *prompt, char *dest, size_t size);
void   promptPhone(const char *prompt, char *dest, size_t size);

/* ---- String helpers (built on string.h) ---- */
int    isValidEmail(const char *email);
int    isValidPhone(const char *phone);
int    equalsIgnoreCase(const char *a, const char *b);
int    containsIgnoreCase(const char *text, const char *part);
int    buildLabel(char *dest, size_t size, const char *first,
                  const char *separator, const char *second);

#endif
