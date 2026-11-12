# C Static Analysis Lab

An intentionally vulnerable **ISO C23** program created for a software
verification and validation lab comparing **GitHub CodeQL** and **Codacy**.

> **WARNING**: This project intentionally contains unsafe memory operations,
> uncontrolled input formatting, and shell command construction. It is for
> **static inspection only**. Do not execute it with `--unsafe`, deploy it, or
> use the vulnerable functions in production software.

## C23 features

The source uses the C23 `bool` keyword without `<stdbool.h>`, the `nullptr`
keyword for null-pointer comparisons, and a message-free `static_assert`.
These language features do not change the intentional vulnerabilities.

**Tool compatibility:** CodeQL lists C23 support as **beta**; Codacy supports
C scanning, but individual analyzers may vary in their C23 language support.
CodeQL default setup normally does not need to compile C source.

## Vulnerabilities included

| Function | Intended weakness | CWE |
| --- | --- | --- |
| `demonstrate_stack_overflow` | Unbounded `strcpy` into small stack buffer | CWE-120 |
| `demonstrate_heap_overflow` | `malloc(strlen(input))` omits NUL byte | CWE-131 |
| `demonstrate_format_string` | User-controlled `printf` format | CWE-134 |
| `demonstrate_command_injection` | User input inserted into `system` command | CWE-78 |
| `demonstrate_use_after_free` | `puts` after `free` | CWE-416 |
| `demonstrate_out_of_bounds_write` | Writes beyond a four-element array | CWE-787 |

These are **intended** weaknesses, not a promise that every scanner will flag
all six. Detected issues depend on tool versions, enabled rules, and analysis
settings. Source locations are in `src/main.c`.

## CodeQL scan (GitHub)

1. Publish the repository **publicly** on GitHub.
2. Open repository **Settings > Advanced Security**.
3. Under **CodeQL analysis**, choose **Set up > Default**.
4. Confirm C/C++ is selected and enable CodeQL. For a broader experiment,
   choose the `security-and-quality` query suite if available.
5. After analysis, inspect **Security > Code scanning** and record findings.
6. Capture a screenshot of the CodeQL results.

GitHub CodeQL default setup supports buildless analysis of C/C++ source.
You do not need to compile or run the program for this lab.

## Codacy scan

1. Visit https://www.codacy.com/ and sign in using GitHub.
2. Add this repository under your Codacy organization/account.
3. Wait for the initial scan and review the **Issues** page.
4. Review enabled C analysis tools (for example Cppcheck or Flawfinder).
5. Capture a screenshot of the findings.

## Comparing results

Fill in the table in `REPORT_TEMPLATE.md` based on the **actual** alerts
reported by each service. An alert count alone does not establish correctness
or tool quality, since the scanners use different rule sets.

## Optional compile-only verification

This code does not need to execute for static analysis. If a C compiler is
installed, a syntax-only check can be done with:

```sh
gcc -std=c23 -fsyntax-only src/main.c
```

Use a compiler with C23 support (for example, GCC 14 or newer).
On Windows, run this from an MSYS2 UCRT64 shell with GCC installed, or use
`clang -std=c23 -fsyntax-only src/main.c` if Clang supports C23.
Compiler warnings about intentional flaws are expected. **Do not run** the
`--unsafe` branch.

## Assignment scope

The class handout specifies the Python project
`mpirnat/lets-be-bad-guys`. This C project is an **alternative** designed to
exercise the same two scanning platforms and comparison objective; obtain
instructor approval before submitting it as a substitute.
