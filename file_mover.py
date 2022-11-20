import os
import shutil

n = 9
i = 0
# Apparently absolute paths are required here

path = "C:/Users/BRMAX/repo/panocam/sources/04_binning2_1000us_gain0"

images = os.listdir("C:/Users/BRMAX/repo/panocam/sources/04_binning2_1000us_gain0")
for image in images:
    if image.lower().endswith(".png"):
        fullpath = os.path.join(path, image)
        if i == n:
            shutil.move(fullpath, "C:/Users/BRMAX/repo/panocam/sources/demo_dataset")
            i = 0
        else: 
            i += 1