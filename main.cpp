#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <iostream>

using namespace cv;

int mouseX[2], mouseY[2];
int stage = 0;
double settings[4] = {3, 8, 0, 0.01}; // thickness, lineType, shift, tip length
int color[3] = {255, 0, 0};

void mouseCallbackFunc(int event, int x, int y, int flags, void* userdata)
{
    if(event == EVENT_LBUTTONDOWN)
    {
      mouseX[stage] = x;
      mouseY[stage] = y;
      ++stage;
    }
}

cv::Mat makeGrayscale(cv::Mat normImage)
{
  cv::Mat grayImage;
  cv::cvtColor(normImage, grayImage, CV_BGR2GRAY);
  cv::namedWindow("VR Painter", 1); // ali NORMAL ali FREERATIO
  cv::imshow("VR Painter", grayImage);
  std::cout << "Press a key to exit this function.\n";
  cv::imwrite("grayscaleOutput.jpg", grayImage);
  cv::waitKey(0);
  return grayImage;
}

cv::Mat makeLine(cv::Mat lineImage)
{////////////////////////pogruntej kako v funkciji prikazes sliko/////////////////////////
  cv::namedWindow("VR Painter", 1); // ali NORMAL ali FREERATIO
  cv::imshow("VR Painter", lineImage);
  std::cout << "Click on two places to make a line. Then press a key to exit this function\n";
  cv::waitKey(0);
  cv::line(lineImage, Point(mouseX[0], mouseY[0]), Point(mouseX[1], mouseY[1]), CV_RGB(color[0], color[1], color[2]), (int)settings[0], (int)settings[1], (int)settings[2]);
  cv::imwrite("lineImage.jpg", lineImage);
  stage = 0;
  return lineImage;
}

cv::Mat makeArrowedLine(cv::Mat arrLineImage)
{
	cv::namedWindow("VR Painter", 1); // ali NORMAL ali FREERATIO
  	cv::imshow("VR Painter", arrLineImage);
 	std::cout << "Click on two places to make a line. Then press a key to exit this function\n";
  	cv::waitKey(0);
 	cv::arrowedLine(arrLineImage, Point(mouseX[0], mouseY[0]), Point(mouseX[1], mouseY[1]), CV_RGB(color[0], color[1], color[2]), (int)settings[0], (int)settings[1], (int)settings[2], settings[3]);
  	cv::imwrite("arrLineImage.jpg", arrLineImage);
	stage = 0;
	return arrLineImage;
}


 
int main( int argc, char** argv ) 
{
  std::string pictureName;
  std::string functions[] = {"a convert to grayscale function", "draw a line function", "draw an arrowed line"};
  std::string responses[] = {"Ok, wtf do u wanna do now?", "Anything else?", 
                             "I'm starting to feel like you are abusing me...", 
                             "Goddamnit, can a program rest?"
                            };
  int function;
  int ct = 0;
  std::cout << "Enter a picture name: ";
  std::cin >> pictureName;
  std::cout << "----------------------------------------------------------\n";

  cv::Mat image = cv::imread(pictureName, CV_LOAD_IMAGE_COLOR);
  if(!image.data ) {
      std::cout <<  "Could not open or find the image\n";
      return -1;
  }

  cv::namedWindow("VR Painter", 1); //ali FREERATIO

  std::cout << "Enter a function:\n";
  for(int i = 0; i < (sizeof(functions)/sizeof(*functions)); i++)
  {
    std::cout << "Enter "<< i + 1 << " for: " << functions[i] << std::endl;
  }

  std::cin >> function;
  setMouseCallback("VR Painter", mouseCallbackFunc, NULL);
  //cv::imshow("VR Painter", image);

  ct = (ct > (sizeof(responses)/sizeof(*responses))) ? 0 : ct;

  switch(function)
  {
    case 1:
      image = makeGrayscale(image);
      std::cout << responses[ct++] << "\n";
      break;
    case 2:
      /*std::cout << "klikni na dve mesti da naredis crto in potem pritisni eno tipko\n";
      cv::waitKey(0);
      cv::line(image, Point(mouseX[0], mouseY[0]), Point(mouseX[1], mouseY[1]), CV_RGB(color[0], color[1], color[2]), settings[0], settings[1], settings[2]);
      cv::imwrite("newImage.jpg", image);*/
      image = makeLine(image);
      std::cout << responses[ct++] << "\n";
      break;
    case 3:
      image = makeArrowedLine(image);
      std::cout << responses[ct++] << "\n";
      break;
    default:
      std::cout << "This function doesn't exist\n";
  }

  cv::waitKey(0);
  ///////////////////USE LATER//////////////
  return 0;
}

/*g++ main.cpp -o output `pkg-config --cflags --libs opencv`
./output*/












/*#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
          cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
          cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if ( event == EVENT_MOUSEMOVE )
     {
          cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

     }
}

int main(int argc, char** argv)
{
     // Read image from file
     Mat img = imread("ja.jpg");

     //if fail to read the image
     if ( img.empty() ) 
     { 
          std::cout << "Error loading the image" << std::endl;
          return -1; 
     }

     //Create a window
     namedWindow("My Window", 1);

     //set the callback function for any mouse event
     setMouseCallback("My Window", CallBackFunc, NULL);

     //show the image
     imshow("My Window", img);
     std::cout << "ada\n";
     int x = 0;
     x++;
     std::cout << x << "\n";

     // Wait until user press some key
     waitKey(0);

     return 0;

}*/