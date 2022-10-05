
from PIL import Image
from PIL import ImageChops
import glob

#THIS WILL NOT WORK IN ANOTHER FOLDER!!!


#print(glob.glob("/Users/samcoleman/Documents/GitHub/mentis-embed/img-original/**/*.png", recursive=True))

#glob.iglob(image_folder_path + '**/*.png', recursive=True)
def offset_image(file):
    
    im_1 = Image.open(file)

    # adjust width and height to desired size
    dx = 8

    im_2 = ImageChops.offset(im_1, dx, 0)

    im_2.save("/Users/samcoleman/Documents/GitHub/mentis-embed/img"+file[60:])
    

for image_path in glob.iglob("/Users/samcoleman/Documents/GitHub/mentis-embed/img-original/**/*.png", recursive=True):
    offset_image(image_path)
