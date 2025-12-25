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
s.find("reference") # Finds the first index of the substring
s.rfind("reference") # Finds the last index of substring

s.startswith('hola') # Checks for a prefix
s.endswith('2026') # Checks for a suffix

s.count('icpc') # Counts the number of non overlapping occurrences
s.lower() # to lower
s.upper() # to upper

s.capitalize() # Capitalizes the word

c = 'a'
c.isalpha() # Is from alphabet

c='2'
c.isdigit() # Checks if it's a digit

c = '69'
c.isnumeric() # Checks if it is a number

# Slice a string (substring)

subs = s[2:5] # Substring from indices 2 to 5
rev = s[::-1] # Reverse a substring
step = s[::2] # Transform into every second character

c = 'z'
ord(c) # Unicode code point of the character
chr(65) # Reverse of ord