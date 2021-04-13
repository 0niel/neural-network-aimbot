# neural-network-aimbot
This is an undetected aimbot that works with the YOLOv3-tiny neural network object detection. You can train her on any of your favorite games.

## Requirements:
* **OpenCV.** To install OpenCV for Visual Studio 2019 use this guide https://www.opencv-srf.com/2017/11/install-opencv-with-visual-studio.html

## How does aimbot work?
Aimbot uses WinAPI functions to move the mouse cursor to the center of the area detected by the neural network each frame.

## Why YOLOv3-tiny?
YOLOv3 is optimized to recognize human-like entities well. YOLO is often cited as one of the fastest architectures for deep learning-based object recognition, achieving a higher frame rate per second. YOLOv3, for example, is more than 1000 times faster than R-CNN, and 100 times faster than Fast R-CNN.

YOLOv3-tiny is a "lightweight" (so to speak) model of YOLOv3, optimized for higher FPS and work on devices like the Raspberry Pi, but it pays for its speed with accuracy.

![image](https://user-images.githubusercontent.com/51058739/114594526-06520c80-9c96-11eb-817f-d69d6c65d359.png)

**Performance on the COCO dataset**
|Model|Train|Test|mAP|FLOPS|FPS|Cfg|Weights|
| --- | --- | --- | --- | --- | --- | --- | --- |
|SSD300|COCO trainval|test-dev|41.2|-|46|[link](https://arxiv.org/abs/1512.02325)|
|SSD500|COCO trainval|test-dev|46.5|-|19|[link](https://arxiv.org/abs/1512.02325)|
|YOLOv2 608x608|COCO trainval|test-dev|48.1|62.94 Bn|40|[cfg](https://github.com/pjreddie/darknet/blob/master/cfg/yolov2.cfg)|[weights](https://pjreddie.com/media/files/yolov2.weights)|
|Tiny YOLO|COCO trainval|test-dev|23.7|5.41 Bn|244|[cfg](https://github.com/pjreddie/darknet/blob/master/cfg/yolov2-tiny.cfg)|[weights](https://pjreddie.com/media/files/yolov2-tiny.weights)|
||
|SSD321|COCO trainval|test-dev|45.4|-|16|[link](https://arxiv.org/abs/1701.06659)|
|DSSD321|COCO trainval|test-dev|46.1|-|12|[link](https://arxiv.org/abs/1701.06659)|
|R-FCN|COCO trainval|test-dev|51.9|-|12|[link](https://arxiv.org/abs/1605.06409)|
|SSD513|COCO trainval|test-dev|50.4|-|8|[link](https://arxiv.org/abs/1701.06659)|
|DSSD513|COCO trainval|test-dev|53.3|-|6|[link](https://arxiv.org/abs/1701.06659)|
|FPN FRCN|COCO trainval|test-dev|59.1|-|6|[link](https://arxiv.org/abs/1612.03144)|
|Retinanet-50-500|COCO trainval|test-dev|50.9|-|14|link|
|Retinanet-101-500|COCO trainval|test-dev|53.1|-|11|link|
|Retinanet-101-800|COCO trainval|test-dev|57.5|-|5|link|
|YOLOv3-320|COCO trainval|test-dev|51.5|38.97 Bn|45|[cfg](https://github.com/pjreddie/darknet/blob/master/cfg/yolov3.cfg)|[weights](https://pjreddie.com/media/files/yolov3.weights)|
|YOLOv3-416|COCO trainval|test-dev|55.3|65.86 Bn|35|[cfg](https://github.com/pjreddie/darknet/blob/master/cfg/yolov3.cfg)|[weights](https://pjreddie.com/media/files/yolov3.weights)|
|YOLOv3-608|COCO trainval|test-dev|57.9|140.69 Bn|20|[cfg](https://github.com/pjreddie/darknet/blob/master/cfg/yolov3.cfg)|[weights](https://pjreddie.com/media/files/yolov3.weights)|
|YOLOv3-tiny|COCO trainval|test-dev|33.1|5.56 Bn|220|[cfg](https://github.com/pjreddie/darknet/blob/master/cfg/yolov3-tiny.cfg)|[weights](https://pjreddie.com/media/files/yolov3-tiny.weights)|
|YOLOv3-spp|COCO trainval|test-dev|60.6|141.45 Bn|20|[cfg](https://github.com/pjreddie/darknet/blob/master/cfg/yolov3-spp.cfg)|[weights](https://pjreddie.com/media/files/yolov3-spp.weights)|

## How detection works:
https://youtu.be/F1cYlHfw2To


*More information about training, testing, and configuring the YOLO model:* https://github.com/AlexeyAB/darknet
