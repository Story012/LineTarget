#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#define KEY_ESC 27

using Pixel = cv::Vec<uchar, 3>; // G,B,R

uchar gray(Pixel p) {
    return 0.3*p[2] + 0.59*p[1] + 0.11*p[0];
}

void plotRow(cv::Mat &image, std::vector<uchar> row_colors, int y, float scale, cv::Scalar color) {
    std::vector<cv::Point> points;
    for (int x = 0; x < row_colors.size(); ++x)
        points.push_back( cv::Point(x, y - scale*row_colors[x]) );
    cv::polylines(image, points, false, color, 2);
}

void findCenterLine(std::vector<uchar> b, cv::Mat &image, cv::Mat &canvas, int y){
    int b_thresh = 0.95*(*max_element(b.begin(), b.end()));
    std::vector<cv::Point2i> cent;
    for (int x = 0; x < image.cols; ++x )
        if (b[x] > b_thresh) cent.push_back(cv::Point(x,y));
    // cv::polylines(canvas, cent, false, cv::Scalar(255,255,255), 2);
    cv::circle(canvas,cent.front(),3,cv::Scalar(255,255,255),1);
    cv::circle(canvas,cent.back(),3,cv::Scalar(255,255,255),1);
    cv::Point midpnt, midint; 
    midpnt = (cent.front() + cent.back())*0.5;
    midint = static_cast<cv::Point2i>(midpnt/2);
    cv::circle(canvas,midpnt,10,cv::Scalar(255,255,255),1);
    cv::line(canvas,midpnt,cv::Point(image.cols/2,y),cv::Scalar(255, 255, 255),2);
    cv::line(canvas,cv::Point(image.cols/2,y+10),cv::Point(image.cols/2,y-10),cv::Scalar(0, 0, 255),2);
    cv::line(canvas,cv::Point(image.cols/2+10,y),cv::Point(image.cols/2-10,y),cv::Scalar(0, 0, 255),2);
}

int main(int argc, char** argv) {

    //Trackbar info:
    cv::namedWindow("EML4840");
    // Trackers
    int track_row = 70;     // Percentage
    int track_scale = 40;   // Percentage
    int track_resize = 100;
    cv::createTrackbar("Row", "EML4840", &track_row, 100);
    cv::createTrackbar("Scale", "EML4840", &track_scale, 100);
    cv::createTrackbar("resize", "EML4840", &track_resize, 100);
    // Menu
    bool show_red = true;
    bool show_blue = true;
    bool show_green = true;
    bool show_gray = true;
    
    // Create vectors to store the graphs
    std::vector<uchar> r, g, b, k;
    
    cv::VideoCapture cap("../line.mp4");
    if ( !cap.isOpened() )  // isOpened() returns true if capturing has been initialized.
    {
        std::cout << "Cannot open the video file. \n";
        return -1;
    }
    // Capturing frame
    cv::Mat image;
    bool okay = cap.read( image );
    // Checking format
    std::string type = cv::typeToString( image.type() );
    std::cout << type << std::endl
            << image.rows << "x" << image.cols
            << std::endl;
    if (type != "CV_8UC3") {
        std::cout << "Ops, format '" << type << "' not supported!" << std::endl;
        return 1;
    }

    std::cout << "Press:" << std::endl
              << "s            : to save image" << std::endl
              << "r, g, b, or k: to show colors" << std::endl
              << "q or ESC     : to quit" << std::endl;

    bool running = true;
    while( true ) {
        
        cap.read(image);
        r.clear();
        g.clear();
        b.clear();
        k.clear();
        // Update scale
        float scale = 0.01*track_scale;
        // Pixel scanine
        int y = 0.01*track_row*(image.rows-1);
        for (int x = 0; x < image.cols; ++x ) {
            Pixel pixel = image.at<Pixel>( cv::Point(x, y) );
            r.push_back( pixel[2] );
            g.push_back( pixel[1] );
            b.push_back( pixel[0] );
            k.push_back( gray(pixel) );
        }
        // clone image and keep the orginal for processing!
        cv::Mat canvas = image.clone();
        if (show_red)   plotRow(canvas, r, y, scale, cv::Scalar(0,0,255));
        if (show_green) plotRow(canvas, g, y, scale, cv::Scalar(0,255,0));
        if (show_blue)  plotRow(canvas, b, y, scale, cv::Scalar(255,0,0));
        if (show_gray)  plotRow(canvas, k, y, scale, cv::Scalar(0,0,0));
        cv::line(canvas, cv::Point(0, y), cv::Point(image.cols, y), cv::Scalar(0,0,0), 2);
        
        findCenterLine(b,image,canvas,y);
        
        // Menu
        int key = cv::waitKey(10);
        switch(key) {
        case 's':
            cv::imwrite("../output.png", canvas);
            continue;
        case 'q':
            running = false;
            goto exit_loop;
        case KEY_ESC:
            running = false;
            goto exit_loop;
        case 'r':
            show_red = !show_red;
            continue;
        case 'g':
            show_green = !show_green;
            continue;
        case 'b':
            show_blue = !show_blue;
            continue;
        case 'k':
            show_gray = !show_gray;
            continue;
        }
        // Show image
        cv::resize(canvas, canvas, cv::Size(), 0.01*track_resize, 0.01*track_resize);
        cv::imshow("EML4840", canvas);
    }
    exit_loop: ;
    // Close all windows
    cv::destroyAllWindows();
    return 0;
}

