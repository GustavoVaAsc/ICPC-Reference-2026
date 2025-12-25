s = "  Hola reference  "
# Remove trailing/whitespaces
print(s.strip()) # also .lstrip and .rstrip
print(s.split()) # Separates by spaces on list

s = "hola,reference,icpc,2026"
print(s.split(',')) # Separate by character

strs = ['vamos', 'a','ganar','icpc']

# Join a list of strings
joined = ' '.join(strs)
print(joined)

print(s.replace('hola','adios')) # Replace substrings