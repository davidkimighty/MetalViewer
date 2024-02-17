//
//  app_delegate.hpp
//  MetalViewer
//
//  Created by Hyunwoo Kim on 2/17/24.
//

#ifndef app_delegate_hpp
#define app_delegate_hpp

#include "../config.h"
#include "view_delegate.hpp"

class AppDelegate : public NS::ApplicationDelegate {
public:
    ~AppDelegate();
    
    virtual void applicationWillFinishLaunching(NS::Notification* notification) override;
    virtual void applicationDidFinishLaunching(NS::Notification* notification) override;
    virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* sender) override;
    
private:
    NS::Window* window;
    MTK::View* mtkView;
    MTL::Device* device;
    ViewDelegate* viewDelegate = nullptr;
};

#endif /* app_delegate_hpp */
