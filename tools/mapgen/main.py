import json

# hvce

j = None

with open('testmap.json') as f:
    c = f.read()
    j = json.loads(c)
    
layers = j['layers']

buffer = ""

l = layers[0]

width = l['width']
height = l['height']
d = l['data']
for x in range(width):
    for y in range(height):
        tmid_raw = d[y*width + x]
        tmid_b = format(tmid_raw, "032b")
        flag_h = tmid_b[0]
        flag_v = tmid_b[1]
        flag_d = tmid_b[2]
        b = tmid_b[-14:]
        
        o = ""
        o += b
        o += flag_h
        o += flag_v
        buffer += o
                
print(buffer)
with open("map.bin", 'w') as f:
    f.write(buffer)