//
//  view_delegate.hpp
//  MetalViewer
//
//  Created by Hyunwoo Kim on 2/4/24.
//

#ifndef view_delegate_hpp
#define view_delegate_hpp

#include "config.h"
#include "../view/renderer.hpp"

class ViewDelegate : public MTK::ViewDelegate {
    public:
        ViewDelegate(MTL::Device* device);
        virtual ~ViewDelegate() override;
        virtual void drawInMTKView(MTK::View* view) override;

    private:
        Renderer* renderer;
};

#endif /* view_delegate_hpp */
