//
//  view_delegate.cpp
//  MetalViewer
//
//  Created by Hyunwoo Kim on 2/4/24.
//

#include "view_delegate.hpp"

ViewDelegate::ViewDelegate(MTL::Device* device) : MTK::ViewDelegate(),
    renderer(new Renderer(device)) {
}

ViewDelegate::~ViewDelegate() {
    delete renderer;
}

void ViewDelegate::drawInMTKView(MTK::View* view) {
    renderer->draw(view);
}
