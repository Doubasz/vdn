

#include "Camera.h"




void Camera::update(float targetX, float targetY, float deltaTime) {

    // Center on target
    this->targetX = targetX - (w / 2);  
    this->targetY = targetY - (h / 2);
    
    if (smoothFollow) {
        x += (this->targetX - x) * followSpeed;
        y += (this->targetY - y) * followSpeed;
    } 
    else {
        // Immediate follow
        x = this->targetX;
        y = this->targetY;
    }
    
    // if out of bonds
    if (x < 0) x = 0;
    if (y < 0) y = 0;

    if(x > levelWidth - w) x = levelWidth - w;
    if(y > levelHeight - h) y = levelHeight - h;
    


    // apply shaking if active
    if(isShaking){
        shakeTimer += deltaTime;

        if(shakeTimer < shakeDuration){
            float offSetX = (rand() % 100) / 100.0f * shakeIntensity;
            float offSetY = (rand() % 100) / 100.0f * shakeIntensity;

            if(rand() % 2 == 0) offSetX *= -1;
            if(rand() % 2 == 0) offSetY *= -1;

            x += offSetX;
            y += offSetY;

            //  also checks here if out of bonds just in case
            if (x < 0) x = 0;
            if (y < 0) y = 0;

            if(x > levelWidth - w) x = levelWidth - w;
            if(y > levelHeight - h) y = levelHeight - h;
        }
        else{
            isShaking = false;
        }
    }
}


void Camera::shake(float intensity, float duration){
    shakeTimer = 0;
    isShaking = true;
    shakeDuration = duration;
    shakeIntensity = intensity;
}