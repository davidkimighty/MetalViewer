//
//  renderer.cpp
//  MetalViewer
//
//  Created by Hyunwoo Kim on 2/4/24.
//

#include "renderer.hpp"

Renderer::Renderer(MTL::Device* device) : device(device->retain()) {
    commandQueue = device->newCommandQueue();
    buildShaders();
}

Renderer::~Renderer() {
    commandQueue->release();
    device->release();
}

void Renderer::buildShaders() {
    std::ifstream file;
    file.open("shaders/triangle.metal");
    std::stringstream reader;
    reader << file.rdbuf();
    std::string raw_string = reader.str();
    NS::String* source_code = NS::String::string(raw_string.c_str(),
                                                 NS::StringEncoding::UTF8StringEncoding);
    NS::Error* error = nullptr;
    MTL::CompileOptions* options = nullptr;
    MTL::Library* library = device->newLibrary(source_code, options, &error);
    if (!library) {
        std::cout << error->localizedDescription()->utf8String() << std::endl;
    }
    
    NS::String* vertexName = NS::String::string("vertexMain", NS::StringEncoding::UTF8StringEncoding);
    MTL::Function* vertexMain = library->newFunction(vertexName);
    
    NS::String* fragmentName = NS::String::string("fragmentMain", NS::StringEncoding::UTF8StringEncoding);
    MTL::Function* fragmentMain = library->newFunction(fragmentName);
    
    MTL::RenderPipelineDescriptor* descriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    descriptor->setVertexFunction(vertexMain);
    descriptor->setFragmentFunction(fragmentMain);
    descriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    
    trianglePipeline = device->newRenderPipelineState(descriptor, &error);
    if (!library) {
        std::cout << error->localizedDescription()->utf8String() << std::endl;
    }
    
    vertexMain->release();
    fragmentMain->release();
    descriptor->release();
    library->release();
}

void Renderer::draw(MTK::View* view) {
    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();
    
    MTL::CommandBuffer* commandBuffer = commandQueue->commandBuffer();
    MTL::RenderPassDescriptor* renderPass = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* encoder = commandBuffer->renderCommandEncoder(renderPass);
    
    encoder->setRenderPipelineState(trianglePipeline);
    encoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle,
                            NS::UInteger(0), NS::UInteger(3));
    
    encoder->endEncoding();
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();
    
    pool->release();
}
