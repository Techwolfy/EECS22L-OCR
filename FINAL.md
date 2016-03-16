Final Version of EECS22L-OCR
============================

Features
--------

### Preprocessing

* Black and White Conversion
* Image Crop
* Stain Removal
* Image Rotation
* Save Image


### OCR

* Capability to convert an image of text to text format


### Post Processing

* Dictionary Support
* Text Editor
* Save Text


Improvements
------------

* Improved character comparison algorithm
* Added dictionary support
* Added AutoCrop feature
* Added command-line interface


Limitations
-----------

* The OCR does not correctly identify all characters; the percentage correct is highly dependent on the way the image is cropped. 
* The image must also have Black and White conversion performed on it beforehand.
* The AutoCrop does not always crop images to their optimal size.
* The image text must be 12 pt Courier font.
* The text cannot be slanted, that is, the angle with the horizontal must be zero degrees. Otherwise, it must be rotated manually.
* The OCR may not work properly if the image width and height is not a multiple of 30 and 56 respectively.
* The optimal cropping coordinates for the provided "01_HelloWorld_Clean300DPI.jpg" are 296,309,1586,1317.
* If the image is cropped to 200,270,1650,1500 then AutoCrop will properly crop the remainder.
