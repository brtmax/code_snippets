#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

int main(void) {

    cv::VideoCapture capturedVideo;
    cv::Mat imageFrame;

    capturedVideo.open("42x42.avi") // replace with correct .avi file later

    if(!capturedVideo.isOpened()) {
        std::cout << "\nerror while reading video file" << std::endl << std::endl;
        _getch();
        return 0;
    }

    capturedVideo.read(imgFrame);

    char keyPressed = 0;

    while(capturedVideo.isOpened() && !checkForEscapeKey(keyPressed)) {

        cv::imshow("imageFrame", imageFrame);
        // prepare for next iteration

        if ((capturedVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT)) { 
            capturedVideo.read(imageFrame);
        } else {
            std::cout << "Reached end of video\n";
            break;
        }

        keyPressed = cv::waitKey(1);
    }

    if (!checkForEscapeKey(keyPressed)) {
        cv::waitKey(0);
    }

    return 0;
    
}

boolean checkForEscapeKey(char keyPressed) {

    if (keyPressed == 27) {
        return true;
    } else {
        return false;
    }
}