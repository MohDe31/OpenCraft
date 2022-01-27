from PIL import Image
import numpy as np


print(np.array(Image.open('res/textures/smooth.png')).shape)
print(np.array(Image.open('res/textures/smooth.png').resize((160, 160)).save("res/textures/smooth.png")).shape)

#Image.open('../res/textures/sand.webp').save('../res/textures/sand.png')