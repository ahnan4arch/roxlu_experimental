#include <glfw_wrapper/SimulationBase.h>
#include <roxlu/Roxlu.h>
//#include "Webcam.h"
#include <videocapture/VideoCapture.h>
#include <videocapture/VideoCaptureGLSurface.h>
#include <videocapture/edsdk/Canon.h>

//#include <videocapture/mac/VideoCaptureMac.h>
//#include "VideoCaptureMediaFoundation.h"
//#include "VideoCaptureDirectShow.h"

//#define USE_CANON // use canon 
//#define USE_MF  // use MediaFoundation grabber
//#define USE_DS  // use DirectShow grabber
void on_frame(AVFrame* in, size_t nbytesIn, AVFrame* out, size_t nbytesOut, void* user);

class Simulation : public SimulationBase {
 public:
  Simulation();
  void setup();
  void update();
  void draw();
  void onMouseDown(int x, int y, int buton);
  void onMouseUp(int x, int y, int button);
  void onMouseDrag(int x, int y, int dx, int dy, int button);
  void onMouseMove(int x, int y);
  void onChar(int ch); 
  void onKeyDown(int key);
  void onKeyUp(int key);
  void onWindowClose();
 public:
  unsigned char* pixels;
  bool has_new_frame;

  FPS fps;
  VideoCaptureGLSurface surface;

#if defined(USE_CANON)
  Canon can;
#endif

#if !defined(USE_CANON)
  VideoCapture cap;
#endif

#if defined(USE_DS)
  VideoCaptureDirectShow2 cap;
#endif

#if defined(USE_MF)
  VideoCaptureMediaFoundation cap;
#endif
};
