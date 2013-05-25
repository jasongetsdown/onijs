#include <node.h>
#include <v8.h>
#include <openni.h>

using namespace v8;
using namespace openni;

videoStream depthStream;

class FrameListener : public VideoStream::Listener
{
    VideoFrameRef m_frame;
	Handle<Function> cb;
public:
    FrameListener( Handle<Function> callback) { cb = callback };
	void onNewFrame( VideoStream& );
};


void frameListener::onNewFrame(VideoStream& stream) {
    stream.readFrame(&m_frame);
    
    const unsigned argc = 1;
    Local<Value> argv[argc] = { analyzeFrame(m_frame) };
    newFrame->Call( Context::GetCurrent()->Global(), argc, argv );
}


//Bind an event handler
//The first argument is a string that specifies the event type (i.e. "newFrame")
//The second argument a callback function(err, data)
Handle<Value> on( const Arguments& args ) {
    HandleScope scope;
    
    Local<String> event = Local<String>::Cast( args[0] );
    
    switch (event) {
        case "newFrame":
            FrameListener listener( Handle<Function>::Cast(args[1]) );
            depth.addNewFrameListener( listener );
            break;
        default:
            break;
    }
    
    return scope.Close( Undefined() );
}


void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("on"), FunctionTemplate::New(on)->GetFunction());
}

NODE_MODULE(onijs, init)