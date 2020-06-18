#include <iostream> 
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat frame;
	Mat image;
	VideoCapture cap;
	cap.open("test2.mp4");
	if (!cap.isOpened()) return -1;
	//cv.VideoWriter(	filename, fourcc, fps, frameSize[, isColor])，视频编写器，写入到write.mp4
	VideoWriter writer("write.mp4", VideoWriter::fourcc('D', 'I', 'V', 'X'), 25.0, Size(512, 500));//MPEG-4 

	HOGDescriptor hog;// 定义HOG对象，HOGDescriptor(Size(64,128), Size(16,16), Size(8,8), Size(8,8), 9 )
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());// 行人检测分类器  

	vector<Rect> regions;
	int i = 0;
	while (true)
	{
		if (i > 20) break;// 显示20个画面后结束

		cap >> frame;
		imshow("Source Video", frame);
		if (frame.empty())
			break;
		frame.copyTo(image);

		// 检测行人区域  
		hog.detectMultiScale(image, regions, 0, cv::Size(8, 8), cv::Size(32, 32), 1.05, 2);

		// 红色矩形框出行人 
		for (size_t j = 0; j < regions.size(); j++) {
			cv::rectangle(image, regions[j], cv::Scalar(0, 0, 255), 2);
		}
		imshow("Pedestrian Detection", image);
		writer << image;
		waitKey(1); // 延时1ms
		i++;
	}
	cv::waitKey(0);// <=0无限等待按键
	return 0;
}