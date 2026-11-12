# Static Code Analysis Lab — Results and Comparison

## Source

- Language: C23
- Repository URL: [fill in]
- Date of scans: [fill in]
- GitHub CodeQL configuration/query suite: [fill in]
- Codacy enabled C analysis tools: [fill in]

## CodeQL findings

- Total alerts: [fill in]
- Alert examples (rule, file/line, severity): [fill in]
- Screenshot: `screenshots/codeql-results.png`

## Codacy findings

- Total issues: [fill in]
- Issue examples (rule, file/line, severity): [fill in]
- Screenshot: `screenshots/codacy-results.png`

## Direct comparison

| Intended vulnerability | CodeQL flagged it? | Codacy flagged it? | Notes |
| --- | --- | --- | --- |
| Stack buffer overflow (CWE-120) | | | |
| Heap allocation off by one (CWE-131) | | | |
| Uncontrolled format string (CWE-134) | | | |
| OS command injection (CWE-78) | | | |
| Use after free (CWE-416) | | | |
| Array out-of-bounds write (CWE-787) | | | |

## Reflection

1. Which issues were identified by both tools?
2. Which issues were only identified by one tool?
3. How did the severity labels and explanations differ?
4. What is the most important thing you learned about static analysis?
5. Why does a static analysis alert need human review?

**Important:** Fill this out using observed results, not the intended
vulnerability list. Scanner results may include additional findings or miss
some deliberate defects.
