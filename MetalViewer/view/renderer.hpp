//
//  renderer.hpp
//  MetalViewer
//
//  Created by Hyunwoo Kim on 2/4/24.
//

#ifndef renderer_hpp
#define renderer_hpp

#include "../config.h"

class Renderer {
    public:
        Renderer(MTL::Device* device);
        ~Renderer();
        void draw(MTK::View* view);

    private:
        MTL::Device* device;
        MTL::CommandQueue* commandQueue;
};

#endif /* renderer_hpp */
