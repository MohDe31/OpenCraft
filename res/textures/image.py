from PIL import Image
import numpy as np



print(np.array(Image.open('../res/textures/emoji.jpeg').resize((160, 160)).save("../res/textures/emoji.png")).shape)

#Image.open('../res/textures/sand.webp').save('../res/textures/sand.png')