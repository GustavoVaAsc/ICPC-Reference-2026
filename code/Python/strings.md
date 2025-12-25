## 1.  Input / Output helpers

| Utility | What it does | One‑liner |
|---------|---------------|-----------|
| `input()` | Reads a whole line (string) | `s = input()` |
| `input().split()` | Split on whitespace | `parts = input().split()` |
| `map(int, input().split())` | Convert to ints | `nums = list(map(int, input().split()))` |
| `sys.stdin.read()` | Read entire stdin (fast for huge data) | `data = sys.stdin.read()` |
| `print(*args, sep=' ', end='\n')` | Flexible printing | `print('Case', case, ':', ans)` |

> **Tip**: `sys.setrecursionlimit(10**7)` for deep recursion, and `sys.stdin = open('input.txt', 'r')` if you use local files.

---

## 2.  Basic string operations

| Method | Typical use | Example |
|--------|--------------|---------|
| `.strip()` | Remove leading/trailing whitespace | `s = s.strip()` |
| `.lstrip()` / `.rstrip()` | Remove only left/right side | `s = s.lstrip()` |
| `.split()` | Split on any whitespace | `tokens = s.split()` |
| `.split(delim)` | Split on a specific delimiter | `rows = s.split('\n')` |
| `.join()` | Join a list of strings | `ans = ' '.join(words)` |
| `.replace(old, new)` | Substring replacement | `s = s.replace('foo', 'bar')` |
| `.find(sub)` | First index of `sub` (or -1) | `pos = s.find('abc')` |
| `.rfind(sub)` | Last index of `sub` | `pos = s.rfind('xyz')` |
| `.index(sub)` / `.rindex(sub)` | Same as `find` but raises `ValueError` | `pos = s.index('abc')` |
| `.startswith(prefix)` / `.endswith(suffix)` | Test prefix / suffix | `if s.startswith('pre'): …` |
| `.count(sub)` | Number of non‑overlap occurrences | `cnt = s.count('a')` |
| `.lower()`, `.upper()` | Case conversion | `s = s.lower()` |
| `.capitalize()`, `.title()` | Title‑case | `s = s.title()` |
| `.isalpha()`, `.isdigit()`, `.isnumeric()` | Character checks | `if s.isdigit(): …` |

> **Why they matter** – almost every CP problem involves parsing, trimming, or simple transformations; these methods are constant‑time or linear in the string length and are battle‑tested.

---

## 3.  Slicing & reversing

| Operation | Syntax | Example |
|-----------|--------|---------|
| Slice | `s[a:b]` | `sub = s[2:5]` |
| Whole string | `s[:]` | `copy = s[:]` |
| Reverse | `s[::-1]` | `rev = s[::-1]` |
| Step | `s[::k]` | `every_second = s[::2]` |
| Negative indices | `s[-1]` | `last_char = s[-1]` |

> **Use case** – palindrome checks, rotations, or simply extracting a substring.

---

## 4.  Character utilities

| Function | What it does | Example |
|----------|---------------|---------|
| `ord(char)` | Unicode code point | `code = ord('A')` |
| `chr(code)` | Reverse of `ord` | `c = chr(65)` |
| `string.ascii_letters`, `string.digits` | Pre‑defined sets | `if c in string.digits: …` |
| `re.sub(pattern, repl, s)` | Regex replacement | `s = re.sub(r'\d+', '0', s)` |

> **Regex** can be a power‑tool when the pattern is non‑trivial, e.g. matching all “ab” blocks or validating a phone number format.

---