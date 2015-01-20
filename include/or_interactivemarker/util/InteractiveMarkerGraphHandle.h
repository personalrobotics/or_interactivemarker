#ifndef INTERACTIVEMARKERGRAPHHANDLE_H_
#define INTERACTIVEMARKERGRAPHHANDLE_H_
#include <openrave/openrave.h>
#include <interactive_markers/interactive_marker_server.h>

namespace or_interactivemarker {
namespace util {

class InteractiveMarkerGraphHandle : public OpenRAVE::GraphHandle {
public:
    typedef boost::shared_ptr<interactive_markers::InteractiveMarkerServer> InteractiveMarkerServerPtr;

    InteractiveMarkerGraphHandle(
        InteractiveMarkerServerPtr const &interactive_marker_server,
        visualization_msgs::InteractiveMarkerPtr const &interactive_marker
    );

    virtual ~InteractiveMarkerGraphHandle();

    void set_parent_frame(std::string const &frame_id);

    virtual void SetTransform(OpenRAVE::RaveTransform<float> const &t);
    virtual void SetShow(bool show);

private:
    InteractiveMarkerServerPtr server_;
    visualization_msgs::InteractiveMarkerPtr interactive_marker_;
    bool show_;
};

}}

#endif
