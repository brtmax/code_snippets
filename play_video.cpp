// Basic openCV video playing function for future reference

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

    char actualKeyPressed = 0;

    while(capturedVideo.isOpened() && !escapeKeyHasBeenPressed(actualKeyPressed)) {

        cv::imshow("imageFrame", imageFrame);
        // prepare for next iteration

        if ((capturedVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT)) { 
            capturedVideo.read(imageFrame);
        } else {
            std::cout << "Reached end of video\n";
            break;
        }

        actualKeyPressed = cv::waitKey(1);
    }

    // If the user hasn't pressed the escape key, then the window 
    // keeps showing to display the end message
    if (!escapeKeyHasBeenPressed(actualKeyPressed)) {
        cv::waitKey(0);
    }

    return 0;
    
}

// function seperated for extendability in the future
boolean escapeKeyHasBeenPressed(char actualKeyPressed) {

    if (actualKeyPressed == 27) {
        return true;
    } else {
        return false;
    }
}