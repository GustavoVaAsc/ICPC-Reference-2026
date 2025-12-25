The “must‑know” Python `re` functions (and their runtimes)

| # | Function | Typical use | Time complexity (average‑case) | Worst‑case | Notes |
|---|-----------|--------------|------------------------------|-----------|-------|
| 1 | `re.match(pattern, string, flags=0)` | Test if the *start* of `string` matches `pattern`. | **O(n)** (linear in the length of the part of the string examined) | **Exponential** if the pattern contains nested back‑tracking groups (`.*.*` etc.) | Most patterns are linear; the exponential blow‑up only happens with “catastrophic backtracking” |
| 2 | `re.search(pattern, string, flags=0)` | Find the *first* match anywhere in `string`. | **O(n)** (linear in the length of the string) | **Exponential** for the same reasons as `match` | Use when you don’t care where the match starts |
| 3 | `re.fullmatch(pattern, string, flags=0)` | Require the *entire* string to match. | **O(n)** | **Exponential** for pathological patterns | Equivalent to `^pattern$` but usually faster |
| 4 | `re.compile(pattern, flags=0)` | Pre‑compile a pattern for reuse. | **O(m)** where *m* is the pattern length | **Exponential** for the same reason as above | Compile once, call many times – huge speed win |
| 5 | `re.findall(pattern, string, flags=0)` | Return a list of *all* non‑overlapping matches. | **O(n)** | **Exponential** if pattern backtracks | Use when you only need the substrings, not the match objects |
| 6 | `re.finditer(pattern, string, flags=0)` | Return an iterator of `Match` objects (lazy). | **O(n)** | **Exponential** | Prefer for streaming / huge strings |
| 7 | `re.split(pattern, string, maxsplit=0, flags=0)` | Split `string` at every match of `pattern`. | **O(n)** | **Exponential** | `maxsplit` limits the number of splits |
| 8 | `re.sub(pattern, repl, string, count=0, flags=0)` | Replace all (or first `count`) matches with `repl`. | **O(n)** (plus the cost of building the replacement) | **Exponential** if the pattern backtracks | `repl` may be a string or a callable |
| 9 | `re.subn(pattern, repl, string, count=0, flags=0)` | Same as `sub`, but also returns the number of substitutions. | **O(n)** | **Exponential** | Useful if you want the replacement count |
|10 | `re.escape(string)` | Escape all regex metacharacters in a literal string. | **O(m)** where *m* is the input length | **Linear** | Handy when you want to use a user‑supplied string literally |
|11 | `re.finditer` + `match.group()` | Extract captured groups lazily. | **O(n)** | **Exponential** | Each group extraction is *O(1)*; the search itself dominates |
|12 | `re.Scanner` (rare) | Perform multiple patterns in a single pass. | **O(n)** | **Exponential** for patterns that backtrack | Good for tokenizers (lexers) |

> **General rule of thumb**
> *If your pattern does not contain nested quantifiers or back‑references, the engine runs in **linear time** in the length of the input string.*
> *If you do have nested `*`, `+`, `{m,n}` or back‑references, the worst‑case becomes **exponential** – this is the “catastrophic backtracking” phenomenon.*

### Why the exponential blow‑up happens

Python’s regex engine is a **back‑tracking NFA**.
When the engine tries a branch (e.g., a `.` that can match any character) it keeps a stack of alternatives. If the branch fails later, it **pops** to the previous branch and tries the next alternative.
If a pattern has *k* nested alternations, the number of states explored can be as high as **2ᵏ**.

Typical examples:

```python
pattern = r'^(a+)+$'          # matches only "a", but the engine explores 2^(len(s)) possibilities
```

> **Tip** – If you ever hit a “too slow” regex, try to rewrite it so that the number of back‑tracking branches is bounded or replace it with a deterministic automaton (e.g., use `re.fullmatch(r'[a-z]+')` instead of `re.match(r'.*')`).

### Pre‑compilation matters

```python
pat = re.compile(r'\bfoo\b')
for line in sys.stdin:
    if pat.search(line):
        ...
```

*Compiling once* keeps the **O(m)** cost to a single place, then every call to `search`, `match`, or `sub` runs in *O(n)*.

### Quick‑reference cheat‑sheet

```python
import re

# 1. Basic matching
re.match(r'foo', 'foobar')          # <re.Match object>
re.search(r'bar', 'foobar')         # <re.Match object>
re.fullmatch(r'foo', 'foo')        # <re.Match object>

# 2. Find all / finditer
re.findall(r'\d+', 'a12b34')        # ['12', '34']
re.finditer(r'\d+', 'a12b34')       # iterator over <Match> objects

# 3. Replace
re.sub(r'\d+', '#', 'a12b34')       # 'a#b#'
re.subn(r'\d+', '#', 'a12b34')     # ('a#b#', 2)

# 4. Split
re.split(r'\W+', 'a,b;c')           # ['a', 'b', 'c']

# 5. Escape a literal
re.escape(r'foo.bar*')              # 'foo\\.bar\\*'

# 6. Pre‑compile
pat = re.compile(r'\bfoo\b')
for line in sys.stdin:
    if pat.search(line):
        ...
```

### Summary of complexities

| Function | Avg. time | Worst‑case | Typical pattern | When you should be careful |
|----------|------------|------------|-----------------|----------------------------|
| `match`, `search`, `fullmatch` | O(n) | 2^k (k = nested quantifiers) | Simple anchors, fixed literals | Patterns with `.*`, `.+`, or back‑references |
| `findall`, `finditer` | O(n) | 2^k | Non‑overlapping matches | Same as above |
| `split` | O(n) | 2^k | Separator patterns | Avoid `.+?` inside the separator |
| `sub`, `subn` | O(n) | 2^k | Replacement string or callable | Replacement that triggers a new search inside the replacement can amplify the cost |
| `escape` | O(m) | O(m) | Any literal | None |
| `compile` | O(m) | 2^k (in compile) | Pattern parsing | Pre‑compile once per program run |

> **Bottom line** – For the vast majority of CP problems you will never hit the exponential worst‑case.  Just avoid nested quantifiers or back‑references, and you’re safely in linear‑time territory.  When you do need them, test the regex on a few worst‑case inputs to be sure it runs in time.