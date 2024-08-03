#include <chrono>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <linux/videodev2.h>
#include <mutex>
#include <opencv2/opencv.hpp> // Include OpenCV headers
#include <queue>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <thread>
#include <unistd.h>

std::queue<void *> buffers;
std::mutex mtx;

void read_queue() {

  while (true) {
    // Dequeue a buffer for video capture
    std::unique_lock<std::mutex> lock(mtx);
    struct v4l2_buffer buf;
    memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1) {
      perror("VIDIOC_DQBUF");
      close(fd);
      return 1;
    }

    // Convert the captured frame data to cv::Mat format
    if (!buffers.empty()) {
    cv::Mat frame(fmt.fmt.pix.height, fmt.fmt.pix.width, CV_8UC1,
                  buffers.front());
    }

    // Save the frame as an image file using OpenCV
    std::string filename = "frame_" + std::to_string(buf.index) + ".jpg";
    cv::imwrite(filename, frame);
    std::cout << "Hi" << std::endl;
    // Requeue the buffer for the next capture
    if (ioctl(fd, VIDIOC_QBUF, &buf) == -1) {
      perror("VIDIOC_QBUF");
      close(fd);
      return 1;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    lock.unlock();
  }
}

int main() {

  std::thread read_thread(read_queue);

  const char *videoDevice = "/dev/video2";
  int fd = open(videoDevice, O_RDWR);
  if (fd == -1) {
    perror("Failed to open video device");
    return 1;
  }

  // Set video format using VIDIOC_S_FMT
  struct v4l2_format fmt;
  memset(&fmt, 0, sizeof(fmt));
  fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  fmt.fmt.pix.width = 1920;
  fmt.fmt.pix.height = 1080;
  fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_SRGGB8;
  fmt.fmt.pix.field = V4L2_FIELD_NONE;

  if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1) {
    perror("VIDIOC_S_FMT");
    close(fd);
    return 1;
  }

  // Request and map video buffers using VIDIOC_REQBUFS and VIDIOC_QUERYBUF
  struct v4l2_requestbuffers req;
  memset(&req, 0, sizeof(req));
  req.count = 4; // Number of video buffers to allocate
  req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  req.memory = V4L2_MEMORY_MMAP;

  if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) {
    perror("VIDIOC_REQBUFS");
    close(fd);
    return 1;
  }

  // Initialize video buffers and start streaming using VIDIOC_STREAMON
  // std::vector<void *> buffers(req.count, nullptr);

  while (true) {
      std::unique_lock<std::mutex> lock(mtx);
      struct v4l2_buffer buf;
      memset(&buf, 0, sizeof(buf));
      buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buf.memory = V4L2_MEMORY_MMAP;
      buf.index = 0;

      if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1) {
        perror("VIDIOC_QUERYBUF");
        close(fd);
        return 1;
      }

      // Memory map the buffer
      buffers.push(mmap(nullptr, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED,
                        fd, buf.m.offset));

      // Queue the buffer for video capture
      if (ioctl(fd, VIDIOC_QBUF, &buf) == -1) {
        perror("VIDIOC_QBUF");
        close(fd);
        return 1;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      lock.unlock();
  }
  // Start streaming video frames
  enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  if (ioctl(fd, VIDIOC_STREAMON, &type) == -1) {
    perror("VIDIOC_STREAMON");
    close(fd);
    return 1;
  }

  std::cout << "Video streaming started. Press Ctrl+C to stop." << std::endl;

  // Main loop to capture frames

  // Stop streaming video frames
  if (ioctl(fd, VIDIOC_STREAMOFF, &type) == -1) {
    perror("VIDIOC_STREAMOFF");
    close(fd);
    return 1;
  }

  // Cleanup and close video device
  for (auto buffer : buffers) {
    munmap(buffer, fmt.fmt.pix.sizeimage);
  }
  close(fd);

  return 0;
}