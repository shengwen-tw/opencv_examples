import cv2
import numpy as np

cap = cv2.VideoCapture(1)

while True:
    ret, img = cap.read()

    #img = cv2.resize(img,(500,500))
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    #gray = 255 -gray
    ret,thresh = cv2.threshold(gray,127,255,0)
    _img,contours,_ = cv2.findContours(thresh,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)

    i = 0
    for cnt in contours:
        if cv2.contourArea(cnt) > 500:#and _[0, i, 2] == -1:  # remove small areas like noise etc
            hull = cv2.convexHull(cnt)    # find the convex hull of contour
            hull = cv2.approxPolyDP(hull,0.1 * cv2.arcLength(hull,True), True)
            if len(hull) == 4:
                cv2.drawContours(img,[hull],0,(0,0,255),2)
        i += 1

    cv2.imshow('img',img)
    cv2.waitKey(30)

cv2.destroyAllWindows()
