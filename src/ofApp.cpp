#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(50, 0);

    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.

    bAnimate = false;
    bAnimateMouse = false;
    animationPosition = 0;
    
    model.loadModel("sysiphus2.dae", true);
    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    if(!bAnimate) {
        model.setPausedForAllAnimations(true);
    }
    
    mountainModel.loadModel("MOUNTAINfinal.3ds", true);
    mountainModel.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    mountainModel.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    mountainModel.playAllAnimations();
    if(!bAnimate) {
        mountainModel.setPausedForAllAnimations(true);
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    model.update();
    
    if(bAnimateMouse) {
        model.setPositionForAllAnimations(animationPosition);
    }

    mesh = model.getCurrentAnimatedMesh(0);


mountainModel.update();

if(bAnimateMouse) {
    mountainModel.setPositionForAllAnimations(animationPosition);
}

mountainMesh = mountainModel.getCurrentAnimatedMesh(0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    camera.begin();
    
    
    ofSetColor(255);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
	ofEnableDepthTest();
    
    glShadeModel(GL_SMOOTH); //some model / light stuff
    light.enable();
    ofEnableSeparateSpecularLight();
/*
    ofPushMatrix();
    ofTranslate(model.getPosition().x+100, model.getPosition().y, 0);
    ofRotate(-mouseX, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    model.drawFaces();
    ofPopMatrix();
    
    */

   if(ofGetGLProgrammableRenderer()){
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
    }
    glEnable(GL_NORMALIZE);

    ofPushMatrix();
    ofTranslate(model.getPosition().x+100, model.getPosition().y, 0);
    ofRotate(270, 0, 0, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    
    
    ofxAssimpMeshHelper & meshHelper = model.getMeshHelper(0);
    
    ofMultMatrix(model.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);
    
    ofMaterial & material = meshHelper.material;
    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().bind();
    }
    material.begin();
    mesh.drawWireframe();
    material.end();
    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().unbind();
    }
    ofPopMatrix();
    
    //drawing mountain
    
    ofPushMatrix();
    ofTranslate(mountainModel.getPosition().x+100, mountainModel.getPosition().y, 0);
    ofRotate(270, 0, 0, 0);
    ofTranslate(-mountainModel.getPosition().x, -mountainModel.getPosition().y, 0);
    
    
    ofxAssimpMeshHelper & mountainMeshHelper = mountainModel.getMeshHelper(0);
    
    ofMultMatrix(mountainModel.getModelMatrix());
    ofMultMatrix(mountainMeshHelper.matrix);
    
    material = meshHelper.material;
    if(mountainMeshHelper.hasTexture()){
        mountainMeshHelper.getTextureRef().bind();
    }
    material.begin();
    mountainMesh.drawWireframe();
    material.end();
    if(mountainMeshHelper.hasTexture()){
        mountainMeshHelper.getTextureRef().unbind();
    }
    ofPopMatrix();
    
    //end draw mountain

    if(ofGetGLProgrammableRenderer()){
    	glPopAttrib();
    }
    
    ofDisableDepthTest();
    light.disable();
    ofDisableLighting();
    ofDisableSeparateSpecularLight();
    
    ofSetColor(255, 255, 255 );
    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
    ofDrawBitmapString("keys 1-5 load models, spacebar to trigger animation", 10, 30);
    ofDrawBitmapString("drag to control animation with mouseY", 10, 45);
    ofDrawBitmapString("num animations for this model: " + ofToString(model.getAnimationCount()), 10, 60);
    
    camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofPoint modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75);
    switch (key) {
        case '1':
            //CHANGE 3D MODEL FILE
            model.loadModel("sysiphus.dae");
            model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            ofEnableSeparateSpecularLight();
            break;
        case '2':
            model.loadModel("sysiphus4.dae");
            model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            //model.setRotation(0, 0, 1, 0, 0);
            ofEnableSeparateSpecularLight();
            break;
        case '3':
            model.loadModel("MOUNTAINfinal.3ds");
            model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            ofDisableSeparateSpecularLight();
            break;
        case '4':
            model.loadModel("sysiphus4.dae");
            model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            model.setRotation(0, -90, 0, 0, 1);
            ofDisableSeparateSpecularLight();
            break;
		case '5':
			model.loadModel("sysiphus5.dae");
		    model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            ofDisableSeparateSpecularLight();
			break;
		case ' ':
			bAnimate = !bAnimate;
			break;
        case '8':
            animationPosition = animationPosition-0.05 ;
            bAnimateMouse = true;
            if (animationPosition <= 0){
                animationPosition = 1;
            }
            break;
        case '9':
            animationPosition = animationPosition+0.05 ;
            bAnimateMouse = true;
            if (animationPosition >= 1){
                animationPosition = 0;
            }
            break;
        default:
            break;
    }
    
    

	mesh = model.getMesh(0);

    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    if(!bAnimate) {
        model.setPausedForAllAnimations(true);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // scrub through aninations manually.
	//animationPosition = y / (float)ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // pause all animations, so we can scrub through them manually.
    model.setPausedForAllAnimations(true);
	animationPosition = y / (float)ofGetHeight();
    bAnimateMouse = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // unpause animations when finished scrubbing.
    if(bAnimate) {
        model.setPausedForAllAnimations(false);
    }
    bAnimateMouse = false;
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

