

#include "Camera.h"




void Camera::update(float targetX, float targetY) {
    this->targetX = targetX - (w / 2);  // Center on target
    this->targetY = targetY - (h / 2);
    
    if (smoothFollow) {
        
        x += (this->targetX - x) * followSpeed;
        y += (this->targetY - y) * followSpeed;
    } else {
        // Immediate follow
        x = this->targetX;
        y = this->targetY;
    }
    
    if(x < 0) x = 0;
    if(y < 0) y = 0;

    //x = std::clamp(x, 0.0f, static_cast<float>(levelWidth - w));
    //y = std::clamp(y, 0.0f, static_cast<float>(levelHeight - h));
}