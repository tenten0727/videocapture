#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    cam.setup(ofGetWidth(), ofGetHeight());
    
    blend_image.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    src.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    
    blend_frame = cv::Mat(blend_image.getHeight(), blend_image.getWidth(), CV_MAKETYPE(CV_8UC3, blend_image.getPixels().getNumChannels()), blend_image.getPixels().getData(), 0);
    
    save_index = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    
    if(cam.isFrameNew()){
        src.setFromPixels(cam.getPixels());
    }
    
    cv::Mat srcMat;
    srcMat = ofxCv::toCv(src);
    
    if (ofGetFrameNum() < FRAME_NUM) {
        for (int i = ofGetFrameNum() - 1; i > 0; i--) {
            save_frame[i - 1].copyTo(save_frame[i]);
        }
        srcMat.copyTo(save_frame[0]);
    }
    else {
        for (int i = FRAME_NUM - 1; i > 0; i--) {
            save_frame[i - 1].copyTo(save_frame[i]);
        }
        srcMat.copyTo(save_frame[0]);
    }
    
    if(ofGetFrameNum() > FRAME_NUM){
       for (int y = 0; y < blend_frame.rows; y++) {
           for (int x = 0; x < blend_frame.cols; x++) {
               int index = ofNoise(x * 0.002, y * 0.002, ofGetFrameNum() * 0.05) * 120;
               blend_frame.at<cv::Vec3b>(y, x) = save_frame[index].at<cv::Vec3b>(y, x);
           }
        }
        blend_image.update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (ofGetFrameNum() > FRAME_NUM) {
        this->blend_image.draw(0, 0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
