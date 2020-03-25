#ifndef _LSB
#define _LSB

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <cstdint>

class LSB
{
private:
	cv::Mat m_image;
	std::vector<bool> m_message;
	uint32_t m_key;

	std::vector<bool> toBinary(const std::string& message);
	uint32_t flipLSB(const uint32_t& value);
public:
	LSB() = default;
	LSB(const std::string& image, const std::string& message, const uint32_t& key);
	LSB(const std::string& image, const uint32_t& key);
	void setImage(const std::string& image);
	void setMessage(const std::string& message);
	void setKey(const uint32_t& key);
	cv::Mat embed();
	std::string extract();
};

#endif