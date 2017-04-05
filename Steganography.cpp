#include "Steganography.hpp"

#include <random>
#include <algorithm>
#include <utility>
#include <bitset>
#include <map>
#include <cmath>


LSB :: LSB(const std::string& image, const std::string& message, const uint32_t& key) : m_image(cv::imread(image)), m_message(toBinary(message)), m_key(key) {}

LSB :: LSB(const std::string& image, const uint32_t& key) : m_image(cv::imread(image)), m_key(key) {}

void LSB :: setImage(const std::string& image) {
    m_image = cv::imread(image);
}

void LSB :: setMessage(const std::string& message) {
    m_message = toBinary(message);
}

void LSB :: setKey(const uint32_t& key) {
    m_key = key;
}

std::vector<bool> LSB :: toBinary(const std::string& message) {
    std::vector<bool> message_binary;
    std::vector<bool> escape_chr{0, 0, 0, 1, 1, 0, 1, 1};
    for(char c : message) {
        std::bitset<8> byte(c);
        for(int32_t i = 7; i >= 0; --i) {
            message_binary.push_back(byte[i]);
        }
    }
    message_binary.resize(message_binary.size() + 8);
    std::copy_n(escape_chr.begin(), 8, message_binary.end() - 8);
    return message_binary;
}

uint32_t LSB :: flipLSB(const uint32_t& value) {
    return value + pow(-1, value);
}

cv::Mat LSB :: embed() {
    std::minstd_rand PRNG(m_key);
    std::map<std::pair<uint32_t, uint32_t>, bool> visited;
    cv::Mat stego_img = m_image.clone();
    uint32_t rows = stego_img.rows;
    uint32_t cols = stego_img.cols * stego_img.channels();

	if(stego_img.isContinuous()) {
		cols *= rows;
		rows = 1;
	}

    for(bool b : m_message) {
        std::pair<uint32_t, uint32_t> point = std::make_pair(PRNG() % rows, PRNG() % cols);
        while(visited[point]) {
            point = std::make_pair(PRNG() % rows, PRNG() % cols);
        }

        visited[point] = true;

        if( (stego_img.at<uchar>(point.first, point.second) & 1) != b) {
            stego_img.at<uchar>(point.first, point.second) = flipLSB(stego_img.at<uchar>(point.first, point.second));
        }
    }
    return stego_img;
}

std::string LSB :: extract() {
    std::minstd_rand PRNG(m_key);
    std::string message;
    std::map<std::pair<uint32_t, uint32_t>, bool> visited;
    std::bitset<8> byte(0);
    uint32_t rows = m_image.rows;
    uint32_t cols = m_image.cols * m_image.channels();

	if(m_image.isContinuous()) {
		cols *= rows;
		rows = 1;
	}

    while(byte.to_ulong() != 27) {
        message.push_back(static_cast<char>(byte.to_ulong()));

        for(int32_t pos = 7; pos >= 0; --pos) {
            std::pair<uint32_t, uint32_t> point = std::make_pair(PRNG() % rows, PRNG() % cols);
            while(visited[point]) {
                point = std::make_pair(PRNG() % rows, PRNG() % cols);
            }

            visited[point] = true;

            byte[pos] = (m_image.at<uchar>(point.first, point.second) & 1);
        }
    }
    return message.substr(1);
}