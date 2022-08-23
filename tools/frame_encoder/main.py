import binascii
from dataclasses import dataclass

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
    
const uint32_t %NAME%l[%RAMES%] PROGMEM = {%DATA_L%}; 

#endif
"""
    header_template = header_template.replace("%NAME_C%", name.upper())
    header_template = header_template.replace("%NAME%", name)
    header_template = header_template.replace("%RAMES%", str(len(filenames)))
    header_template = header_template.replace("%DATA_L%", sdata_l)
    header_template = header_template.replace("%DATA%", sdata)

    with open(f"tools\\frame_encoder\\output\\{name[:-2]}.h", "w") as text_file:
        text_file.write(header_template)
    

def complete_folder(name, folder, sub_folders, sub_file_num):
    for index, sub_fo in enumerate(sub_folders):
            filenames = [f'img\\{folder}\\{sub_fo}\\{sub_fo} {n}.png' for n in range(1,sub_file_num[index]+1)]
            create_header(f"{name.lower()}_{sub_fo.lower()}_i", filenames)

def complete_simple_folder(name, folder, filename, sub_file_num):
    filenames = [f'img\\{folder}\\{filename} {n}.png' for n in range(1,sub_file_num+1)]
    create_header(f"{name}_i", filenames)

def complete_single(name, folder, filename):
    filenames = [f'img\\{folder}\\{filename}.png']
    create_header(f"{name}_i", filenames)

complete_folder("colonise", "From scratch", ["Close", "Colonising", "Inject", "Insert", "Wipe"], [12] * 5)

complete_simple_folder("fruiting", "Fruiting", "Fruiting", 5)

complete_simple_folder("grow_ready", "Grow\\Ready", "Ready", 12)

# HELP

complete_single("help_lid", "Help", "Close lid")
complete_single("help_inject", "Help", "Inject spores")
complete_single("help_insert", "Help", "Insert bag into device")
complete_single("help_wipe", "Help", "Wipe injection port")

complete_folder("menu", "Menu", ["Dehydrate", "From Scratch", "Mycelium", "Settings"], [12] * 4)

complete_folder("mycelium", "Mycelium", ["Close", "Fruiting", "Insert"], [12] * 3)

complete_folder("settings", "Settings", ["Airflow", "Beep", "Colonisation", "Fruiting", "Light", "Temperature", "Time Period"], [10, 4, 5, 4, 10, 11, 50])


#complete_simple_folder("grow_ready", "Grow\\Ready", "Ready", 12)

#filenames = [f'img\\Menu\\Fruiting\\Fruiting {n}.png' for n in range(1,6)]
#create_header("menu_dehydrate", filenames)

#complete_folder("mycelium", "Fruiting", ["Close", "Colonising", "Inject", "Insert", "Wipe"], [12] * 5)


"""
sub_folders = ["Close", "Colonising", "Inject", "Inset", "Wipe"]
filenames = [f'img\\Menu\\Dehydrate\\Dehydrate {n}.png' for n in range(1,13)]
create_header("menu_dehydrate", filenames)

filenames = [f'img\\Menu\\From scratch\\From scratch {n}.png' for n in range(1,13)]
create_header("menu_colonise", filenames)

filenames = [f'img\\Menu\\Mycelium\\Mycelium {n}.png' for n in range(1,13)]
create_header("menu_mycelium", filenames)

filenames = [f'img\\Menu\\Settings\\Settings {n}.png' for n in range(1,13)]
create_header("menu_settings", filenames)

filenames = [f'img\\Menu\\Settings\\Settings {n}.png' for n in range(1,13)]
create_header("menu_settings", filenames)
"""