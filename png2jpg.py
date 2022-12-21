from pathlib import Path
from PIL import Image

inputPath = Path("/Users/maxbretschneider/Desktop/dataset_full")
inputFiles = inputPath.glob("**/*.png")
outputPath = Path("/Users/maxbretschneider/Desktop/Development/panocam/sources/04jpg")
for f in inputFiles:
    outputFile = outputPath / Path(f.stem + ".jpg")
    im = Image.open(f)
    im.save(outputFile)