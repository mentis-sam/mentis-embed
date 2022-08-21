import binascii
from dataclasses import dataclass

filename = 'img\\UI Screens (2)\\Menu\\From scratch\\From scratch 1.jpg'

def convert_file(filename):
    with open(filename, 'rb') as f:
        content = f.read()

    data = binascii.hexlify(content, ",", 1).decode("utf-8")

    data = data.replace(",", ", 0x")
    data = "0x" + data

    return data, data.count(",")+1

def create_header(name, filenames):

    data = []
    data_l = []

    for filename in filenames:
        temp_data, temp_data_l = convert_file(filename)

        data.append(temp_data)
        data_l.append(temp_data_l)

    sdata = ','.join(map(str, data)) 
    sdata_l = ','.join(map(str, data_l)) 

    header_template = \
"""#ifndef %NAME_C%_H
#define %NAME_C%_H

#include <pgmspace.h>
#include <stdint.h>

const uint8_t %NAME%[] PROGMEM = 
{%DATA%}; 
    
const uint32_t %NAME%_l[%RAMES%] PROGMEM = {%DATA_L%}; 

#endif
"""
    header_template = header_template.replace("%NAME_C%", name.upper())
    header_template = header_template.replace("%NAME%", name)
    header_template = header_template.replace("%RAMES%", str(len(filenames)))
    header_template = header_template.replace("%DATA_L%", sdata_l)
    header_template = header_template.replace("%DATA%", sdata)

    with open(f"tools\\frame_encoder\\output\\{name}.h", "w") as text_file:
        text_file.write(header_template)
    
#filenames = [f'img\\UI Screens (2)\\Menu\\From scratch\\From scratch {n}.png' for n in range(1,13)]
#create_header("colonise", filenames)

filenames = [f'img\\UI Screens (2)\\Menu\\Dehydrate\\Dehydrate {n}.png' for n in range(1,13)]
create_header("menu_dehydrate", filenames)