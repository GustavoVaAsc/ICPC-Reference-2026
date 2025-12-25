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