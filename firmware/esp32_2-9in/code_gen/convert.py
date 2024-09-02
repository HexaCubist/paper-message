from PIL import Image, ImageOps
import numpy as np
import os

def define_file(file_name):

    img = Image.open(file_name)
    data = np.array(img)
    data = 1 - data
    print(data)
    print(len(data[0]))
    bitpacked_array = np.packbits((data.flatten()))

    array_text = ""
    for elm in bitpacked_array:
        # Turn to hex
        array_text += f"0x{elm:02x},"


    file_name = file_name.split(".")[0]

    assert file_name.isalpha()

    var_name = f"IMAGE_{file_name.strip().upper()}"

    array_text = array_text[:-1]
    finalFile = f"#pragma once\nconst unsigned char {var_name}[] PROGMEM = {{\n{array_text}}};"

    with open(f"{file_name}.h", "w") as f:
        f.write(finalFile)

if __name__ == "__main__":
    for file in os.listdir():
        if file.endswith(".bmp"):
            define_file(file)