
import cv2
import matplotlib.pyplot as plt

# Get image and cascade names
imagePath = r"C:\Users\ASUS\Downloads\AdobeStock_614124314.cropimg.width=335.crop=portrait.jpeg"
cascPath = cv2.data.haarcascades + "haarcascade_frontalface_default.xml"

# Create the haar cascade
faceCascade = cv2.CascadeClassifier(cascPath)

# Read the image
image = cv2.imread(imagePath)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Convert BGR to RGB
RGB_img = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

plt.imshow(RGB_img)
plt.show()

# Detect faces in the image
faces = faceCascade.detectMultiScale(
    gray,
    scaleFactor=1.1,
    minNeighbors=5,
    minSize=(30, 30),
    flags=cv2.CASCADE_SCALE_IMAGE
)

print("Found {0} faces!".format(len(faces)))

# Draw a rectangle around the faces
for (x, y, w, h) in faces:
    cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), 2)

# Convert BGR to RGB
RGB_img = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

plt.imshow(RGB_img)
plt.show()

#python face_detect.py